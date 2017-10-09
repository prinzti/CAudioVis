/*
 * AbstractVisualizer.h
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#ifndef ABSTRACTVISUALIZER_H_
#define ABSTRACTVISUALIZER_H_

#include "../../Data/AudioProcessingFrameData.h"
#include "../AbstractVisOutputProcessor.h"

class AbstractVisualizer {
public:
	AbstractVisualizer(int inputSpectrumSize, int samplingRate, AbstractVisOutputProcessor* visOutputProcessor);
	virtual ~AbstractVisualizer();
	virtual void processInputData(AudioProcessingFrameData inputData) = 0;
	float calcVisualizerHubSelectionProbabilityWeight();

protected:
	VisOutputData prepareVisOutputData(AudioProcessingFrameData inputData);

	int inputSpectrumSize;
	int samplingRate;
	AbstractVisOutputProcessor* visOutputProcessor;
};

#endif /* ABSTRACTVISUALIZER_H_ */
