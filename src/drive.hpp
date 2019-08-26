#include <motorShield.hpp>

#ifndef DRIVE_HPP_
#define DRIVE_HPP_

/**
 * enum for defaults values in no remote functions
 */
enum defaultValues{
	nospeedchange=0,
	defaultFrequenz=high_f
};

class DRIVE
{
public:
	/**
	 * motorshield object pointer for accessing motor move functions
	 */
	MOTORSHIELD *motorshield;
	/**
	 * Creates a new DRIVE, initialisation of motorshield to get access for driving
	 */
	DRIVE();
	~DRIVE();
	/**
	 * detect if the initialisation problems of motorshield
	 * return: 0 if no problems, else 01
	 */
	int checkError(void);
	/**
	 * drive function for using both motors with same parameters
	 * direction: sets the direction to rotate
	 * speed: to increase the default speed with this value (0-240)
	 * freq: used frequenz for pwm signal
	 */
	void drive(int direction, int speed, int freq);
	/**
	 * for forward side driving depend on the input parameter side
	 * driving left or right will be executed
	 * side: side of the motor to run
	 * speed:to increase the default speed with this value (0-240)
	 * freq:used frequenz for pwm signal
	 */
	void forwardSideDriving(int direction, int speed, int freq);
	/**
	 * drive function for using both motors with same parameters
	 * side: side of the motor to run
	 * speed: to increase the default speed with this value (0-240)
	 * freq: used frequenz for pwm signal
	 */
	void backwardSideDriving(int direction, int speed, int freq);
	/**
	 * detect via input sensors values (distance) which direction to rotate,
	 * which frequenz to use  for escaping
	 * frontDistance: front sensor value
	 * rearDistance: rear sensors value
	 * speed:to increase the default speed with this value (0-240)
	 * freq:used frequenz for pwm signal
	 */
	int intelligentEscaping(int frontDistance, int rearDistance, int speed, int freq);

	/**
	 * detect via input sensors values (distance) which direction to rotate,
	 * which frequenz to use  for following
	 * frontDistance: front sensor value
	 * rearDistance: rear sensors value
	 * speed:to increase the default speed with this value (0-240)
	 * freq:used frequenz for pwm signal
	 */
	int intelligentFollowing(int frontDistance, int rearDistance, int speed, int freq);
	/**
	 * detect via input sensors values (distance) which direction to rotate,
	 * which frequenz to use  for escaping
	 * f: front sensor value
	 * r: rear sensors value
	 * speed:to increase the default speed with this value (0-240)
	 * freq:used frequenz for pwm signal
	 */
	int remoteControl(int& dir, int& side, int &speed, int& freq, int &t);
	/**
	 * check if entered values are valide
	 * dir: direction for movement parameter
	 * side: side direction for movement
	 * time: time of moving
	 */
	int valideRemote(int& dir, int& side, int& time);

};

#endif /* DRIVE_H_ */
