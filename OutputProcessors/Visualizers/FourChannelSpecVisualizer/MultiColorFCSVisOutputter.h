/*
 * SingleColorVisOutputter.h
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#ifndef VISUALIZERS_FOURCHANNELSPECVISUALIZER_MULTICOLORFCSVISOUTPUTTER_H_
#define VISUALIZERS_FOURCHANNELSPECVISUALIZER_MULTICOLORFCSVISOUTPUTTER_H_

#include "AbstractFCSVisOutputter.h"

class MultiColorFCSVisOutputter : AbstractFCSVisOutputter {
public:
	MultiColorFCSVisOutputter();
	virtual ~MultiColorFCSVisOutputter();

	void processFCS(AudioProcessingFrameData audioData, float* bars, VisOutputData* targetVisOutputData);
	void printVisOutputterInfo();

private:
	void barsToVisOutputForChannel(float bar, UnitData* targetUnitData);
};

#endif /* VISUALIZERS_FOURCHANNELSPECVISUALIZER_MULTICOLORFCSVISOUTPUTTER_H_ */
