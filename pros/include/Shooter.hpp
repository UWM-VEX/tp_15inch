#ifndef _SHOOTER_HPP_
#define _SHOOTER_HPP_

class Shooter{
	pros::Motor* driver1;
	pros::Motor* driver2;
public:
	Shooter();
	void makeShooter(int driver1Port, int driver2Port);
	void set(int speed);
};

extern Shooter robotShooter;

#endif