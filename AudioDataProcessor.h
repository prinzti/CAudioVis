/*
 * AudioDataProcessor.h
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#ifndef AUDIODATAPROCESSOR_H_
#define AUDIODATAPROCESSOR_H_
#include "AudioData.h"
#include "onsetsds.h"
#include "fftw3.h"

class AudioDataProcessor {
public:
	AudioDataProcessor(int inputBufferSize, int numBeatDetectionNormalisationSamples, int beatDetectionOdfType, float samplingRate);
	virtual ~AudioDataProcessor();

	void processAudioData(AudioProcessingFrameData* audioData);

private:
	int inputBufferSize;
	int numBeatDetectionNormalisationSamples;
	int beatDetectionOdfType;
	float samplingRate;
	float* windowFunction;
	float* windowedFloatArrayBuffer;
	float* odsDataBuffer;
	fftwf_complex* spectrumBuffer;
	fftwf_plan fftw_plan;
	OnsetsDS ods;

	float* getWindowFunction();
	void inputBufferToWindowedFloatArray(float* target, short* src);
	void initFft();
	void initOnset();
};

#endif /* AUDIODATAPROCESSOR_H_ */
