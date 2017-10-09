/*
 * VisualizerHub.cpp
 *
 *  Created on: Oct 9, 2017
 *      Author: ti
 */

#include "VisualizerHub.h"
#include "FourChannelSpecVisualizer/FourChannelSpecVisualizer.h"

VisualizerHub::VisualizerHub(int inputSpectrumSize, int samplingRate, AbstractVisOutputProcessor* visOutputProcessor) {
	fprintf(stdout, "VisualizerHub::VisualizerHub\n");
	this->samplingRate = samplingRate;
	this->inputSpectrumSize = inputSpectrumSize;
	this->visOutputProcessor = visOutputProcessor;
	initializeVisualizers();
	animate();
}

VisualizerHub::~VisualizerHub() {
	VisualizerWithAnimationMetaData** visualizerArray = (VisualizerWithAnimationMetaData**)visualizerList.getAsArray();
	for (int i = visualizerList.getNumberOfElements() - 1; i >= 0 ; i--) {
		delete visualizerArray[i]->visualizer;
		delete visualizerArray[i];
		visualizerList.removeElementAt(i);
	}
}

void VisualizerHub::initializeVisualizers() {
	FourChannelSpecVisualizer* fourChannelSpecVisualizer = new FourChannelSpecVisualizer(inputSpectrumSize, samplingRate, visOutputProcessor);
	registerVisualizer(fourChannelSpecVisualizer);
	currentlySelectedVisualizer = fourChannelSpecVisualizer;
}

void VisualizerHub::registerVisualizer(AbstractVisualizer* visualizer) {
	VisualizerWithAnimationMetaData* visualizerWithMetaData = new VisualizerWithAnimationMetaData;

	visualizerWithMetaData->visualizer = visualizer;
	visualizerWithMetaData->lastSelectionTime = time(NULL);
	visualizerWithMetaData->selectionCount = 0;

	visualizerList.addElement((void*)visualizerWithMetaData);
}

void VisualizerHub::processInputData(AudioProcessingFrameData inputData) {
	if (currentlySelectedVisualizer != 0) {
		currentlySelectedVisualizer->processInputData(inputData);
	}
	if (time(NULL) - timeOfLastAnimation > maxTimeBetweenAnimations || beatCounter % beatsBetweenAnimations == 0) {
		beatCounter++;
		animate();
	}
}

void VisualizerHub::animate() {
	timeOfLastAnimation = time(NULL);
	int i, j;
	VisualizerWithAnimationMetaData** visualizerArray = (VisualizerWithAnimationMetaData**)visualizerList.getAsArray();
	int totalWeight = 0;
	int* weights = new int[visualizerList.getNumberOfElements()];
	for (i = 0; i < visualizerList.getNumberOfElements(); i++) {
		weights[i] = getSelectionProbabilityWeight(visualizerArray[i]);
		totalWeight += weights[i];
	}
	int* statisticalPopulation = new int[totalWeight];
	int statisticalPopulationSize = 0;
	for (i = 0; i < visualizerList.getNumberOfElements(); i++) {
		for (j = 0; j < weights[i]; j++) {
			statisticalPopulation[statisticalPopulationSize] = i;
			statisticalPopulationSize++;
		}
	}
	int winnerIndex = statisticalPopulation[rand() % totalWeight];
	VisualizerWithAnimationMetaData* winner = visualizerArray[winnerIndex];
	printf("VisualizerHub switching Visualizer to #%i\n", winnerIndex);
	currentlySelectedVisualizer = winner->visualizer;
	winner->lastSelectionTime = time(NULL);
	winner->selectionCount++;
	totalSelectionCount++;
	delete[] weights;
	delete[] statisticalPopulation;
}

int VisualizerHub::getSelectionProbabilityWeight(VisualizerWithAnimationMetaData* visualizerWithAnimationMetaData) {
	float weight = time(NULL) - visualizerWithAnimationMetaData->lastSelectionTime;
	weight *= (totalSelectionCount+1) / (visualizerWithAnimationMetaData->selectionCount+1);
	weight *= visualizerWithAnimationMetaData->visualizer->calcVisualizerHubSelectionProbabilityWeight();
	weight = weight >= 0 ? weight : weight * -1.0f;
	weight = weight > maxWeight ? maxWeight : weight;
	return (int)(weight);
}
