#ifndef _SHOOTER_HPP_
#define _SHOOTER_HPP_

class Shooter{
	pros::Motor* driver;
public:
	Shooter();
	void makeShooter(int driverPort);
	void set(int speed);
};

extern Shooter robotShooter;

#endif