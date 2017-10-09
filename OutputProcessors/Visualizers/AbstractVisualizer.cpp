/*
 * AbstractVisualizer.cpp
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#include "AbstractVisualizer.h"
#include <cstring>

AbstractVisualizer::AbstractVisualizer(int inputSpectrumSize, int samplingRate, AbstractVisOutputProcessor* visOutputProcessor) {
	fprintf(stdout, "AbstractVisualizer::AbstractVisualizer\n");
	this->samplingRate = samplingRate;
	this->inputSpectrumSize = inputSpectrumSize;
	this->visOutputProcessor = visOutputProcessor;
}

AbstractVisualizer::~AbstractVisualizer() {
}

VisOutputData AbstractVisualizer::prepareVisOutputData(AudioProcessingFrameData inputData) {
	VisOutputData visOutputData;
	memset(&visOutputData, false, sizeof(VisOutputData));
	visOutputData.metaData.currentBpm = inputData.currentBpm;
	return visOutputData;
}

float AbstractVisualizer::calcVisualizerHubSelectionProbabilityWeight() {
	return 1.0f;
}

