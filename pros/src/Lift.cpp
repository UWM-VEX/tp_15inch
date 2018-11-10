#include "main.h"

using namespace pros;

Lift robotLift;

Lift::Lift() {};

void Lift::makeLift(int leftPort, int rightPort)
{
	bool leftReverse = leftPort < 0;
	if(leftPort < 0) leftPort *= -1;

	Motor* leftMotor = new Motor((std::uint8_t) leftPort, E_MOTOR_GEARSET_18, leftReverse, E_MOTOR_ENCODER_ROTATIONS);

	left = (Motor*) malloc(sizeof(Motor));

	memcpy(left, leftMotor, sizeof(*leftMotor));

	bool rightReverse = rightPort < 0;
	if(rightPort < 0) rightPort *= -1;

	Motor* rightMotor = new Motor((std::uint8_t) rightPort, E_MOTOR_GEARSET_18, rightReverse, E_MOTOR_ENCODER_ROTATIONS);

	right = (Motor*) malloc(sizeof(Motor));

	memcpy(right, rightMotor, sizeof(*rightMotor));
}

void Lift::set(int speed)
{
	left->move(speed);
	right->move(speed);
}