#include "main.h"

using namespace pros;

Intake robotIntake;

Intake::Intake() {};

void Intake::makeIntake(int rollerPort, int elevatorPort)
{
	bool rollerReverse = rollerPort < 0;
	if(rollerPort < 0) rollerPort *= -1;

	Motor* rollerMotor = new Motor((std::uint8_t) rollerPort, E_MOTOR_GEARSET_18, rollerReverse, E_MOTOR_ENCODER_ROTATIONS);

	memcpy(roller, rollerMotor, sizeof(*rollerMotor));

	bool elevatorReverse = elevatorPort < 0;
	if(elevatorPort < 0) elevatorPort *= -1;

	Motor* elevatorMotor = new Motor((std::uint8_t) elevatorPort, E_MOTOR_GEARSET_18, elevatorReverse, E_MOTOR_ENCODER_ROTATIONS);

	memcpy(elevator, elevatorMotor, sizeof(*elevatorMotor));
}

void Intake::setRoller(int speed)
{
	roller->move(speed);
}

void Intake::setElevator(int speed)
{
	elevator->move(speed);
}