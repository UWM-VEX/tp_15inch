#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

#define INTAKE_IN 0
#define INTAKE_OUT 1
#define INTAKE_STOP 2

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