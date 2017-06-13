#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "AudioInputter.h"
#include "AudioDataProcessor.h"
#include "ConsoleVisOutputProcessor.h"
#include "GpioVisOutputProcessor.h"
#include "Visualizers/FourChannelSpecVisualizer/FourChannelSpecVisualizer.h"

using namespace std;

void recordAndProcess(char* captureDevice, char* parmN, char* parmS, char* parmDetectionFunction);

int main(int argc, char* argv[]) {
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
   FourChannelSpecVisualizer* fourChannelSpecVisualizer = new FourChannelSpecVisualizer(N, samplingRate, visOutputProcessor);
   short* audioRawBuffer = new short[N*2];
   int framesRead = 1;

   printf("\n\n");
   while (framesRead > 0) {
	   AudioProcessingFrameData audioFrameData;
	   audioFrameData.rawData = audioRawBuffer;
	   framesRead = audioInputter->readStream(&audioFrameData, N);
	   audioDataProcessor->processAudioData(&audioFrameData);
	   fourChannelSpecVisualizer->processInputData(audioFrameData);

       fflush(stdout);

   }
   delete visOutputProcessor;
   delete fourChannelSpecVisualizer;
   exit(0);
   
}


