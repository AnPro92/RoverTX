#include <running.hpp>

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

/**
 * enum for different running modes
 */
enum modes {
	sensorFollowing = 1,
	sensorsEscaping = 2,
	remoteControl = 3,
	defaultRunnungMode=sensorFollowing
} ;
/**
 * enum for different coniditions of programm stopping, ending or continuing
 */
enum conditions{
	reenter = 32
};

class CONTROLLER
{
public:
	/**
	 * running object pointer to run the different modes
	 */
	RUNNING *running;
	/**
	 * current mode for running
	 */
	int mode;
	/**
	 * Creates a new CONTROLLER, sets default mode and initializes a running object
	 */
	CONTROLLER();
	~CONTROLLER();
	/**
	 * check in while loop if escape condition is repeated or return via reenter condition
	 * return: escape or reeneter conition
	 */
	int waiting();
	/**
	 * set new mode after change via keyboard entry
	 * return : mode for runnungMode
	 * TODO:check keyPress without enter during runningMode for mode change
	 */
	int checkModeChange();
	/**
	 * for different runningmodes depend on the current mode
	 * return: 1 if no valide mode
	 */
	int runningMode();
	/**
	 * start the different running modes, if no escape condition
	 * else waiting for reenter condition
	 */
	void run();
};

#endif /* CONTROLLER_HPP_ */

