/*
 * BpmAnalyzer.cpp
 *
 *  Created on: Jun 13, 2017
 *      Author: ti
 */

#include "BpmAnalyzer.h"
#include <sys/time.h>
#include <math.h>
#include "../Util/ConsoleOutputHelper.h"

BpmAnalyzer::BpmAnalyzer() {
	int beatTimingHistoryLength = 50;
	this->historyItemsMaxAge = 10*1000;
	this->historyProcessingInterval = 200;
	this->shortestHistLengthForBpmAnalysis = 5;
	this->currentBpm = 0;
	this->lastHistoryProcessingTime = 0;
	this->biggestRelativeSdToAcceptBpmResult = 0.8;
	beatTimingHistory = new SimpleValueHistory<long int>(beatTimingHistoryLength, -1);
}

BpmAnalyzer::~BpmAnalyzer() {
	 if (beatTimingHistory) {
		 delete beatTimingHistory;
	 }
}

void BpmAnalyzer::postProcessAudioData(AudioProcessingFrameData* audioData) {
	long int currentMs = getCurrentMs();
	if (audioData->isBeatRaw) {
		processRawBeat(currentMs);
	}
	if (currentMs - this->lastHistoryProcessingTime > this->historyProcessingInterval) {
		cleanupHistory(currentMs);
		recalulateBpm(currentMs);

	}
	audioData->isBeatBpmAnalyzer = getIsBpmBeat();
}

bool BpmAnalyzer::getIsBpmBeat() {
	return false;
}

void BpmAnalyzer::processRawBeat(long int currentMs) {
	beatTimingHistory->addElement(currentMs);
}

void getMeanDifferenceAndSD(long int* history, int numEntriesToLookAt, double* meanDiff, double* sd) {
	(*meanDiff) = ((double)(history[0] - history[numEntriesToLookAt - 1]))/(double)(numEntriesToLookAt - 1);
	*sd = 0;
	for (int idx = 0; idx < numEntriesToLookAt - 1; idx++) {
		double dev = ((double)(history[idx] - history[idx + 1])) - (*meanDiff);
		(*sd) += dev * dev;
	}
	*sd = sqrt(*sd);
}

void BpmAnalyzer::recalulateBpm(long int currentTime) {
	int numEntriesToLookAt = beatTimingHistory->getCapacity();
	long int* lastNEntries;
	int numEntriesReturned;
	beatTimingHistory->getLastNNonDefaultEntries(numEntriesToLookAt, &lastNEntries, &numEntriesReturned);
	double meanDiff = 1;
	double sd = 1000;
	numEntriesToLookAt = numEntriesReturned;
	bool retryAnalysisWithLessData = true;
	bool acceptData = false;
	while (retryAnalysisWithLessData) {
		getMeanDifferenceAndSD(lastNEntries, numEntriesToLookAt, &meanDiff, &sd );
		if (sd > 0 && biggestRelativeSdToAcceptBpmResult > sd / meanDiff) {
			acceptData = true;
			retryAnalysisWithLessData = false;
		} else {
			numEntriesToLookAt *= 0.8;
			if (numEntriesToLookAt < shortestHistLengthForBpmAnalysis) {
				retryAnalysisWithLessData = false;
			}
		}
	}
	if (acceptData) {
		this->currentBpm = (float)(60000.0 / meanDiff);
		printf("BpmAnalyzer recalculated BPM to be #%4.2f\n", this->currentBpm);
	}

	delete[] lastNEntries;
}

void BpmAnalyzer::cleanupHistory(long int currentTime) {
	long int beatTimingHistoryDefaultValue = beatTimingHistory->getDefaultValue();
	long int* historyValues = beatTimingHistory->getValues();
	for (int idx = 0; idx < beatTimingHistory->getCapacity(); idx++) {
		if (historyValues[idx] < currentTime - this->historyItemsMaxAge) {
			historyValues[idx] = beatTimingHistoryDefaultValue;
		}
	}
}

long int BpmAnalyzer::getCurrentMs() {
	timeval tp;
	gettimeofday(&tp, (timezone*)NULL);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}
