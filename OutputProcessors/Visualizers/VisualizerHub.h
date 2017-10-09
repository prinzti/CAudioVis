/*
 * VisualizerHub.h
 *
 *  Created on: Oct 9, 2017
 *      Author: ti
 */

#ifndef OUTPUTPROCESSORS_VISUALIZERS_VISUALIZERHUB_H_
#define OUTPUTPROCESSORS_VISUALIZERS_VISUALIZERHUB_H_
#include "../../Util/List.h"
#include "time.h"
#include "AbstractVisualizer.h"

struct VisualizerWithAnimationMetaData {
	AbstractVisualizer* visualizer;
	time_t lastSelectionTime;
	int selectionCount;
};

class VisualizerHub {
public:
	VisualizerHub(int inputSpectrumSize, int samplingRate, AbstractVisOutputProcessor* visOutputProcessor);
	virtual ~VisualizerHub();
	void processInputData(AudioProcessingFrameData inputData);

protected:
	static const float maxTimeBetweenAnimations = 30;
	static const int beatsBetweenAnimations = 32;
	static const int maxWeight = 50;
	void initializeVisualizers();
	void animate();
	void registerVisualizer(AbstractVisualizer* visualizer);
	int getSelectionProbabilityWeight(VisualizerWithAnimationMetaData* visualizerWithAnimationMetaData);

	int inputSpectrumSize;
	int samplingRate;

	AbstractVisOutputProcessor* visOutputProcessor;
	AbstractVisualizer* currentlySelectedVisualizer;
	List visualizerList;
	time_t timeOfLastAnimation;
	int beatCounter;
	int totalSelectionCount;
};

#endif /* OUTPUTPROCESSORS_VISUALIZERS_VISUALIZERHUB_H_ */
