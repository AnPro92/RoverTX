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
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <jetsonGPIO.h>
#include "drive.hpp"
#include <stdint.h>
#include "sensors.hpp"
#include <flags.h>

SENSORS::SENSORS() {
	hcsr04Front = new HCSR04(gpio37,gpio31);
	hcsr04Rear = new HCSR04(gpio13, gpio12);
//	usr_button = gpio23;
//	shutdown_button = gpio24;
	initSensors();
//	initButtons();
}

SENSORS::~SENSORS() {
}


void SENSORS::initSensors(){
    hcsr04Front->unexportGPIO();
    hcsr04Rear->unexportGPIO();
    // Make the HC-SR04s available in user space
    hcsr04Front->exportGPIO() ;
    hcsr04Rear->exportGPIO() ;
    // Then set the direction of the pins
    hcsr04Front->setDirection() ;
    hcsr04Rear->setDirection() ;
}

void SENSORS::deinitSensors(){
	hcsr04Front->unexportGPIO();
	hcsr04Rear->unexportGPIO();
}

void SENSORS::initButtons(jetsonGPIO gpio){
	gpioUnexport(gpio);
	gpioExport(gpio);
	gpioSetDirection(gpio, inputPin);
}

int SENSORS::readButtons(jetsonGPIO gpio){
    initButtons(gpio);
	unsigned int value;
	gpioGetValue(gpio, &value);
	gpioUnexport(gpio);
	return value;
}

int SENSORS::readDistance(char sensor){
	HCSR04 *hcsr;//=hcsr04Front;
	if(sensor == 'F')
		hcsr=hcsr04Front;
	else if (sensor == 'R')
		hcsr=hcsr04Rear;
	if (hcsr != NULL){
		unsigned int echoTime = hcsr->pingMedian(10);
		if (echoTime == NO_ECHO) {
		  return NO_ECHO;//cout << " No echo" << endl ;
		}
		else {
			int range = echoTime/58.0;
#ifdef INCLUDE_DEBUG_STATEMENT
			printf("%c Sensor %d cm  and echoTime: %d\t",sensor,range, echechoTime);
#endif
			return range;
		}
	}
}
