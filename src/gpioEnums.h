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

#ifndef GPIOENUMS_H_
#define GPIOENUMS_H_



/**
 * enum for used gpios. Declare pinadress as gpionumber name
 */
enum UsedGPIOsNumber{
	gpio23 = 427,
	gpio24 = 430,
	gpio28 = 341,
	gpio31 = 298,	  //J21 - Pin31 OUTPUT used
	gpio37 = 388,	  //J21 - Pin37  INPUT used
	gpio11 = 466,	  // used buzzer output
	gpio12 = 392,	  //J21 - Pin 12 OUTPUT used
	gpio13 = 397,	  //J21 - Pin 13 INPUT used
	gpio40 = 393,	  //J21 - Pin40 OUTPUT used
	gpio35 = 395 ,    //J21 - Pin 35 OUTPUT used
	gpio32 = 297	  //J21 - Pin 32 OUTPUT used
}  ;



#endif /* GPIOENUMS_H_ */
