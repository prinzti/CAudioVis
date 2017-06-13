/*
 * AudioInputter.h
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#ifndef AUDIOINPUTTER_H_
#define AUDIOINPUTTER_H_
#define __c_plus_plus
#include <alsa/asoundlib.h>
#include "AudioData.h"


class AudioInputter {
public:
	AudioInputter(const char* deviceName, unsigned int* targetBitrate);
	virtual ~AudioInputter();

	int readStream(AudioProcessingFrameData* targetAudioData, int numFrames);

private:
	snd_pcm_t* getCaptureHandle(const char* deviceName, unsigned int* targetBitrate);
	void handleError(int returnCode);

	snd_pcm_t* captureHandle;

	unsigned int samplingRate;
};

#endif /* AUDIOINPUTTER_H_ */
