/*
 * SingleColorVisOutputter.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#include "MultiColorFCSVisOutputter.h"

MultiColorFCSVisOutputter::MultiColorFCSVisOutputter() {
}

MultiColorFCSVisOutputter::~MultiColorFCSVisOutputter() {
}

void MultiColorFCSVisOutputter::processFCS(AudioProcessingFrameData audioData, float* bars, VisOutputData* targetVisOutputData) {
	barsToVisOutputForChannel(bars[0], &targetVisOutputData->left);
	barsToVisOutputForChannel(bars[1], &targetVisOutputData->centerLeft);
	barsToVisOutputForChannel(bars[2], &targetVisOutputData->centerRight);
	barsToVisOutputForChannel(bars[3], &targetVisOutputData->right);

	targetVisOutputData->bottom.red = audioData.isBeat;
}

void MultiColorFCSVisOutputter::printVisOutputterInfo() {
	printf("MultiColorFCSVisOutputter.");
}

void MultiColorFCSVisOutputter::barsToVisOutputForChannel(float bar, UnitData* targetUnitData) {
	if ((0.0f < bar) && (bar < 0.1f)) {
		targetUnitData->red = true;
	} else if ((0.1f < bar) && (bar < 0.15f)) {
		targetUnitData->red = true;
		targetUnitData->blue = true;
	} else if ((0.15f < bar) && (bar < 0.2f)) {
		targetUnitData->blue = true;
	} else if ((0.2f < bar) && (bar < 0.25f)) {
		targetUnitData->red = true;
		targetUnitData->green = true;
	} else if ((0.25f < bar) && (bar < 0.3f)) {
		targetUnitData->green = true;
	} else if ((0.3f < bar) && (bar < 0.35f)) {
		targetUnitData->green = true;
		targetUnitData->blue = true;
	} else if ((0.35f < bar)) {
		targetUnitData->green = true;
		targetUnitData->blue = true;
		targetUnitData->red = true;
	}
}
