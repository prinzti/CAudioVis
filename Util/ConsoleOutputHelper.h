/*
 * ConsoleOutputHelper.h
 *
 *  Created on: Jun 13, 2017
 *      Author: ti
 */

#ifndef CONSOLEOUTPUTHELPER_H_
#define CONSOLEOUTPUTHELPER_H_

class ConsoleOutputHelper {
public:
	ConsoleOutputHelper();
	virtual ~ConsoleOutputHelper();

	static void printArrayOfFloats(int lengthOfarray, float* data) {
		char* string = new char[lengthOfarray*10];
		int lengthOfString = 0;
		memset(string, 0, 6 * lengthOfarray + 2);
		for (int i = 0; i < lengthOfarray; i++) {
			lengthOfString += sprintf(&(string[lengthOfString]), "%4.2f ", data[i]);
		}
		lengthOfString += sprintf(&(string[lengthOfString]), "\n");
		printf(string);
		delete[] string;
	}

	static void printArrayOfInts(int lengthOfarray, int* data) {
		char* string = new char[lengthOfarray*10];
		int lengthOfString = 0;
		memset(string, 0, 6 * lengthOfarray + 2);
		for (int i = 0; i < lengthOfarray; i++) {
			lengthOfString += sprintf(&(string[lengthOfString]), "%i ", data[i]);
		}
		lengthOfString += sprintf(&(string[lengthOfString]), "\n");
		printf(string);
		delete[] string;
	}

	static void printArrayOfShorts(int lengthOfarray,short * data) {
		char* string = new char[lengthOfarray*10];
		int lengthOfString = 0;
		printf("printing %d shorts...\n", lengthOfarray);
		memset(string, 0, 6 * lengthOfarray + 2);
		for (int i = 0; i < lengthOfarray; i++) {
			lengthOfString += sprintf(&(string[lengthOfString]), "%d ", (int)data[2*i]);
		}
		lengthOfString += sprintf(&(string[lengthOfString]), "\n");
		printf(string);
		delete[] string;
	}
};

#endif /* CONSOLEOUTPUTHELPER_H_ */
