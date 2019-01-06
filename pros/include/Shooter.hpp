#ifndef _SHOOTER_HPP_
#define _SHOOTER_HPP_

class Shooter{
	pros::Motor* driver1;
	pros::Motor* driver2;
public:
	Shooter();
	void initShooter(int driver1Port, int driver2Port);
	void set(int speed);
	void printMotorTemps();
};

extern Shooter robotShooter;

#endif