/*
 * BpmAnalyzer.h
 *
 *  Created on: Jun 13, 2017
 *      Author: ti
 */

#ifndef BPMANALYZER_H_
#define BPMANALYZER_H_

#include "../Data/AudioProcessingFrameData.h"
#include "../Data/SimpleValueHistory.h"

class BpmAnalyzer {
public:
	BpmAnalyzer();
	virtual ~BpmAnalyzer();

	void postProcessAudioData(AudioProcessingFrameData* audioData);

protected:
	bool getIsBpmBeat();
	void processRawBeat(long int currentMs);
	long int getCurrentMs();
	void recalulateBpm(long int currentTime);
	void cleanupHistory(long int currentTime);

	float currentBpm;
	long int historyItemsMaxAge;
	long int lastHistoryProcessingTime;
	long int historyProcessingInterval;
	long int shortestHistLengthForBpmAnalysis;
	float biggestRelativeSdToAcceptBpmResult;
	SimpleValueHistory<long int>* beatTimingHistory;
};

#endif /* BPMANALYZER_H_ */
