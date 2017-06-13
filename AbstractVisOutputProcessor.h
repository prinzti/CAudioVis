/*
 * VisOutputProcessor.h
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#ifndef ABSTRACTVISOUTPUTPROCESSOR_H_
#define ABSTRACTVISOUTPUTPROCESSOR_H_

#include "VisOutputData.h"

class AbstractVisOutputProcessor {
public:
	AbstractVisOutputProcessor();
	virtual ~AbstractVisOutputProcessor();

	virtual void processVisOutput(VisOutputData visOutputData) = 0;
};

#endif /* ABSTRACTVISOUTPUTPROCESSOR_H_ */
