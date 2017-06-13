/*
 * FourChannelSpecVisualizer.cpp
 *
 *  Created on: 15 Apr 2017
 *      Author: Matthias
 */

#include "FourChannelSpecVisualizer.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include "FCSVisOutputterInitializer.h"

FourChannelSpecVisualizer::FourChannelSpecVisualizer(int inputSpectrumSize, int samplingRate,
		AbstractVisOutputProcessor* visOutputProcessor) :
		AbstractVisualizer(inputSpectrumSize, samplingRate, visOutputProcessor) {
	createPowerSpectrumBarIndexByBinIndex();
	//linearCorrectionFactor = 1 / ((double) numPointsToAverageOver);
	powerSpectrum = new float[inputSpectrumSize];
	minSpectrumAmplitudeHistory = new SimpleValueHistory<float>(minSpectrumAmplitudeHistoryLength, 0.0f);
	maxSpectrumAmplitudeHistory = new SimpleValueHistory<float>(maxSpectrumAmplitudeHistoryLength, 0.0f);
	channelAverageHistory = new SimpleValueHistory<float>(channelAverageHistoryLength, 0.0f);
	srand(time(NULL));
	timeOfLastAnimation = time(NULL);
	beatCounter = 1;

	FCSVisOutputterInitializer visOutputterInitializer;
	visOutputterInitializer.initVisOutputters(&visOutputterHub);
}

FourChannelSpecVisualizer::~FourChannelSpecVisualizer() {
	if (powerSpectrumBarIndexByBinIndex != NULL) {
		delete[] powerSpectrumBarIndexByBinIndex;
	}
	if (minSpectrumAmplitudeHistory) {
		delete minSpectrumAmplitudeHistory;
	}
	if (maxSpectrumAmplitudeHistory) {
		delete maxSpectrumAmplitudeHistory;
	}
	if (channelAverageHistory) {
		delete channelAverageHistory;
	}
}

static void printArrayOfFloats(int lengthOfarray, float* data) {
	char* string = new char[lengthOfarray*10];
	int lengthOfString = 0;
	memset(string, 0, 6 * lengthOfarray + 2);
	for (int i = 0; i < lengthOfarray; i++) {
		lengthOfString += sprintf(&(string[lengthOfString]), "%4.2f ", data[i]);
	}
	lengthOfString += sprintf(&(string[lengthOfString]), "\n");
	printf(string);
	delete[] string;
}

static void printArrayOfInts(int lengthOfarray, int* data) {
	char* string = new char[lengthOfarray*10];
	int lengthOfString = 0;
	memset(string, 0, 6 * lengthOfarray + 2);
	for (int i = 0; i < lengthOfarray; i++) {
		lengthOfString += sprintf(&(string[lengthOfString]), "%i ", data[i]);
	}
	lengthOfString += sprintf(&(string[lengthOfString]), "\n");
	printf(string);
	delete[] string;
}

void FourChannelSpecVisualizer::processInputData(
		AudioProcessingFrameData inputData) {
	//printf("FourChannelSpecVisualizer::processInputData\n");
	if (inputData.isBeat) {
		beatCounter++;
	}
	float* bars = new float[numChannels];
	calculatePowerSpectrumFromDftData(inputData);
	powerSpectrumToBars(&bars);
	VisOutputData visOutputData;
	memset(&visOutputData, false, sizeof(VisOutputData));
	//printf("FourChannelSpecVisualizer::processInputData -> call to VisOutputterHub.processAudioData\n");
	visOutputterHub.processAudioData(inputData, bars, &visOutputData);
	//printf("FourChannelSpecVisualizer::processInputData -> call to visOutputProcessor.processVisOutput\n");
	visOutputProcessor->processVisOutput(visOutputData);
	if (time(NULL) - timeOfLastAnimation > maxTimeBetweenAnimations || beatCounter % beatsBetweenAnimations == 0) {
		beatCounter++;
		timeOfLastAnimation = time(NULL);
		//printf("FourChannelSpecVisualizer::processInputData -> call to VisOutputterHub.animate\n");
		visOutputterHub.animate();
	}
}

void FourChannelSpecVisualizer::calculatePowerSpectrumFromDftData(
		AudioProcessingFrameData inputData) {
	float sumOfSpectrumElements;
	float smallestValue = 0;
	float highestValue = 0;
	int numRelevantBins = 14000.0f / inputData.frequencyWidth;
	if (numRelevantBins >  inputSpectrumSize/2) {
		numRelevantBins = inputSpectrumSize/2;
	}
	powerSpectrum[0] = 0;

	for (int i = 1; i < inputSpectrumSize/2; i++) {
		powerSpectrum[i] = sqrt(
				inputData.spectrum[i][0] * inputData.spectrum[i][0] + inputData.spectrum[i][1] * inputData.spectrum[i][1]);
		sumOfSpectrumElements += powerSpectrum[i] / (float) inputSpectrumSize;
	}
	for (int i = 1; i < inputSpectrumSize/2; i++) {
		powerSpectrum[i] = log(powerSpectrum[i]/*/sumOfSpectrumElements*/);
		if (powerSpectrum[i] < smallestValue) {
			smallestValue = powerSpectrum[i];
		}
		if (powerSpectrum[i] > highestValue) {
			highestValue = powerSpectrum[i];
		}
	}
	minSpectrumAmplitudeHistory->addElement(smallestValue);
	maxSpectrumAmplitudeHistory->addElement(highestValue-smallestValue);
	float offset = minSpectrumAmplitudeHistory->getAverage();
	float normalizer = maxSpectrumAmplitudeHistory->getAverage();
	if (normalizer == 0) {
		normalizer = 1.0f;
	}
	for (int i = 1; i < inputSpectrumSize / 2; i++) {
		powerSpectrum[i] -= offset;
		powerSpectrum[i] /= normalizer;
	}
}

void FourChannelSpecVisualizer::powerSpectrumToBars(float** barsOutput) {
	memset(*barsOutput, 0, numChannels * sizeof(float));
	for (int binIdx = 0; binIdx < inputSpectrumSize/2; binIdx++) {
		if (powerSpectrumBarIndexByBinIndex[binIdx] != -1) {
			if ( powerSpectrum[binIdx] > (*barsOutput)[powerSpectrumBarIndexByBinIndex[binIdx]]) {
				(*barsOutput)[powerSpectrumBarIndexByBinIndex[binIdx]] = powerSpectrum[binIdx];
			}
		}
	}
	float channelAverage = 0.0f;
	for (int barIdx = 0; barIdx < numChannels; barIdx++) {
		channelAverage += (*barsOutput)[barIdx]/numChannels;
	}
	channelAverageHistory->addElement(channelAverage);
	float historicalltAveragedChannelAverage = channelAverageHistory->getAverage();
	for (int barIdx = 0; barIdx < numChannels; barIdx++) {
		(*barsOutput)[barIdx] -= historicalltAveragedChannelAverage;
	}
}

void FourChannelSpecVisualizer::createPowerSpectrumBarIndexByBinIndex() {
	int* indexByBinIndex = new int[this->inputSpectrumSize/2];
	memset(indexByBinIndex, -1, this->inputSpectrumSize/2*sizeof(int));
	int* numBinsByBarIndex = new int[numChannels];
	memset(numBinsByBarIndex, 0, numChannels*sizeof(int));

	float channelMinFrequencies[numChannels] = {80.0f, 200.0f, 450.0f, 750.0f};
	float channelMaxFrequencies[numChannels] = {200.0f, 450.0f, 750.0f, 14000.0f};
	int binIndex;

	float BinFrequencyWidth = ((float)this->samplingRate) / ((float)this->inputSpectrumSize);

	for (int channelIdx = 0; channelIdx < numChannels; channelIdx ++) {
		int firstBinRepresentingFreqAboveMin = ceil(channelMinFrequencies[channelIdx]/BinFrequencyWidth);
		int lastBinRepresentingFreqBelowMax = floor(channelMaxFrequencies[channelIdx]/BinFrequencyWidth);

		for (binIndex = firstBinRepresentingFreqAboveMin; binIndex < lastBinRepresentingFreqBelowMax; binIndex++) {
			indexByBinIndex[binIndex] = channelIdx;
			numBinsByBarIndex[channelIdx]++;
		}
	}
	this->powerSpectrumBarIndexByBinIndex = indexByBinIndex;
	this->numBinsByBarIndex = numBinsByBarIndex;
}
