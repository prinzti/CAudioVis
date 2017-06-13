/*
 * GpioVisOutputProcessor.h
 *
 *  Created on: Apr 15, 2017
 *      Author: ti
 */

#ifndef GPIOVISOUTPUTPROCESSOR_H_
#define GPIOVISOUTPUTPROCESSOR_H_

#include "AbstractVisOutputProcessor.h"

class GpioVisOutputProcessor: public AbstractVisOutputProcessor {
public:
	GpioVisOutputProcessor();
	virtual ~GpioVisOutputProcessor();

	void processVisOutput(VisOutputData visOutputData);
protected:
	void initPins();
	int boolToInt(bool boolValue);
};

#endif /* GPIOVISOUTPUTPROCESSOR_H_ */
