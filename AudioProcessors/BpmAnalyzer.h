/*
 * BpmAnalyzer.h
 *
 *  Created on: Jun 13, 2017
 *      Author: ti
 */

#ifndef BPMANALYZER_H_
#define BPMANALYZER_H_

#include "../Data/AudioProcessingFrameData.h"

class BpmAnalyzer {
public:
	BpmAnalyzer();
	virtual ~BpmAnalyzer();

	void postProcessAudioData(AudioProcessingFrameData* audioData);

protected:

};

#endif /* BPMANALYZER_H_ */
