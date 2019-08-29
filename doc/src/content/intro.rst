.. toctree::
   :glob:

Introduction
#########################
*************************************************
What is RoverTX?
*************************************************
This project is about developing a new revision of the POLARSYS and APP4MC Rover.
The main goal of this revision is to provide an academic demonstrator that provides functionality close to the automotive domain with improved processing power by using a more powerful computing module.
As the new computing module the Nvidia Jetson TX2 has been chosen.
To assure the complete functionality of the interfaces a carrier board has to be used.
For the other part of this new development the existing hardware components have to be evaluated and selected to gain the same functionality on the new version of the rover.
These hardware components are for example sensors for information collection of the environment.
Other components such as the chassis or motor shield are important for the movement of the rover.
After selecting and changing hardware components the using of an operating system is necessary.
As preferred OS a RTOS should be used.
Therefore, the understanding of how the OS works is essential.
After knowing how the OS works an application based on this OS should be created.
Firstly, getting control of all connected devices is necessary for beeing able to use the full functionality.
As next work step an industrial example should be converted onto the developed embedded system of the rover.
To validate the achievement of the goal for developing a new revision, the rover has to deliver the same functionality as the POLARSYS and APP4MC Rover.

*************************************************
Goal
*************************************************
We want to execute real-time applications using a RTOS on typical heterogeneous embedded systems and compare the results with APP4MC.
In order to achieve this goal we intend to extend the well-known POLARSYS and APP4MC Rovers.
This new revision will include a significant increase of processing power based on an heterogeneous computing platform typically encountered in the automotive domain.
Therefore, we will integrate the Nvidia Jetson TX2 Module into the new rover.
All deliverables, i.e. guides on how to reconstruct this new revision of the rover as well as the new application along with its documentation will be published open
source.

*************************************************
Project Repository
*************************************************
The repository the RoverTX software: `RoverTX source code <https://github.com/AnPro92/RoverTX.git>`_

The Documentation of the construction and implementation of the RoverTX: `RoverTX documenation <https://gitlab-pages.idial.institute/panorama.gsoc.project/rover.doc/content/intro.html>`_

`Merge request on git.eclipse.org <https://git.eclipse.org/r/#/c/148423/>`_

*************************************************
Additional Links
*************************************************
`GSoC 2019 Project: <https://summerofcode.withgoogle.com/projects/#5928914382225408>`_

The reference to the exisiting version of the APP4MC Rover: `APP4MC Rover <https://app4mc-rover.github.io/rover-docs/content/intro.html#additional-links>`_

