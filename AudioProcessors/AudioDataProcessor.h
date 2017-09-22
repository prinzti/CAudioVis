/*
 * AudioDataProcessor.h
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#ifndef AUDIODATAPROCESSOR_H_
#define AUDIODATAPROCESSOR_H_
#include "../Data/AudioProcessingFrameData.h"
#include "../onsetsds.h"
#include "../fftw3.h"
#include "BpmAnalyzer.h"
#include "../BTrack/BTrack.h"

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
	double* windowedDoubleArrayBuffer;
	float* odsDataBuffer;
	fftwf_complex* spectrumBuffer;
	fftwf_plan fftw_plan;
	OnsetsDS ods;
	BpmAnalyzer* bpmAnalyzer;
	BTrack* bTrack;

	float* getWindowFunction();
	void inputBufferToWindowedFloatAndDoubleArray(float* fTarget, double* dTarget, short* src);
	void initFft();
	void initOnset();
	void initBTrack();
};

#endif /* AUDIODATAPROCESSOR_H_ */
