#include "main.h"

using namespace pros;

Intake robotIntake;

Intake::Intake() {};

void Intake::initIntake(int rollerPort)
{
	roller = new Motor((std::uint8_t) abs(rollerPort), E_MOTOR_GEARSET_18, rollerPort < 0, E_MOTOR_ENCODER_ROTATIONS);
}

void Intake::set(int speed)
{
	roller->move(speed);
}

void Intake::printMotorTemps()
{
	lcd::print(0, "Roller: %f", roller->get_temperature());
}