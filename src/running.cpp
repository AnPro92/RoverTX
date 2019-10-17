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
#include "running.hpp"
#include <stdint.h>
#include <iostream>
#include <string>
#include <flags.h>

RUNNING::RUNNING() {
	sensors = new SENSORS();
	drive = new DRIVE();
}

RUNNING::~RUNNING() {
}

int RUNNING::checkEscape(char &dir){
    dir=(int)dir;
    if(dir==escape){
        return 1;
    }
    else
        return 0;
}

int RUNNING::checkKeyPressed( ){
	int pressedKey=0; //TODO:replace 0 with getKey of pressed key without enter
#ifdef INCLUDE_DEBUG_STATEMENT
			printf("The symbol with ASCII number %d was pressed\n",pressedKey);
#endif
	if(pressedKey==escape){
		return escape;
	}
	else
		return pressedKey;
}
int RUNNING::checkQuit(){
	if(drive->checkError()||checkKeyPressed())
		return 1;
	else
		return 0;
}

int RUNNING::checkValues(int& direction, int& side, int &speed, int& freq, int& t){
	int check;
	char dir;
    check=scanf("%c %d %d %d %d",&dir,&side, &speed, &freq, &t);
    getchar();
    if(check==5){
    	if(checkEscape(dir))
    		return escape;
    	else{
     	   direction = atoi(&dir); //convert char to integer value
#ifdef INCLUDE_DEBUG_STATEMENT
     	   printf("The converted direction entry is %d",direction);
#endif
     	   printf("%d",direction);
     	   if((direction==0 && dir==48) || direction==1){	//check if direction value and the dir asci value is valide
#ifdef INCLUDE_DEBUG_STATEMENT
       	    printf("Direction:%d Side:%d Speed:%d Frequenz:%d Time:%d",direction,side,speed,freq,t);
#endif
    	    return 1;
     	   }
    	}
    }
    else {
    	if(checkEscape(dir)){
    		return escape;
    	}
    }
	return 0;
}

void RUNNING::stopSensorsRunning(){
	sensors->deinitSensors();
}

int RUNNING::runRemote(){
	int f=sensors->readDistance(front);
	int r =sensors->readDistance(rear);
	if(f > 2 && r >2){	//check if there is still space to move
		//while(!checkQuit()){
			int direction,side, speed, frequenz,t;
			while(((f > NO_ECHO) || (r> NO_ECHO))){	//while at least one sensor delivers a value
				printf("Remote Control via direction side speed frequenz  time, increse speed till 240 and Escape via pressing Esc Esc\t");
				int check = checkValues(direction, side, speed, frequenz,t);	//check valdie sensors values for remote control
#ifdef INCLUDE_DEBUG_STATEMENT
       	    printf("CHeck value for entries is:%d",check);
#endif
				if(check == 1){
					if(drive->remoteControl(direction, side, speed, frequenz,t)){
						f=sensors->readDistance(front);
						r=sensors->readDistance(rear);

					}else
						return 0;
				}
				else if(check==escape){
					printf("remote control is ending now. Default mode is starting now");
					return escape;
				}
				else{
					printf("Please type in the correct format direction = [0-1], side = [0-2] speed=[1-240] and frequenz = number, time = [1-..]");
				}
			}
		//}
	}
}

void RUNNING::runFollow(){
	int f=sensors->readDistance(front);
	int r =sensors->readDistance(rear);
	if(f > 2 && r >2){	//check if there is still space to move
		while(!checkQuit()){	//while no mode changed or escape condition
			while(((f > NO_ECHO) || (r > NO_ECHO))){//while at least one sensor delivers a value
				if(drive->intelligentFollowing(f,r,nospeedchange,defaultFrequenz)){
					f=sensors->readDistance(front);
					r=sensors->readDistance(rear);
				}else
					return;
			}
		}
	}
}

void RUNNING::runEscape(){
	int f=sensors->readDistance(front);
	int r =sensors->readDistance(rear);
	if(f > 2 && r >2){	//check if there is still space to move
		while(!checkQuit()){	//while no mode changed or escape condition
			while(((f > NO_ECHO) || (r> NO_ECHO))){//while at least one sensor delivers a value
				if(drive->intelligentEscaping(f,r,nospeedchange,defaultFrequenz)){
					f=sensors->readDistance(front);
					r=sensors->readDistance(rear);
					printf("Front: %d and Rear %d", f,r);
				}else{
					return;
				}
			}
		}
	}
	drive->stopDriving();
}
