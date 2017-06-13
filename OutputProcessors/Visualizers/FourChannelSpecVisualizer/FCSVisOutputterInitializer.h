/*
 * FCSVisOutputterInitializer.h
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#ifndef VISUALIZERS_FOURCHANNELSPECVISUALIZER_FCSVISOUTPUTTERINITIALIZER_H_
#define VISUALIZERS_FOURCHANNELSPECVISUALIZER_FCSVISOUTPUTTERINITIALIZER_H_

#include "FCSVisOutputterHub.h"

class FCSVisOutputterInitializer {
public:
	FCSVisOutputterInitializer();
	virtual ~FCSVisOutputterInitializer();

	void initVisOutputters(FCSVisOutputterHub* visOutputterHub);
private:
	void initSingleColorVisOutputters(FCSVisOutputterHub* visOutputterHub);
};

#endif /* VISUALIZERS_FOURCHANNELSPECVISUALIZER_FCSVISOUTPUTTERINITIALIZER_H_ */
