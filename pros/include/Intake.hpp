#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

class Intake{
private:
	pros::Motor* roller;
public:
	Intake();
	void initIntake(int rollerPort);
	void set(int speed);
};

extern Intake robotIntake;

#endif