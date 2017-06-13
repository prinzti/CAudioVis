/*
 * SingleColorVisOutputter.h
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#ifndef VISUALIZERS_FOURCHANNELSPECVISUALIZER_SINGLECOLORFCSVISOUTPUTTER_H_
#define VISUALIZERS_FOURCHANNELSPECVISUALIZER_SINGLECOLORFCSVISOUTPUTTER_H_

#include "AbstractFCSVisOutputter.h"

struct UnitColorConfig {
	bool useRed;
	bool useGreen;
	bool useBlue;
};

struct VisOutputColorConfig {
	UnitColorConfig colorConfigLeft;
	UnitColorConfig colorConfigCenterLeft;
	UnitColorConfig colorConfigCenterRight;
	UnitColorConfig colorConfigRight;
	UnitColorConfig colorConfigBottom;
};

class SingleColorFCSVisOutputter : AbstractFCSVisOutputter {
public:
	SingleColorFCSVisOutputter(VisOutputColorConfig colorConfig);
	virtual ~SingleColorFCSVisOutputter();

	void processFCS(AudioProcessingFrameData audioData, float* bars, VisOutputData* targetVisOutputData);
	void printVisOutputterInfo();

private:
	VisOutputColorConfig colorConfig;
};

#endif /* VISUALIZERS_FOURCHANNELSPECVISUALIZER_SINGLECOLORFCSVISOUTPUTTER_H_ */
