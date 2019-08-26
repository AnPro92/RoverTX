/*******************************************************************************
 * Copyright (c) 2019 Dortmund University of Applied Sciences and Arts and others.
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 *  
 * Contributors:
 * 	Dortmund University of Applied Sciences and Arts - initial API and implementation
 *******************************************************************************/
#include <stdio.h>
#include "controller.hpp"
using namespace std;



CONTROLLER::CONTROLLER() {
	mode = remoteControl;
	running = new RUNNING();
}
CONTROLLER::~CONTROLLER() {
}


int CONTROLLER::waiting(){
	int check;
	while((check=checkModeChange())!=reenter){
		if(check==escape)
			return escape;
	}return reenter;
}

int CONTROLLER::checkModeChange(){
	int modeX = mode;//TODO:replace mode with keyPress value without enter
	if(modeX == 'R'){	//R
		mode = remoteControl;
		printf("Entering mode: %d \n", mode);
	}
	else if(modeX == 69){ //E
		printf("Entering mode: %d \n", mode);
		mode = sensorsEscaping;
	}
	else if(modeX == 70){ //F
		mode = sensorFollowing;
		printf("Entering mode: %d \n", mode);
	}
	else if(modeX==escape){//Escape
		return 27;
	}
	else if (modeX == reenter)//space bar
		return 32;
	return mode;
}

int CONTROLLER::runningMode(){
	if(mode == remoteControl){
		if(running->runRemote()==escape)
			return escape;
	}
	else if(mode ==sensorsEscaping){
		running->runEscape();
	}
	else if(mode ==sensorFollowing){
		running->runFollow();
	}
	return 1;
}

void CONTROLLER::run(){
	printf("Press Esc to quit, r for Remote Control(3) ,e for change mode for Follow mode(1). Default mode is now Escaping() \n");
	while(true){
		if(checkModeChange()!=escape){
			if(runningMode()==escape)
				mode =defaultRunnungMode;
		}
		else{
			//running->stopRunning();
			printf("Stopped Application with ESC, press space bar to restart");
			if(waiting()==reenter);
			else
				return;
		}
	}
}
