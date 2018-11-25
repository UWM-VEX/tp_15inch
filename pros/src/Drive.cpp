#include "main.h"

Drive robotDrive;

Drive::Drive() {}

void Drive::initDrive(int8_t frontLeftPort, int8_t frontRightPort, int8_t rearLeftPort, int8_t rearRightPort)
{
	frontLeft = frontLeftPort;
	frontRight = frontRightPort;
	rearLeft = rearLeftPort;
	rearRight = rearRightPort;
}

okapi::ChassisControllerIntegrated Drive::makeDrive()
{
	okapi::Motor fl(frontLeft);
	okapi::Motor fr(frontRight);
	okapi::Motor rl(rearLeft);
	okapi::Motor rr(rearRight);

	return ChassisControllerFactory::create(
		  fl, fr, rl, rr,
		  AbstractMotor::gearset::green,
		  {2.5_in, 11.25_in}
		);
}