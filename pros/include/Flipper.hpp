#ifndef _FLIPPER_HPP_
#define _FLIPPER_HPP_

class Flipper{
	pros::Motor* motor;
public:
	Flipper();
	void initFlipper(int motorPort);
	void set(int speed);
	void down();
	void up();
	void printMotorTemps();
};

extern Flipper robotFlipper;

#endif