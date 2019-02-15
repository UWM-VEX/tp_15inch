#include "main.h"

using namespace pros;

Flipper robotFlipper;

Flipper::Flipper() {};

void Flipper::initFlipper(int motorPort)
{
	motor = new Motor((std::uint8_t) abs(motorPort), E_MOTOR_GEARSET_18, motorPort < 0, E_MOTOR_ENCODER_DEGREES);
	UP_POSITION = 0;
	DOWN_POSITION = 410;
}

void Flipper::set(int speed)
{
	motor->move(speed);
}

void Flipper::down()
{
	motor->move_absolute(DOWN_POSITION, 127);
}

bool Flipper::isDown()
{
	return std::abs(motor->get_position() - DOWN_POSITION) < 10;
}

void Flipper::downBlocking()
{
	uint32_t startTime = pros::millis();

	do{
		down();
	}while(!isDown() && pros::millis() - startTime < 2000);
}

void Flipper::up()
{
	motor->move_absolute(UP_POSITION, 127);
}

bool Flipper::isUp()
{
	return std::abs(motor->get_position() - UP_POSITION) < 10;
}

void Flipper::upBlocking()
{
	uint32_t startTime = pros::millis();
	do{
		up();
	}while(!isUp() && pros::millis() - startTime < 2000);
}

void Flipper::printMotorTemps()
{
	lcd::print(0, "Flipper: %f", motor->get_temperature());
}