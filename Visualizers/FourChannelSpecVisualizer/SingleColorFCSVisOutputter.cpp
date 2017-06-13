/*
 * SingleColorVisOutputter.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#include "SingleColorFCSVisOutputter.h"

SingleColorFCSVisOutputter::SingleColorFCSVisOutputter(VisOutputColorConfig colorConfig) {
	this->colorConfig = colorConfig;
}

SingleColorFCSVisOutputter::~SingleColorFCSVisOutputter() {
}

void printUnitColorConfig(UnitColorConfig unitColorConfig) {
	if (unitColorConfig.useRed && !unitColorConfig.useBlue && !unitColorConfig.useGreen) {
		printf("red");
	} else if (!unitColorConfig.useRed && unitColorConfig.useBlue && !unitColorConfig.useGreen) {
		printf("blue");
	} else if (!unitColorConfig.useRed && !unitColorConfig.useBlue && unitColorConfig.useGreen) {
		printf("green");
	} else if (unitColorConfig.useRed && unitColorConfig.useBlue && !unitColorConfig.useGreen) {
		printf("purple");
	} else if (unitColorConfig.useRed && !unitColorConfig.useBlue && unitColorConfig.useGreen) {
		printf("yellow");
	} else if (!unitColorConfig.useRed && unitColorConfig.useBlue && unitColorConfig.useGreen) {
		printf("cyan");
	}
}

void SingleColorFCSVisOutputter::printVisOutputterInfo() {
	printf("SingleColorFCSVisOutputter. Color scheme: left: ");
	printUnitColorConfig(colorConfig.colorConfigLeft);
	printf(", centerLeft: ");
	printUnitColorConfig(colorConfig.colorConfigCenterLeft);
	printf(", centerRight: ");
	printUnitColorConfig(colorConfig.colorConfigCenterRight);
	printf(", right: ");
	printUnitColorConfig(colorConfig.colorConfigRight);
	printf(", bottom: ");
	printUnitColorConfig(colorConfig.colorConfigBottom);
	printf("\n");
}

void setValueForOutputChannel(bool value, UnitData* targetUnitData, UnitColorConfig unitColorConfig) {
	if (value) {
		if (unitColorConfig.useRed && !unitColorConfig.useBlue && !unitColorConfig.useGreen) {
			targetUnitData->red = true;
		} else if (!unitColorConfig.useRed && unitColorConfig.useBlue && !unitColorConfig.useGreen) {
			targetUnitData->blue = true;
		} else if (!unitColorConfig.useRed && !unitColorConfig.useBlue && unitColorConfig.useGreen) {
			targetUnitData->green = true;
		} else if (unitColorConfig.useRed && unitColorConfig.useBlue && !unitColorConfig.useGreen) {
			targetUnitData->red = true;
			targetUnitData->blue = true;
		} else if (unitColorConfig.useRed && !unitColorConfig.useBlue && unitColorConfig.useGreen) {
			targetUnitData->red = true;
			targetUnitData->green = true;
		} else if (!unitColorConfig.useRed && unitColorConfig.useBlue && unitColorConfig.useGreen) {
			targetUnitData->green = true;
			targetUnitData->blue = true;
		}
	}
}

void barsToVisOutputForChannel(float bar, UnitData* targetUnitData, UnitColorConfig unitColorConfig) {
	setValueForOutputChannel(bar > 0.0f, targetUnitData, unitColorConfig);
}

void SingleColorFCSVisOutputter::processFCS(AudioProcessingFrameData audioData, float* bars, VisOutputData* targetVisOutputData) {
	//printf("SingleColorFCSVisOutputter::processAudioData\n");

	barsToVisOutputForChannel(bars[0], &(targetVisOutputData->left), (colorConfig.colorConfigLeft));
	barsToVisOutputForChannel(bars[1], &(targetVisOutputData->centerLeft), (colorConfig.colorConfigCenterLeft));
	barsToVisOutputForChannel(bars[2], &(targetVisOutputData->centerRight), (colorConfig.colorConfigCenterRight));
	barsToVisOutputForChannel(bars[3], &(targetVisOutputData->right), (colorConfig.colorConfigRight));

	setValueForOutputChannel(audioData.isBeat, &(targetVisOutputData->bottom), colorConfig.colorConfigBottom);
}


