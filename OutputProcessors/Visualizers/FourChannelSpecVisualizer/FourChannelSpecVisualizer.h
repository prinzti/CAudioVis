/*
 * FourChannelSpecVisualizer.h
 *
 *  Created on: 15 Apr 2017
 *      Author: Matthias
 */

#ifndef FOURCHANNELSPECVISUALIZER_H_
#define FOURCHANNELSPECVISUALIZER_H_

#include "../AbstractVisualizer.h"
#include "../../../Data/SimpleValueHistory.h"
#include "FCSVisOutputterHub.h"
#include "time.h"

const int numChannels = 4;
const int minSpectrumAmplitudeHistoryLength = 10;
const int maxSpectrumAmplitudeHistoryLength = 10;
const int channelAverageHistoryLength = 20;
const float maxTimeBetweenAnimations = 30;
const int beatsBetweenAnimations = 32;

class FourChannelSpecVisualizer: public AbstractVisualizer {
public:
	FourChannelSpecVisualizer(int inputSpectrumSize, int samplingrate, AbstractVisOutputProcessor* visOutputProcessor);
	virtual ~FourChannelSpecVisualizer();
	void processInputData(AudioProcessingFrameData inputSpectrum);

protected:
	int* powerSpectrumBarIndexByBinIndex;
	int* numBinsByBarIndex;
	float* powerSpectrum;
	float linearCorrectionFactor;
	SimpleValueHistory<float>* minSpectrumAmplitudeHistory;
	SimpleValueHistory<float>* maxSpectrumAmplitudeHistory;
	SimpleValueHistory<float>* channelAverageHistory;
	int animationIndexGlobal;
	int animationIndexPerChannel[numChannels];
	int beatCounter;
	time_t timeOfLastAnimation;
	FCSVisOutputterHub visOutputterHub;

	void createPowerSpectrumBarIndexByBinIndex();
	void powerSpectrumToBars(float** barsOutput);
	void calculatePowerSpectrumFromDftData(AudioProcessingFrameData inputData);
	void initVisOutputters();

};

#endif /* FOURCHANNELSPECVISUALIZER_H_ */
