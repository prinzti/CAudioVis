/*
 * FCSVisOutputterHub.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#include "FCSVisOutputterHub.h"
#include <stdlib.h>
#include <ctime>

FCSVisOutputterHub::FCSVisOutputterHub() {
	srand(time(NULL));
}

FCSVisOutputterHub::~FCSVisOutputterHub() {
	std::list<AbstractFCSVisOutputter*>::iterator registeredVisOutputtersIterator;
	for(registeredVisOutputtersIterator = registeredVisOutputters.begin(); registeredVisOutputtersIterator != registeredVisOutputters.end(); registeredVisOutputtersIterator++) {
		if (NULL != (*registeredVisOutputtersIterator)) {
			delete (*registeredVisOutputtersIterator);
		}
	}
}

void FCSVisOutputterHub::processAudioData(AudioProcessingFrameData audioData, float* fcsBars, VisOutputData* targetVisOutputData) {
	//printf("FCSVisOutputterHub::processAudioData\n");
	if ((*currentVisOutputter)!=NULL) {
		//printf("FCSVisOutputterHub::processAudioData: Call to Outputter\n");
		(*currentVisOutputter)->processFCS(audioData, fcsBars, targetVisOutputData);
	}
}

void FCSVisOutputterHub::animate() {
	int numVisOutputtersInList = registeredVisOutputters.size();
	//printf("FCSVisOutputterHub::animate numVisOutputtersInList=%i\n", numVisOutputtersInList);
	int randomNumberOfIterationSteps = rand() % numVisOutputtersInList;
	printf("FCSVisOutputterHub switching VisOutputter to #%i\n", randomNumberOfIterationSteps);
	//printf("FCSVisOutputterHub::animate iterating %i times\n", randomNumberOfIterationSteps);
	currentVisOutputter = registeredVisOutputters.begin();
	for (int i = 0; i < randomNumberOfIterationSteps; i++) {
		++currentVisOutputter;
	}
	if ((*currentVisOutputter)!=NULL) {
		(*currentVisOutputter)->printVisOutputterInfo();
	}
	//printf("FCSVisOutputterHub::animate done\n");
}

void FCSVisOutputterHub::registerVisOutputter( AbstractFCSVisOutputter* visOutputter ) {
	//printf("FCSVisOutputterHub::registerVisOutputter\n");
	registeredVisOutputters.push_back(visOutputter);
}

void FCSVisOutputterHub::deregisterVisOutputter( AbstractFCSVisOutputter* visOutputter ) {
	std::list<AbstractFCSVisOutputter*>::iterator registeredVisOutputtersIterator;
	for(registeredVisOutputtersIterator = registeredVisOutputters.begin(); registeredVisOutputtersIterator != registeredVisOutputters.end(); registeredVisOutputtersIterator++) {
		if (visOutputter == (*registeredVisOutputtersIterator)) {
			registeredVisOutputters.erase(registeredVisOutputtersIterator);
		}
	}
}
