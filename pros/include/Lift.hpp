#ifndef _LIFT_HPP_
#define _LIFT_HPP_

class Lift{
	pros::Motor* left;
	pros::Motor* right;
public:
	Lift();
	void makeLift(int leftPort, int rightPort);
	void set(int speed);
};

extern Lift robotLift;

#endif