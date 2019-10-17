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
#include <hcsr04.h>
#include <jetsonGPIO.h>

#ifndef SENSORS_HPP_
#define SENSORS_HPP_

/**
 * enum for different sensor types
 */
enum differentSensors {
	front  = 'F',
	rear = 'R'
} ;

class SENSORS
{
public:
	/**
	 * pointer on object of front HCSR04 ultrasonic sensor module
	 */
	HCSR04 *hcsr04Front;
	/**
	 * pointer on object of rear HCSR04 ultrasonic sensor module
	 */
	HCSR04 *hcsr04Rear;
	/**
	 * GPIO adress of usr_button
	 */
	jetsonGPIO usr_button;
	/**
	 * GPIO adress of shutdown_button
	 */
	jetsonGPIO shutdown_button;
	/**
	 * Creates a new SENSORS, initialisation of all Sensors and used GPIOs to get access for reading
	 * of values and changes
	 */
	SENSORS();
	~SENSORS();
	/**
	 * initialisation of the used sensors
	 * includes export and direction set for required gpios of sensors
	 */
	void initSensors();
	/**
	 * deinitialisation of used sensors
	 */
	void deinitSensors();
	/**
	 * initialisation of button for used gpio
	 * gpio: gpio adress of button
	 */
	void initButtons(jetsonGPIO gpio);
	/**
	 * read values of #
	 * gpio: gpio adress of button
	 * return: value of read button
	 */
	int readButtons(jetsonGPIO gpio);
	/**
	 * read distance of ultrasonic sensor, depend on input of sensor name
	 * sensor: sensor short name
	 * return: range of measured distance in cm
	 */
	int readDistance(char sensor);
};

#endif /* SENSORS_HPP_ */
