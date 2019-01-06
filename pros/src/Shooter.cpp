#include "main.h"

using namespace pros;

Shooter robotShooter;

Shooter::Shooter() {};

void Shooter::initShooter(int driver1Port, int driver2Port)
{
	driver1 = new Motor((std::uint8_t) abs(driver1Port), E_MOTOR_GEARSET_18, driver1Port < 0, E_MOTOR_ENCODER_ROTATIONS);
	driver2 = new Motor((std::uint8_t) abs(driver2Port), E_MOTOR_GEARSET_18, driver2Port < 0, E_MOTOR_ENCODER_ROTATIONS);
}

void Shooter::set(int speed)
{
	driver1->move(speed);
	driver2->move(speed);
}

void Shooter::printMotorTemps()
{
	lcd::print(0, "Driver 1: %f", driver1->get_temperature());
	lcd::print(1, "Driver 2: %f", driver2->get_temperature());
}