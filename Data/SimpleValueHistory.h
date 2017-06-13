/*
 * SimpleValueHistory.h
 *
 *  Created on: Apr 16, 2017
 *      Author: ti
 */

#ifndef SIMPLEVALUEHISTORY_H_
#define SIMPLEVALUEHISTORY_H_

#include <cstring>
#include <algorithm>

template <typename T> class SimpleValueHistory {
public:
	SimpleValueHistory(int numEntries, T defaultValue) {
		this->values = new T[numEntries];
		this->numEntries = numEntries;
		this->defaultValue = defaultValue;
		memset(this->values, defaultValue, numEntries*sizeof(T));
		this->currentIdx = 0;
	}
	~SimpleValueHistory() {
		if (this->values) {
			delete[] this->values;
		}
	}

	void addElement(T value) {
		this->currentIdx++;
		if (this->currentIdx >= this->numEntries) {
			this->currentIdx = 0;
		}
		this->values[this->currentIdx] = value;
	}

	T* getValues() {
		return this->values;
	}

	T getAverage() {
		T average = this->defaultValue;
		int numEntriesAdded = 0;
		for (int idx = 0; idx < this->numEntries; idx++) {
			if (this->values[idx] != this->defaultValue) {
				average += this->values[idx];
				numEntriesAdded++;
			}
		}

		if (numEntriesAdded > 0) {
			average /= (T)numEntriesAdded;
		}
		return average;
	}

	void getLastNNonDefaultEntries(int N, T** targetBuffer, int* numValuesReturned) {
		if (N > this->numEntries) {
			N = this->numEntries;
		}
		T* lastNEntries = new T[N];
		*numValuesReturned = 0;
		int numValuesChecked = 0;
		int currentIdxToCheck = this->currentIdx;
		while ((*numValuesReturned) < N && numValuesChecked < this->numEntries) {
			if (this->values[currentIdxToCheck] != this->defaultValue) {
				lastNEntries[*numValuesReturned] = this->values[currentIdxToCheck];
				(*numValuesReturned)++;
			}
			currentIdxToCheck--;
			numValuesChecked++;
			if (currentIdxToCheck < 0) {
				currentIdxToCheck += this->numEntries;
			}
		}
		(*targetBuffer) = new T[*numValuesReturned];
		memcpy(*targetBuffer, lastNEntries, (*numValuesReturned)*sizeof(T));
		delete[] lastNEntries;
	}

	int getCapacity() {
		return this->numEntries;
	}

	T getDefaultValue() {
		return defaultValue;
	}

private:
	T* values;
	T defaultValue;
	int currentIdx;
	int numEntries;
};

#endif /* SIMPLEVALUEHISTORY_H_ */
