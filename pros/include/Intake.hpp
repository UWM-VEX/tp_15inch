#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

class Intake{
private:
	pros::Motor* roller;
	pros::Motor* elevator;
public:
	Intake();
	void makeIntake(int rollerPort, int elevatorPort);
	void setRoller(int speed);
	void setElevator(int speed);
};

extern Intake robotIntake;

#endif