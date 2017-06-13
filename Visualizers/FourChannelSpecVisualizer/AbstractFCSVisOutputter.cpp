/*
 * AbstractVisualizer.cpp
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#include "AbstractFCSVisOutputter.h"

AbstractFCSVisOutputter::AbstractFCSVisOutputter() {
}

AbstractFCSVisOutputter::~AbstractFCSVisOutputter() {
}

void AbstractFCSVisOutputter::processFCS(AudioProcessingFrameData audioData, float* bars, VisOutputData* targetVisOutputData) {

}

void AbstractFCSVisOutputter::printVisOutputterInfo() {
	printf("AbstractFCSVisOutputter does nothing.");
}
