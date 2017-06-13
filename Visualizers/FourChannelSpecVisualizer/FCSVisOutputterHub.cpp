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
	if ((*currentVisOutputter)!=NULL) {
		(*currentVisOutputter)->processFCS(audioData, fcsBars, targetVisOutputData);
	}
}

void FCSVisOutputterHub::animate() {
	int numVisOutputtersInList = registeredVisOutputters.size();
	int randomNumberOfIterationSteps = rand() % numVisOutputtersInList;
	printf("FCSVisOutputterHub switching VisOutputter to #%i\n", randomNumberOfIterationSteps);
	currentVisOutputter = registeredVisOutputters.begin();
	for (int i = 0; i < randomNumberOfIterationSteps; i++) {
		++currentVisOutputter;
	}
	if ((*currentVisOutputter)!=NULL) {
		(*currentVisOutputter)->printVisOutputterInfo();
	}
}

void FCSVisOutputterHub::registerVisOutputter( AbstractFCSVisOutputter* visOutputter ) {
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
