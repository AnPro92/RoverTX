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
#include <iostream>
#include <jetsonGPIO.h>
#include "motorShield.hpp"
#include <flags.h>


MOTORSHIELD::MOTORSHIELD() {
    enableMotors =  enable_motor;
    leftDirection = left_motor_direction;
    rightDirection = right_motor_direction;
    pwmDriver = new PCA9685();
    buzzer = buzzer_signal;
    motorState = 0;
}

MOTORSHIELD::~MOTORSHIELD() {
}


void MOTORSHIELD::setUsedGPIOS ( void ) {
    gpioExport(leftDirection);
    gpioExport(rightDirection);
    gpioExport(enableMotors);
    gpioExport(buzzer);
    gpioSetDirection(enableMotors,outputPin) ;
    gpioSetDirection(leftDirection,outputPin) ;
    gpioSetDirection(rightDirection,outputPin) ;
    gpioSetDirection(buzzer,outputPin) ;
}

void MOTORSHIELD::unsetUsedGPIOS ( void ) {
    gpioUnexport(enableMotors);
    gpioUnexport(leftDirection);
    gpioUnexport(rightDirection);
    gpioUnexport(buzzer);
}

void MOTORSHIELD::activateMotors(void){
	unsetUsedGPIOS();
	setUsedGPIOS();
	initPwmDriver();
}

void MOTORSHIELD::initPwmDriver(void){
    int err = pwmDriver->openPCA9685();
#ifdef INCLUDE_DEBUG_STATEMENT
    if (err < 0){
        printf("Error: %d", pwmDriver->error);
    }
	printf("PCA9685 Device Address: 0x%02X\n",pwmDriver->kI2CAddress) ;
#endif
	pwmDriver->setAllPWM(0,0) ;
	pwmDriver->reset() ;
}


void MOTORSHIELD::deactivateMotors(void){
	unsetUsedGPIOS();
	pwmDriver->closePCA9685();
}

void MOTORSHIELD::stopMoving(void){
	gpioSetValue(left_motor_direction,drive_backward);
	gpioSetValue(right_motor_direction,drive_backward);
	pwmDriver->setAllPWM(0,0);	//minimum pwm signal in rear direction results no movement
}

int MOTORSHIELD::checkError(void){
	int i;
	if((i=pwmDriver->error) >= 0)
		return 0;
	else{
#ifdef INCLUDE_DEBUG_STATEMENT
       	    printf("Error value of pwm driver is:%d",pwmDriver->error);
#endif
		return 1;
	}
}

void MOTORSHIELD::beeping(int time){
	gpioSetValue(buzzer,high);
	sleep(time);
	gpioSetValue(buzzer,low);
}

int MOTORSHIELD::checkRunningMotor(void){
	if(motorState==1)
		return 1;
	else
		return 0;
}

void MOTORSHIELD::turnOffMotors(void){
	if(motorState!=0){
		gpioSetValue(enableMotors,low);
		motorState=0;
	}
	stopMoving();
}

void MOTORSHIELD::turnOnMotors(void){
	if(checkRunningMotor()){
#ifdef INCLUDE_DEBUG_STATEMENT
		printf("enableMotors is already high");
#endif
	}
	else{
		gpioSetValue(enableMotors,high);
		motorState=1;
	}
}

void MOTORSHIELD::oneMotor(int motorDirectionPin,int dir, int speed, int freq){
	int onValue = 0;
	int offValue = 0;
	pwmDriver->setPWMFrequency(freq);
	if(dir == drive_forward){
		//240 difference
		onValue = slow_forward+speed;	//increase the onValue -> more speed
		offValue = fast_forward;
	}
	else if(dir == drive_backward){
		onValue = slow_backward-speed;	//decrease the onValue -> more speed
		offValue = fast_backward;;
	}
	gpioSetValue(motorDirectionPin,dir);
	printf("Direction %d ", dir);
	//problems with back roatation only on right side?
	if(motorDirectionPin == right_motor_direction){
		pwmDriver->setPWM(rightmotor,onValue,offValue);
#ifdef INCLUDE_DEBUG_STATEMENT
		printf("Left Motor has PWM signal now with onValue: %d and offValue: %d",onValue,offValue);
#endif
	}
	else if(motorDirectionPin==left_motor_direction){
		pwmDriver->setPWM(leftmotor,onValue,offValue);
#ifdef INCLUDE_DEBUG_STATEMENT
		printf("Left Motor has PWM signal now with onValue: %d and offValue: %d",onValue,offValue);
#endif
	}
	turnOnMotors();
}

void MOTORSHIELD::bothMotor(int dir, int speed, int freq){
	int onValue = 0;
	int offValue = 0;
	pwmDriver->setPWMFrequency(freq);
	if(dir == drive_forward){
		onValue = slow_forward+speed;	//increase the onValue -> more speed
		offValue = fast_forward;
	}
	else if(dir == drive_backward){
		onValue = slow_backward;//-speed;	//decrease the onValue -> more speed
		offValue = fast_backward+speed;	//increase the offValue -> more speed
	}
	//problem with power supply for motors?
	gpioSetValue(right_motor_direction,dir);
	gpioSetValue(left_motor_direction,dir);

	printf("Direction %d ", dir);
	pwmDriver->setAllPWM(onValue,offValue);
	turnOnMotors();
#ifdef INCLUDE_DEBUG_STATEMENT
		printf("Both Motors are running now with onValue: %d and offValue: %d",onValue,offValue);
#endif
}
