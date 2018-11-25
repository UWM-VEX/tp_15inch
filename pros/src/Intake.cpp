#include "main.h"

using namespace pros;

Intake robotIntake;

Intake::Intake() {};

void Intake::initIntake(int rollerPort)
{
	bool rollerReverse = rollerPort < 0;
	if(rollerPort < 0) rollerPort *= -1;

	Motor* rollerMotor = new Motor((std::uint8_t) rollerPort, E_MOTOR_GEARSET_18, rollerReverse, E_MOTOR_ENCODER_ROTATIONS);

	roller = (Motor*) malloc(sizeof(Motor));

	memcpy(roller, rollerMotor, sizeof(*rollerMotor));
}

void Intake::set(int speed)
{
	roller->move(speed);
}