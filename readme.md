# [RoverTX][documentation]
> RoverTX is a implementation of the software for the new developed RoverTX on the Jetson TX2 Development Kit. The RoverTX
is a new revision of the well known POLARSYS and APP4MC Rover. This software allows to access via Jetson TX2 to the Rover 
and its components. 

This project is done in the context of Google Summer of Code 2019 

## Quick start
0. Connect all devices with the configuration from this table:
	https://gitlab-pages.idial.institute/panorama.gsoc.project/rover.doc/content/roverhw.html#connecting

1. Fork the repository:
	git clone https://gitlab.idial.institute/panorama.gsoc.project/rover.src

2. To get the I2C drivers for implementation use the following command:
	sudo apt-get install libi2c-dev i2c-tools

3. Please install the I2C-Tools also on the Jetson TX2 via following commands:
	sudo apt-get install libi2c-dev i2c-tools
and check if the i2c device is conncted via default adress 0x40 via the command:
	sudo i2cdetect -y -r 1
If no device is conncted, please check the correct connection or installation of I2C-Tools.

3. To download extern source files for hardware drivers you have to download these repositories 
via the script inside the installscripts directory into the main RoverTX directory:
	sh installExtern.sh

4. To compile implementations via Nvidia Nsight please install JRW8 via:
	sudo apt-get install openjdk-8-jre

5. Before compile the implementation you have to change the include command inside the JHPWMPCA9685.h. You have to change the include command:
	#include <linux/i2c-dev.h>
to this include command:
	#include "i2c-dev.h"
Now you have the I2C drivers inside your project directory

6. Now you have all drivers and source files to compile the application. Start the RoverTX application inside Eclipse Nsight as Remote C/C++ Application with the option for upload executable. The instructions for the remote configuration are shown on:
https://gitlab-pages.idial.institute/panorama.gsoc.project/rover.doc/content/installation.html#configuration-nvidia-nsight-remote

7. Connect to the Jetson TX2 via ssh and start the apllication with:
	sudo ./RoverTX/Debug

## Usage example

RoverTX software can be used to implement different application for the Jetson TX2. It enables to improve the processing power of the rover
by using the Jetson TX2.

_For more examples and usage, please refer to the [documentation][documentation]._

## Contributers

* Andreas Pronosa – AndreasPro@t-online.de

Distributed under EPL license.

<!-- Markdown link & img dfn's -->
[documentation]: https://gitlab-pages.idial.institute/panorama.gsoc.project/rover.doc/content/intro.html
