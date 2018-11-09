#include "main.h"

using namespace pros;

Turner robotTurner;

Turner::Turner() {};

void Turner::makeTurner(int driverPort)
{
	bool driverReverse = driverPort < 0;
	if(driverPort < 0) driverPort *= -1;

	Motor* driverMotor = new Motor((std::uint8_t) driverPort, E_MOTOR_GEARSET_18, driverReverse, E_MOTOR_ENCODER_ROTATIONS);

	memcpy(driver, driverMotor, sizeof(*driverMotor));
}

void Turner::set(int speed)
{
	driver->move(speed);
}