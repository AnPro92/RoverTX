#!/usr/bin/env bash
echo "RoverTX patching Script version 1.0"
echo "*****************************************************"
echo "cloning dependencies..."
cd ../
directory=$PWD
mkdir extern
git clone https://github.com/jetsonhacks/JHHC-SR04.git
cd JHHC-SR04/src/
cp hcsr04.cpp hcsr04.h jetsonGPIO.c jetsonGPIO.h ../../extern/
cd ../../
git clone https://github.com/jetsonhacks/JHPWMDriver.git
cd JHPWMDriver/src
cp JHPWMPCA9685.cpp JHPWMPCA9685.h ../../extern/
cd ../../

cd /../usr/include/linux
cp i2c-dev.h /../../$directory/extern/

sudo rm -r /../../$directory/JHPWMDriver
sudo rm -r /../../$directory/JHHC-SR04
echo "*****************************************************"
pwd
echo "***************************************"
echo "done"
