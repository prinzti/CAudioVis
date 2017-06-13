/*
 * AudioData.h
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#ifndef AUDIODATA_H_
#define AUDIODATA_H_
#include "fftw3.h"

struct AudioProcessingFrameData{
	int bufferSize;
	unsigned int bitRate;
	float frequencyWidth;
	short* rawData;
	fftwf_complex* spectrum;
	bool isBeatRaw;
	bool isBeatBpmAnalyzer;
};


#endif /* AUDIODATA_H_ */
