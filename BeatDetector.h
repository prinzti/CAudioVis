/*
 * BeatDetector.h
 *
 *  Created on: 8 Apr 2017
 *      Author: Matthias
 */

#ifndef BEATDETECTOR_H_
#define BEATDETECTOR_H_

class BeatDetector {
public:
	BeatDetector(int inputSpectrumSize);
	virtual ~BeatDetector();

	void processInputData(float* inputSpectrum);

private:
	int inputSpectrumSize;
};

#endif /* BEATDETECTOR_H_ */
