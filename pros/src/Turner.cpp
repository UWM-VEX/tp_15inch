#include "main.h"
#include <cmath>

using namespace pros;

Turner robotTurner;

Turner::Turner() {};

void Turner::initTurner(int driverPort)
{
	bool driverReverse = driverPort < 0;
	if(driverPort < 0) driverPort *= -1;

	Motor* driverMotor = new Motor((std::uint8_t) driverPort, E_MOTOR_GEARSET_18, driverReverse, E_MOTOR_ENCODER_ROTATIONS);

	driver = (Motor*) malloc(sizeof(Motor));

	memcpy(driver, driverMotor, sizeof(*driverMotor));
}

void Turner::set(int speed)
{
	driver->move(speed);
}

bool Turner::rotate180(bool isFirstTime)
{
	if(isFirstTime)
	{
		driver->move_relative(0.5, 100);
	}

	return std::abs(driver->get_position() - driver->get_target_position()) < 0.01;
}