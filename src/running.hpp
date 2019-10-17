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
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <sensors.hpp>
#include <drive.hpp>

#ifndef RUNNING_HPP_
#define RUNNING_HPP_

/**
 * enum for escape condition. defined by the keynumber from escape key.
 * in this case it is Esc with number 27
 */
enum condition{
	escape = 27
};

class RUNNING
{
public:
	/**
	 * sensors object pointer for accesing the sensors and their functionality
	 */
	SENSORS *sensors;
	/**
	 * drive object pointer for accessing the drive functionality
	 */
	DRIVE *drive;

	/**
	 * Creates a new RUNNING and initializes sensors and drive
	 */
	RUNNING();
	~RUNNING();

	/**
	 *  detect if escape condition appeared. Escape condition is typed in X
	 */
	int checkEscape(char &dir);
	/**
	 * implement if key pressed during running
	 * return: if escape key pressed return escape condition, else return pressed key
	 *TODO: implement check functionality for pressed key without enter
	 */
	int checkKeyPressed();
	/**
	 * detect if any problem or escape condition is appeared
	 * return: 0 if no problem else 1
	 */
	int checkQuit();
	/**
	 * check all entered values as integers
	 * direction: adress of direction
	 * side: adress of side
	 * speed: adress of speed
	 * freq: adress of freq
	 * t: adress of t (time)
	 * return: 1, if all entries valide, escape, if escape condition entered or else 0
	 */
	int checkValues(int& direction, int& side, int &speed, int& freq, int& t);
	/**
	 * to stop the sensor Running via deinitialisation
	 */
	void stopSensorsRunning();
	/**
	 * to run  the remote mode. checks via sensors values if the movement is allowed
	 * and runs via remoteControl if the entered values are correct for moving the motors
	 */
	int runRemote();
	/**
	* run  the follow mode. checks via sensors values if the movement is allowed
	* and depend of the sensor values it runs the intelligentFollowing
	 */
	void runFollow();
	/**
	* run  the escape mode. checks via sensors values if the movement is allowed
	* and depend of the sensor values it runs the intelligentEscaping
	 */
	void runEscape();
};



#endif /* RUNNING_HPP_ */
