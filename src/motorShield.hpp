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
#include <JHPWMPCA9685.h>
#include "gpioEnums.h"
#include "flags.h"

#ifndef MOTORSHIELD_H_
#define MOTORSHIELD_H_

#define low_f 10 //24
#define high_f 10000

/**
 * enum for used gpio pins by motorshield
 */
enum usedGPIOS {
	enable_motor = gpio32,
	left_motor_direction = gpio40,
	right_motor_direction  = gpio35,
	buzzer_signal = gpio11
} ;

/**
 * enum for min and max value for drive values in different directions
 */
enum driveValues {
	fast_forward  = 255,
	slow_forward = 15,
	fast_backward = 0,
	slow_backward = 240
} ;

/**
 * enum for the pwm adress for each motor
 */
enum motorPWMS {
	leftmotor = 0,
	rightmotor = 7
} ;

/**
 * enum for declaration of direction and values for drive direction
 */
enum driveDirection {
	drive_forward  = high,
	drive_backward = low,
	drive_left = 1,
	drive_right = 2
} ;

class MOTORSHIELD
{
public:
	/**
	 * gpio pin to activate or deactivate motors
	 */
    jetsonGPIO enableMotors;
	/**
	 * gpio pin to setDirection for left motor
	 */
    jetsonGPIO leftDirection;
	/**
	 * gpio pin to setDirection for right motor
	 */
    jetsonGPIO rightDirection;
	/**
	 * gpio pin of connected buzzer
	 */
    jetsonGPIO buzzer;
	/**
	 * pwm driver object pointer to get access for pwm functionality
	 */
    PCA9685 *pwmDriver;
	/**
	 * current motorState
	 */
    int motorState;

    /**
     * Creates a new MOTORSHIELD.
     * Sets the adress for the used gpio pins and the current motorState
     * and also the initialisation of pwm driver to get access for pwm functionality
     */
    MOTORSHIELD() ;
    ~MOTORSHIELD() ;
    /**
     *  set up the used GPIO pins MOTORSHIELD.
     */
    void setUsedGPIOS ( void ) ;
    /**
     *  unset the used GPIO pins MOTORSHIELD.
     */
    void unsetUsedGPIOS ( void ) ;
    /**
     *  initalisation of used GPIOs and pwm driver for the actiovation of motors to allow the driving
     */
    void activateMotors(void);
    /**
     *  initialisation of pwm driver. Required for generation of pwm signals
     */
    void initPwmDriver(void);
    /**
     *  deactivate the used pwm driver and the motors
     */
    void deactivateMotors(void);
    /**
     * stop the moving with no pwm signal
     */
    void stopMoving(void);
    /**
     * detect if pwm driver of motorshield has initialisation problems
     * return: 1 if problem, else 0
     */
    int checkError(void);
    /**
     * set buzzer for a specififc time
     * time: specific running time
     */
    void beeping(int time);
    /**
     * check the current motor state
     * return: 1 if already active, else 0
     */
    int checkRunningMotor(void);
    /**
     * turning off motors and pwm signal
     */
    void turnOffMotors(void);
    /**
     * turning on motors and set current motorState
     */
    void turnOnMotors(void);
    /**
     * rotating one motor. Rotation behaviour depends on input parameters
     * motorDirectionPin: sets the motor to rotate
     * dir: sets the direction to rotate
     * speed: to increase the default speed with this value (0-240)
     * freq: used frequenz for pwm signal
     */
    void oneMotor(int motorDirectionPin, int dir, int speed, int freq);
    /**
     * rotating both motors. Rotation behaviour depends on input parameters
     * dir: sets the direction to rotate
     * speed: to increase the default speed with this value (0-240)
     * freq: used frequenz for pwm signal
     */
    void bothMotor(int dir, int speed, int freq);
};


#endif /* MOTORSHIELD_H_ */
