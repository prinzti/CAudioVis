/*
 * FCSVisOutputterInitializer.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: ti
 */

#include "FCSVisOutputterInitializer.h"
#include "SingleColorFCSVisOutputter.h"
#include "MultiColorFCSVisOutputter.h"

FCSVisOutputterInitializer::FCSVisOutputterInitializer() {
}

FCSVisOutputterInitializer::~FCSVisOutputterInitializer() {
}

void FCSVisOutputterInitializer::initVisOutputters(FCSVisOutputterHub* visOutputterHub) {
	printf("FCSVisOutputterInitializer initializing VisOutputters\n");
	initSingleColorVisOutputters(visOutputterHub);
	MultiColorFCSVisOutputter* multiColorFCSVisOutputter = new MultiColorFCSVisOutputter();
	visOutputterHub->registerVisOutputter((AbstractFCSVisOutputter*)multiColorFCSVisOutputter);
	printf("FCSVisOutputterInitializer done initializing VisOutputters\n");
	visOutputterHub->animate();
}

void FCSVisOutputterInitializer::initSingleColorVisOutputters(FCSVisOutputterHub* visOutputterHub) {
	UnitColorConfig colorConfigs[6];
	colorConfigs[0].useRed = true;
	colorConfigs[1].useGreen = true;
	colorConfigs[2].useBlue = true;
	colorConfigs[3].useRed = true;
	colorConfigs[3].useGreen = true;
	colorConfigs[4].useRed = true;
	colorConfigs[4].useBlue = true;
	colorConfigs[5].useGreen = true;
	colorConfigs[5].useBlue = true;

	for (int ccLeftIdx = 0; ccLeftIdx < 6; ccLeftIdx++) {
		for (int ccCenterLeftIdx = 0; ccCenterLeftIdx < 6; ccCenterLeftIdx++) {
			for (int ccCenterRightIdx = 0; ccCenterRightIdx < 6; ccCenterRightIdx++) {
				for (int ccRightIdx = 0; ccRightIdx < 6; ccRightIdx++) {
					for (int ccBottomIdx = 0; ccBottomIdx < 6; ccBottomIdx++) {
						VisOutputColorConfig visOutputterColorConfig;
						visOutputterColorConfig.colorConfigLeft = colorConfigs[ccLeftIdx];
						visOutputterColorConfig.colorConfigCenterLeft = colorConfigs[ccCenterLeftIdx];
						visOutputterColorConfig.colorConfigCenterRight = colorConfigs[ccCenterRightIdx];
						visOutputterColorConfig.colorConfigRight = colorConfigs[ccRightIdx];
						visOutputterColorConfig.colorConfigBottom = colorConfigs[ccBottomIdx];
						SingleColorFCSVisOutputter* visOutputter =
								new SingleColorFCSVisOutputter(visOutputterColorConfig);

						visOutputterHub->registerVisOutputter((AbstractFCSVisOutputter*)visOutputter);
					}
				}
			}
		}
	}
}
