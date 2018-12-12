#include "main.h"
#include <cmath>

using namespace pros;

Drive robotDrive;

Drive::Drive() {}

void Drive::initDrive(int frontLeftPort, int frontRightPort, int rearLeftPort, int rearRightPort)
{
	bool frontLeftReverse = frontLeftPort < 0;
	if(frontLeftPort < 0) frontLeftPort *= -1;

	Motor* frontLeftMotor = new Motor((std::uint8_t) frontLeftPort, E_MOTOR_GEARSET_18, frontLeftReverse, E_MOTOR_ENCODER_ROTATIONS);

	frontLeft = (Motor*) malloc(sizeof(Motor));

	memcpy(frontLeft, frontLeftMotor, sizeof(*frontLeftMotor));

	bool frontRightReverse = frontRightPort < 0;
	if(frontRightPort < 0) frontRightPort *= -1;

	Motor* frontRightMotor = new Motor((std::uint8_t) frontRightPort, E_MOTOR_GEARSET_18, frontRightReverse, E_MOTOR_ENCODER_ROTATIONS);

	frontRight = (Motor*) malloc(sizeof(Motor));

	memcpy(frontRight, frontRightMotor, sizeof(*frontRightMotor));

	bool rearLeftReverse = rearLeftPort < 0;
	if(rearLeftPort < 0) rearLeftPort *= -1;

	Motor* rearLeftMotor = new Motor((std::uint8_t) rearLeftPort, E_MOTOR_GEARSET_18, rearLeftReverse, E_MOTOR_ENCODER_ROTATIONS);

	rearLeft = (Motor*) malloc(sizeof(Motor));

	memcpy(rearLeft, rearLeftMotor, sizeof(*rearLeftMotor));

	bool rearRightReverse = rearRightPort < 0;
	if(rearRightPort < 0) rearRightPort *= -1;

	Motor* rearRightMotor = new Motor((std::uint8_t) rearRightPort, E_MOTOR_GEARSET_18, rearRightReverse, E_MOTOR_ENCODER_ROTATIONS);

	rearRight = (Motor*) malloc(sizeof(Motor));

	memcpy(rearRight, rearRightMotor, sizeof(*rearRightMotor));
}

void Drive::tankDrive(int left, int right)
{
	frontLeft->move(left);
	frontRight->move(right);
	rearLeft->move(left);
	rearRight->move(right);
}

void Drive::arcadeDrive(int mag, int rot)
{
	int left = mag + rot;
	int right = mag - rot;

	if(left > 127)
	{
		left = 127;
	}
	else if(left < -127)
	{
		left = -127;
	}

	if(right > 127)
	{
		right = 127;
	}
	else if(right < -127)
	{
		right = -127;
	}

	tankDrive(left, right);
}

void Drive::moveDistance(double distance, int speed)
{
	int32_t velocity = (distance > 0) ? speed : -speed;
	double targetRotation = distance / (wheelDiameter * M_PI);

	frontLeft->move_relative(targetRotation, velocity);
	frontRight->move_relative(targetRotation, velocity);
	rearLeft->move_relative(targetRotation, velocity);
	rearRight->move_relative(targetRotation, velocity);

	bool done = false;

	while(!done)
	{
		std::cout << "Auto Looping" << std::endl;
		done = (std::abs(frontLeft->get_position() - frontLeft->get_target_position()) < 0.05) &&
		(std::abs(frontRight->get_position() - frontRight->get_target_position()) < 0.05) &&
		(std::abs(rearLeft->get_position() - rearLeft->get_target_position()) < 0.05) &&
		(std::abs(rearRight->get_position() - rearRight->get_target_position()) < 0.05);
		delay(20);
	}
}

void Drive::turnAngle(double angle, int speed)
{
	int32_t velocity = (angle > 0) ? speed : -speed;
	double distanceToTurn = (angle / 360.0) * M_PI * wheelBaseWidth;
	double targetRotation = distanceToTurn / (wheelDiameter * M_PI);

	frontLeft->move_relative(targetRotation, velocity);
	frontRight->move_relative(-targetRotation, velocity);
	rearLeft->move_relative(targetRotation, velocity);
	rearRight->move_relative(-targetRotation, velocity);

	bool done = false;

	while(!done)
	{
		std::cout << "Auto Looping" << std::endl;
		done = (std::abs(frontLeft->get_position() - frontLeft->get_target_position()) < 0.05) &&
		(std::abs(frontRight->get_position() - frontRight->get_target_position()) < 0.05) &&
		(std::abs(rearLeft->get_position() - rearLeft->get_target_position()) < 0.05) &&
		(std::abs(rearRight->get_position() - rearRight->get_target_position()) < 0.05);
		delay(20);
	}
}

/*okapi::ChassisControllerIntegrated Drive::makeDrive()
{
	Motor fl(frontLeft);
	Motor fr(frontRight);
	Motor rl(rearLeft);
	Motor rr(rearRight);

	return ChassisControllerFactory::create(
		  {fl, rl}, {fr, rr},
		  AbstractMotor::gearset::green,
		  {4_in, 17_in}
		);
}*/