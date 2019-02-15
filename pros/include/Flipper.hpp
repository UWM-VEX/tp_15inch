#ifndef _FLIPPER_HPP_
#define _FLIPPER_HPP_

class Flipper{
	pros::Motor* motor;
	double DOWN_POSITION;
	double UP_POSITION;
public:
	Flipper();
	void initFlipper(int motorPort);
	void set(int speed);
	void down();
	bool isDown();
	void downBlocking();
	void up();
	bool isUp();
	void upBlocking();
	void printMotorTemps();
};

extern Flipper robotFlipper;

#endif