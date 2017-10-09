/*
 * List.h
 *
 *  Created on: Oct 9, 2017
 *      Author: ti
 */

#ifndef UTIL_LIST_H_
#define UTIL_LIST_H_
#include <cstring>

class List {
public:
	List() {
		numEntries = 0;
		numEntriesAllocated = 0;
		allocateArray(8);
	}
	~List() {
		delete[] contentArray;
	}

	void addElement(void* element) {
		if (numEntries + 1 > numEntriesAllocated) {
			reallocateArray(arrayResizingSize());
		}
		memcpy(&(contentArray[numEntries*elementSize]), element, elementSize);
		numEntries++;
	}

	void* getElementAt(int index) {
		void** dataPointer = (void**)&(contentArray[numEntries*elementSize]);
		return *dataPointer;
	}

	void removeElementAt(int index) {
		if (numEntries == 0 || index >= numEntries) {
			return;
		}
		if (numEntries > 1) {
			memcpy(&(contentArray[index*elementSize]), &(contentArray[(index+1)*elementSize]),(numEntries-index-1)*elementSize);
		}
		numEntries--;
	}

	void removeElement(void* element) {
		for (int i = 0; i < numEntries; i++) {
			void* currentElement = getElementAt(i);
			if (currentElement == element) {
				removeElementAt(i);
				return;
			}
		}
	}

	void** getAsArray() {
		return (void**)&contentArray;
	}

	int getNumberOfElements() {
		return numEntries;
	}

protected:
	int numEntries;
	int numEntriesAllocated;
	static const int elementSize = sizeof(void*);
	void** contentArray;

	int arrayResizingSize() {
		return numEntriesAllocated * 2;
	}

	void reallocateArray(int newSize) {
		void** oldArray = contentArray;
		allocateArray(newSize);
		if (oldArray != 0) {
			memcpy(contentArray, oldArray, numEntries*elementSize);
			delete[] oldArray;
		}
	}

	void allocateArray(int size) {
		contentArray = (void**)(new char[size*elementSize]);
		numEntriesAllocated = size;
	}
};

#endif /* UTIL_LIST_H_ */
