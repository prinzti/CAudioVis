/*
 * AbstractVisualizer.cpp
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#include "AbstractVisualizer.h"

AbstractVisualizer::AbstractVisualizer(int inputSpectrumSize, int samplingRate, AbstractVisOutputProcessor* visOutputProcessor) {
	fprintf(stdout, "AbstractVisualizer::AbstractVisualizer\n");
	this->samplingRate = samplingRate;
	this->inputSpectrumSize = inputSpectrumSize;
	this->visOutputProcessor = visOutputProcessor;
}

AbstractVisualizer::~AbstractVisualizer() {
}
