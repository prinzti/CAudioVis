/*
 * ConsoleVisOutputProcessor.cpp
 *
 *  Created on: Apr 15, 2017
 *      Author: ti
 */

#include "ConsoleVisOutputProcessor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

ConsoleVisOutputProcessor::ConsoleVisOutputProcessor() {
}

ConsoleVisOutputProcessor::~ConsoleVisOutputProcessor() {
}

void ConsoleVisOutputProcessor::processVisOutput(VisOutputData visOutputData) {
	char* buffer = new char[500];
	int charsWritten = 0;
	charsWritten += sprintf(buffer, "\033[F");
	charsWritten += unitDataToConsoleOutput(&(buffer[charsWritten]), 2, visOutputData.left);
	charsWritten += unitDataToConsoleOutput(&(buffer[charsWritten]), 2, visOutputData.centerLeft);
	charsWritten += unitDataToConsoleOutput(&(buffer[charsWritten]), 2, visOutputData.centerRight);
	charsWritten += unitDataToConsoleOutput(&(buffer[charsWritten]), 2, visOutputData.right);
	buffer[charsWritten] = '\n';
	charsWritten++;
	charsWritten += unitDataToConsoleOutput(&(buffer[charsWritten]), 14, visOutputData.bottom);
	charsWritten += sprintf(&(buffer[charsWritten]), " current BPM: %2.1f", visOutputData.metaData.currentBpm);
	fprintf(stdout, buffer);

}

int ConsoleVisOutputProcessor::unitDataToConsoleOutput(char* targetBuffer,
		int visLength, UnitData unitData) {
	int charsWritten = 0;
	charsWritten = sprintf(targetBuffer, "!\033[%02dm", 30 + unitDataToColor(unitData));
	if (unitData.red || unitData.blue || unitData.green) {
		for (int i = 0; i < visLength; i++) {
			(targetBuffer)[charsWritten] = 'O';
			charsWritten++;
		}
	} else {
		for (int i = 0; i < visLength; i++) {
			(targetBuffer)[charsWritten] = ' ';
			charsWritten++;
		}
	}
	charsWritten += sprintf(targetBuffer + charsWritten, "\033[0m!");
	return charsWritten;
}

int ConsoleVisOutputProcessor::unitDataToColor(UnitData unitData) {
	if (!unitData.red && !unitData.blue && unitData.green) {
		return 2;
	} else if (!unitData.red && unitData.blue && !unitData.green) {
		return 4;
	} else if (!unitData.red && unitData.blue && unitData.green) {
		return 6;
	} else if (unitData.red && !unitData.blue && !unitData.green) {
		return 1;
	} else if (unitData.red && !unitData.blue && unitData.green) {
		return 3;
	} else if (unitData.red && unitData.blue && !unitData.green) {
		return 5;
	} else if (unitData.red && unitData.blue && unitData.green) {
		return 7;
	} else {
		return 0;
	}
}
