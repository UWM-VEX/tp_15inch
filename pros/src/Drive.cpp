#include "main.h"

//using namespace okapi;

Drive::Drive(int8_t frontLeft, int8_t frontRight, int8_t rearLeft, int8_t rearRight)
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

	//chassis = myChassis;
}

void Drive::tankDrive(int left, int right)
{
	//chassis.tank(left, right);
}
