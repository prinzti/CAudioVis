/*
 * ConsoleVisOutputProcessor.cpp
 *
 *  Created on: Apr 15, 2017
 *      Author: ti
 */

#include "GpioVisOutputProcessor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <wiringPi.h>

GpioVisOutputProcessor::GpioVisOutputProcessor() {
	if (wiringPiSetup() == -1) {
		printf("Error: Could not init wiringPi");
	} else {
		initPins();
	}
}

GpioVisOutputProcessor::~GpioVisOutputProcessor() {
}

void GpioVisOutputProcessor::processVisOutput(VisOutputData visOutputData) {
	digitalWrite(15, boolToInt(visOutputData.left.red));
	digitalWrite(7, boolToInt(visOutputData.left.green));
	digitalWrite(16, boolToInt(visOutputData.left.blue));
	digitalWrite(2, boolToInt(visOutputData.centerLeft.red));
	digitalWrite(0, boolToInt(visOutputData.centerLeft.green));
	digitalWrite(1, boolToInt(visOutputData.centerLeft.blue));
	digitalWrite(13, boolToInt(visOutputData.centerRight.red));
	digitalWrite(12, boolToInt(visOutputData.centerRight.green));
	digitalWrite(6, boolToInt(visOutputData.centerRight.blue));
	digitalWrite(10, boolToInt(visOutputData.right.red));
	digitalWrite(14, boolToInt(visOutputData.right.green));
	digitalWrite(11, boolToInt(visOutputData.right.blue));
	digitalWrite(4, boolToInt(visOutputData.bottom.red));
	digitalWrite(3, boolToInt(visOutputData.bottom.green));
	digitalWrite(5, boolToInt(visOutputData.bottom.blue));
}

int GpioVisOutputProcessor::boolToInt(bool boolValue) {
	return boolValue ? 1 : 0;
}

void GpioVisOutputProcessor::initPins() {
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(14, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);
}
