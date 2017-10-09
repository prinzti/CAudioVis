#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "AudioInputter.h"
#include "AudioProcessors/AudioDataProcessor.h"
#include "OutputProcessors/ConsoleVisOutputProcessor.h"
#include "OutputProcessors/GpioVisOutputProcessor.h"
#include "OutputProcessors/Visualizers/VisualizerHub.h"

using namespace std;

void recordAndProcess(char* captureDevice, char* parmN, char* parmS, char* parmDetectionFunction);

int main(int argc, char* argv[]) {
	srand(time(NULL));
	recordAndProcess(argv[1], argv[2], argv[3], argv[4]);
	return 0;
}

void recordAndProcess(char* captureDevice, char* parmN, char* parmS, char* parmDetectionFunction) {
   int N = 1024;
   int S = 11;
   int detectionFunction;
   std::istringstream(parmN) >> N;
   std::istringstream(parmS) >> S;
   std::istringstream(parmDetectionFunction) >> detectionFunction;
   printf("Starting with numSamples=%d, onSet-SamplingHistorySize=%d, detectionFunction=%d\n", N, S, detectionFunction);
   unsigned int samplingRate = 44100;
   AudioInputter* audioInputter = new AudioInputter(captureDevice, &samplingRate);
   AudioDataProcessor* audioDataProcessor = new AudioDataProcessor(N, S, detectionFunction, (float)samplingRate);
   AbstractVisOutputProcessor* visOutputProcessor = new ConsoleVisOutputProcessor();
   //AbstractVisOutputProcessor* visOutputProcessor = new GpioVisOutputProcessor();
   VisualizerHub* visualizerHub = new VisualizerHub(N, samplingRate, visOutputProcessor);
   short* audioRawBuffer = new short[N*2];
   int framesRead = 1;

   printf("\n\n");
   while (framesRead > 0) {
	   AudioProcessingFrameData audioFrameData;
	   audioFrameData.rawData = audioRawBuffer;
	   framesRead = audioInputter->readStream(&audioFrameData, N);
	   audioDataProcessor->processAudioData(&audioFrameData);
	   visualizerHub->processInputData(audioFrameData);

       fflush(stdout);

   }
   delete visOutputProcessor;
   delete visualizerHub;
   exit(0);
   
}


