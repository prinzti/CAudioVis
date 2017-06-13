/*
 * AbstractVisualizer.h
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#ifndef ABSTRACTVISUALIZER_H_
#define ABSTRACTVISUALIZER_H_

#include "../AbstractVisOutputProcessor.h"
#include "../AudioData.h"

class AbstractVisualizer {
public:
	AbstractVisualizer(int inputSpectrumSize, int samplingRate, AbstractVisOutputProcessor* visOutputProcessor);
	virtual ~AbstractVisualizer();
	virtual void processInputData(AudioProcessingFrameData inputData) = 0;

protected:
	int inputSpectrumSize;
	int samplingRate;
	AbstractVisOutputProcessor* visOutputProcessor;
};

#endif /* ABSTRACTVISUALIZER_H_ */
