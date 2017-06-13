/*
 * AbstractFCSVisOutputter.h
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#ifndef VISUALIZERS_FOURCHANNELSPECVISUALIZER_ABSTRACTFCSVISOUTPUTTER_H_
#define VISUALIZERS_FOURCHANNELSPECVISUALIZER_ABSTRACTFCSVISOUTPUTTER_H_

#include "../../VisOutputData.h"
#include "../../AudioData.h"

class AbstractFCSVisOutputter {
public:
	AbstractFCSVisOutputter();
	virtual ~AbstractFCSVisOutputter();

	virtual void processFCS(AudioProcessingFrameData audioData, float* bars, VisOutputData* targetVisOutputData);
	virtual void printVisOutputterInfo();
};

#endif /* VISUALIZERS_FOURCHANNELSPECVISUALIZER_ABSTRACTFCSVISOUTPUTTER_H_ */
