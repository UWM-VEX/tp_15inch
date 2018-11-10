#include "main.h"

//using namespace okapi;

Drive robotDrive;

Drive::Drive() {}

void Drive::initDrive(int8_t frontLeftPort, int8_t frontRightPort, int8_t rearLeftPort, int8_t rearRightPort)
{
	frontLeft = frontLeftPort;
	frontRight = frontRightPort;
	rearLeft = rearLeftPort;
	rearRight = rearRightPort;
}

/*Drive::Drive(int8_t frontLeft, int8_t frontRight, int8_t rearLeft, int8_t rearRight)
{
	okapi::Motor fl(frontLeft);
	okapi::Motor fr(frontRight);
	okapi::Motor rl(rearLeft);
	okapi::Motor rr(rearRight);

	auto myChassis = ChassisControllerFactory::create(
		  fl, fr, rl, rr,
		  AbstractMotor::gearset::green,
		  {5_in, 11.25_in}
		);

	chassis = myChassis;
}*/

okapi::ChassisControllerIntegrated Drive::makeDrive()
{
	okapi::Motor fl(frontLeft);
	okapi::Motor fr(frontRight);
	okapi::Motor rl(rearLeft);
	okapi::Motor rr(rearRight);

	return ChassisControllerFactory::create(
		  fl, fr, rl, rr,
		  AbstractMotor::gearset::green,
		  {5_in, 11.25_in}
		);

	//chassis = myChassis;

	//chassis = (okapi::ChassisControllerIntegrated*) malloc(sizeof(okapi::ChassisControllerIntegrated));

	//memcpy(chassis, &myChassis, sizeof(okapi::ChassisControllerIntegrated));
}
