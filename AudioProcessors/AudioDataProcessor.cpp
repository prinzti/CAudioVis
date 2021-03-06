/*
 * AudioDataProcessor.cpp
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#include "AudioDataProcessor.h"

#include <stdio.h>
#include <stdlib.h>

AudioDataProcessor::AudioDataProcessor(int inputBufferSize, int numBeatDetectionNormalisationSamples, int beatDetectionOdfType, float samplingRate) {
	this->inputBufferSize = inputBufferSize;
	this->samplingRate = samplingRate;
	this->windowedFloatArrayBuffer = new float[inputBufferSize];
	this->windowedDoubleArrayBuffer = new double[inputBufferSize];
	this->spectrumBuffer = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * inputBufferSize);
	this->numBeatDetectionNormalisationSamples = numBeatDetectionNormalisationSamples;
	this->beatDetectionOdfType = beatDetectionOdfType;
	this->odsDataBuffer = (float*) malloc(onsetsds_memneeded(beatDetectionOdfType, inputBufferSize, numBeatDetectionNormalisationSamples));
	this->windowFunction = getWindowFunction();
	initFft();
	initOnset();
	initBTrack();
	this->bpmAnalyzer = new BpmAnalyzer;
}

AudioDataProcessor::~AudioDataProcessor() {
	if (windowFunction) {
		delete[] windowFunction;
	}
	if (windowedFloatArrayBuffer) {
		fftwf_free(windowedFloatArrayBuffer);
	}
	if (windowedDoubleArrayBuffer) {
		fftwf_free(windowedDoubleArrayBuffer);
	}
	if (odsDataBuffer) {
		delete[] odsDataBuffer;
	}
	if (bpmAnalyzer) {
		delete bpmAnalyzer;
	}
}

void AudioDataProcessor::processAudioData(AudioProcessingFrameData* audioData) {
	inputBufferToWindowedFloatAndDoubleArray(windowedFloatArrayBuffer, windowedDoubleArrayBuffer, audioData->rawData);
	fftwf_execute(fftw_plan);
	//bool onset = onsetsds_process(&ods, (float*)spectrumBuffer);
	bTrack->processAudioFrame(windowedDoubleArrayBuffer);
	audioData->currentBpm = bTrack->getCurrentTempoEstimate();

	float maxSpectrumFrequency = ((float)audioData->bitRate)/2.0f;
	audioData->frequencyWidth = 2*maxSpectrumFrequency / ((float)inputBufferSize);
	audioData->isBeatRaw = bTrack->beatDueInCurrentFrame();
	audioData->isBeatBpmAnalyzer = audioData->isBeatRaw;
	audioData->spectrum = spectrumBuffer;
	/*if (bpmAnalyzer) {
		bpmAnalyzer->postProcessAudioData(audioData);
	}*/
}

void AudioDataProcessor::inputBufferToWindowedFloatAndDoubleArray(float* fTarget, double* dTarget, short* src) {
	for (int i = 0; i < inputBufferSize; i++) {
		dTarget[i] = ((double) src[2*i]) / 65535.0;
		fTarget[i] = (float) windowFunction[i] * dTarget[i];
	}
}

float* AudioDataProcessor::getWindowFunction() {
	float* windowFunction = new float[inputBufferSize];
	double pi = acos(-1.);
	double winc = pi / (double) inputBufferSize;
	int i;
	for (i = 0; i < inputBufferSize; ++i) {
		double w = i * winc;
		windowFunction[i] = sin(w);
	}
	return windowFunction;
}

void AudioDataProcessor::initFft() {
	fftw_plan = fftwf_plan_dft_r2c_1d(inputBufferSize, windowedFloatArrayBuffer, spectrumBuffer, FFTW_ESTIMATE);
}

void AudioDataProcessor::initOnset() {
	/**ODS_ODF_POWER, ODS_ODF_MAGSUM, ODS_ODF_COMPLEX, ODS_ODF_RCOMPLEX, ODS_ODF_PHASE, ODS_ODF_WPHASE, ODS_ODF_MKL **/
	ods.odftype = beatDetectionOdfType;
	onsetsds_init(&ods, odsDataBuffer, ODS_FFT_FFTW3_R2C, ods.odftype, inputBufferSize, numBeatDetectionNormalisationSamples, samplingRate);
}

void AudioDataProcessor::initBTrack() {
	bTrack = new BTrack(inputBufferSize, inputBufferSize);
}

