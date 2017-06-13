/*
 * AudioInputter.cpp
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#include "AudioInputter.h"
#include <iostream>
#include <stdio.h>

AudioInputter::AudioInputter(const char* deviceName, unsigned int* targetSamplingrate) {
	this->captureHandle = getCaptureHandle(deviceName, targetSamplingrate);
	handleError(snd_pcm_prepare(this->captureHandle));
	this->samplingRate = *targetSamplingrate;
}

AudioInputter::~AudioInputter() {
	snd_pcm_close(captureHandle);
}

int AudioInputter::readStream(AudioProcessingFrameData* targetAudioData, int numFrames) {
	targetAudioData->bitRate = samplingRate;
	int framesRead = snd_pcm_readi(this->captureHandle, targetAudioData->rawData, numFrames);
	//printf("read %d samples\n", framesRead);
	targetAudioData->bufferSize = framesRead;
	return framesRead;
}

snd_pcm_t* AudioInputter::getCaptureHandle(const char* deviceName, unsigned int* targetSamplingRate) {
   snd_pcm_hw_params_t* hw_params;
   snd_pcm_t* capture_handle;

   fprintf(stdout, "open device\n");
   handleError(snd_pcm_open(&capture_handle, deviceName, SND_PCM_STREAM_CAPTURE, 0));
   fprintf(stdout, "mallow hw_parms\n");
   handleError(snd_pcm_hw_params_malloc( &hw_params));
   fprintf(stdout, "init capture handle\n");
   handleError(snd_pcm_hw_params_any(capture_handle, hw_params));
   fprintf(stdout, "set access\n");
   handleError(snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED));
   fprintf(stdout, "set format\n");
   handleError(snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE));
   fprintf(stdout, "set bitrate..\n");
   handleError(snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, targetSamplingRate, NULL));
   printf("bitrate: %d\n", *targetSamplingRate);
   fprintf(stdout, "set channels\n");
   handleError(snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2));
   fprintf(stdout, "set hw_parms on capture_handle\n");
   handleError(snd_pcm_hw_params(capture_handle, hw_params));
   fprintf(stdout, "free hw_parms\n");
   snd_pcm_hw_params_free(hw_params);
   return capture_handle;
}

void AudioInputter::handleError(int returnCode) {
   if (returnCode < 0){
       fprintf (stderr, "error occured: %s\n", snd_strerror(returnCode));
       exit(1);
   }
}
