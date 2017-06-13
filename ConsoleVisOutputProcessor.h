/*
 * ConsoleVisOutputProcessor.h
 *
 *  Created on: Apr 15, 2017
 *      Author: ti
 */

#ifndef CONSOLEVISOUTPUTPROCESSOR_H_
#define CONSOLEVISOUTPUTPROCESSOR_H_

#include "AbstractVisOutputProcessor.h"

class ConsoleVisOutputProcessor: public AbstractVisOutputProcessor {
public:
	ConsoleVisOutputProcessor();
	virtual ~ConsoleVisOutputProcessor();

	void processVisOutput(VisOutputData visOutputData);
protected:
	int unitDataToConsoleOutput(char* targetBuffer, int visLength, UnitData unitData);
	int unitDataToColor(UnitData unitData);
};

#endif /* CONSOLEVISOUTPUTPROCESSOR_H_ */
