/*
 * FCSVisOutputterHub.h
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#ifndef VISUALIZERS_FOURCHANNELSPECVISUALIZER_FCSVISOUTPUTTERHUB_H_
#define VISUALIZERS_FOURCHANNELSPECVISUALIZER_FCSVISOUTPUTTERHUB_H_

#include "../../../Data/AudioData.h"
#include "../../../Data/VisOutputData.h"
#include "AbstractFCSVisOutputter.h"
#include <list>

class FCSVisOutputterHub {
public:
	FCSVisOutputterHub();
	virtual ~FCSVisOutputterHub();

	void processAudioData(AudioProcessingFrameData audioData, float* fcsBars, VisOutputData* targetVisOutputData);
	void animate();

	void registerVisOutputter( AbstractFCSVisOutputter* visOutputter );
	void deregisterVisOutputter( AbstractFCSVisOutputter* visOutputter );


private:
	std::list<AbstractFCSVisOutputter*> registeredVisOutputters;
	std::list<AbstractFCSVisOutputter*>::iterator currentVisOutputter;
};

#endif /* VISUALIZERS_FOURCHANNELSPECVISUALIZER_FCSVISOUTPUTTERHUB_H_ */
