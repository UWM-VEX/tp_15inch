#include "main.h"
#include <cmath>

using namespace okapi;

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
	return ChassisControllerFactory::create(
		  {frontLeft, rearLeft}, {frontRight, rearRight},
		  AbstractMotor::gearset::green,
		  {4_in, 15_in}
		);
}