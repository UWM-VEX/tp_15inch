#include "main.h"

using namespace pros;

Flipper robotFlipper;

Flipper::Flipper() {};

void Flipper::initFlipper(int motorPort)
{
	motor = new Motor((std::uint8_t) abs(motorPort), E_MOTOR_GEARSET_18, motorPort < 0, E_MOTOR_ENCODER_DEGREES);
}

void Flipper::set(int speed)
{
	motor->move(speed);
}

void Flipper::down()
{
	motor->move_absolute(200, 127);
}

void Flipper::up()
{
	motor->move_absolute(0, 127);
}

void Flipper::printMotorTemps()
{
	lcd::print(0, "Flipper: %f", motor->get_temperature());
}