#ifndef _CLAW_HPP_
#define _CLAW_HPP_

class Claw{
	pros::Motor* motor1;
	pros::Motor* motor2;
public:
	Claw();
	void initClaw(int motor1Port, int motor2Port);
	void set(int speed);
	void printMotorTemps();
};

extern Claw robotClaw;

#endif