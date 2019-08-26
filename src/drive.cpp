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
#include <jetsonGPIO.h>
#include "drive.hpp"
#include <stdio.h>
#include <iostream>
#include <flags.h>


DRIVE::DRIVE() {
	motorshield = new MOTORSHIELD();
	motorshield->activateMotors();
}

DRIVE::~DRIVE() {
}

int DRIVE::checkError(void){
	if(motorshield->checkError())
		return 1;
	else
		return 0;
}

void DRIVE::drive(int direction, int speed, int freq){
	motorshield->bothMotor(direction, speed, freq);
}

void DRIVE::forwardSideDriving(int side, int speed, int freq){
	if(side > 0){	//side 0=both motors, 1=left, 2=right
		motorshield->pwmDriver->setAllPWM(0,0);
		if(side == drive_left){
			printf("Drive forward left");
			motorshield->oneMotor(left_motor_direction, drive_forward, speed, freq);

		}
		else if(side==drive_right){
			printf("Drive forward right");
			motorshield->oneMotor(right_motor_direction, drive_forward, speed, freq);
		}
	}
}

void DRIVE::backwardSideDriving(int side, int speed, int freq){
	if(side > 0){	//side 0=both motors, 1=left, 2=right
		motorshield->pwmDriver->setAllPWM(0,0);
		if(side == drive_right){
			printf("Drive backward right\n");
			motorshield->oneMotor(right_motor_direction, drive_backward, speed, freq);

		}
		else if(side==drive_left){
			printf("Drive backward left\n");
			motorshield->oneMotor(left_motor_direction,drive_backward, speed, freq);
		}
	}
}


int DRIVE::intelligentEscaping(int frontDistance, int rearDistance, int speed, int freqT){
	int freq = defaultFrequenz;
	int direction;
	if((frontDistance<40 && frontDistance>2) || (rearDistance<40 && rearDistance>2)){	//check if some space changes happened inside the reacting range for just this application
		if(frontDistance<rearDistance && rearDistance>0){	//if frontDistance is lower then the rearDistance and the rearDistance gives space to move
			printf("Drive Backward\n");
			direction = drive_backward;
			if(frontDistance<20){
				freq=low_f;
				speed+=100;
//				if(frontDistance<5){
//					motorshield->beeping(1);
//					return 0;
//				}
			}
		}
		else if(rearDistance<frontDistance && frontDistance>0){	//if rearDistance is lower then the frontDistance and the frontDistance gives space to move
			printf("Drive Forward\n");
			direction = drive_forward;
			if(rearDistance<20){
				freq=low_f;
				speed+=100;
//				if(r<5){
//					motorshield->beeping(0.2);
//					sleep(0.2);
//					motorshield->beeping(0.2);
//					return 0;
//				}
			}
		}
		if(freqT!=defaultFrequenz&&freqT!=0)	//if allowed frequenz change is avaible
			freq=freqT;
		drive(direction,speed,freq);
		return 1;
	}
	motorshield->turnOffMotors();
	return 0;
}

int DRIVE::intelligentFollowing(int frontDistance, int rearDistance, int speed, int freqT){
	int freq = defaultFrequenz;
	int direction ;
	if((frontDistance<40 && frontDistance>2) || (rearDistance<40 && rearDistance>2)){	//check if some space changes happened inside the reacting range for just this application
		if(frontDistance<rearDistance && rearDistance>0){		//if frontDistance is lower then the rearDistance and the frontDistance gives space to move
			printf("Follow Forward\n");
			direction = drive_forward;
			if(frontDistance<20){
				freq=low_f;	//decrease frequenz
				speed+=50;
			}
			if(frontDistance<5){	//if distance gets to low then beeping and movement stop
				motorshield->beeping(1);
				motorshield->turnOffMotors();
			}
		}
		else if(rearDistance<frontDistance && frontDistance>0){	//if rearDistance is lower then the frontDistance and the rearDistance gives space to move
			printf("Follow Backward\n");
			direction = drive_backward;
			if(rearDistance<20){
				freq=low_f;	//decrease frequenz
				speed+=50;
			}
			if(rearDistance<5){	//if distance gets to low then beeping and movement stop
				motorshield->beeping(0.2);
				sleep(0.2);
				motorshield->beeping(0.2);
				motorshield->turnOffMotors();
			}
		}
		if(freqT!=defaultFrequenz&&freqT!=0)	//if allowed frequenz change is avaible
			freq=freqT;
		drive(direction,speed,freq);	//drive with the set attribute
		return 1;
	}
	motorshield->turnOffMotors();
	return 0;
}

int DRIVE::remoteControl(int& dir, int& side, int& speed, int& freq, int &t){
	if(valideRemote(dir,side,t)!=0){	//check if the attribute are valide for remtoe control
		if(side > 0 ){	//check if side driving is necessary
			if(dir == drive_backward)
				backwardSideDriving(side,speed, freq);
			if(dir == drive_forward)
				forwardSideDriving(side,speed, freq);
		}
		else
			drive(dir,speed, freq);
		sleep(t);	//duration time of the remote command
		motorshield->turnOffMotors();
		return 1;
	}
	motorshield->turnOffMotors();
	return 0;
}

int DRIVE::valideRemote(int &dir, int& side, int &time){
	if(time==0){
		printf("time = 0 is not allowed\n");
		return 0;
	}
	if(!(dir==drive_forward || dir ==drive_backward)){
		printf("direction must be 0 or 1\n");
		return 0;
	}
	if(!(side>=0 && side <= drive_right)){
		printf("side must be between 0 and 2\n");
		return 0;
	}
	else
		return 1;
}
