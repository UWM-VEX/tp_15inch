#include "main.h"

using namespace pros;

Drive robotDrive;

Drive::Drive() {}

void Drive::makeDrive (int frontLeftPort, int frontRightPort, int rearLeftPort, int rearRightPort)
{
	bool frontLeftReverse = frontLeftPort < 0;
	if(frontLeftPort < 0) frontLeftPort *= -1;

	Motor* frontLeftMotor = new Motor((std::uint8_t) frontLeftPort, E_MOTOR_GEARSET_18, frontLeftReverse, E_MOTOR_ENCODER_ROTATIONS);

	memcpy(frontLeft, frontLeftMotor, sizeof(*frontLeftMotor));

	bool frontRightReverse = frontRightPort < 0;
	if(frontRightPort < 0) frontRightPort *= -1;

	Motor* frontRightMotor = new Motor((std::uint8_t) frontRightPort, E_MOTOR_GEARSET_18, frontRightReverse, E_MOTOR_ENCODER_ROTATIONS);

	memcpy(frontRight, frontRightMotor, sizeof(*frontRightMotor));

	bool rearLeftReverse = rearLeftPort < 0;
	if(rearLeftPort < 0) rearLeftPort *= -1;

	Motor* rearLeftMotor = new Motor((std::uint8_t) rearLeftPort, E_MOTOR_GEARSET_18, rearLeftReverse, E_MOTOR_ENCODER_ROTATIONS);

	memcpy(rearLeft, rearLeftMotor, sizeof(*rearLeftMotor));

	bool rearRightReverse = rearRightPort < 0;
	if(rearRightPort < 0) rearRightPort *= -1;

	Motor* rearRightMotor = new Motor((std::uint8_t) rearRightPort, E_MOTOR_GEARSET_18, rearRightReverse, E_MOTOR_ENCODER_ROTATIONS);

	memcpy(rearRight, rearRightMotor, sizeof(*rearRightMotor));
}

void Drive::tankDrive(int left, int right)
{
	frontLeft->move(left);
	frontRight->move(right);
	rearLeft->move(left);
	rearRight->move(right);
}