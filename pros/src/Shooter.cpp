#include "main.h"

using namespace pros;

Shooter robotShooter;

Shooter::Shooter() {};

void Shooter::initShooter(int driver1Port, int driver2Port)
{
	bool driver1Reverse = driver1Port < 0;
	if(driver1Port < 0) driver1Port *= -1;

	Motor* driver1Motor = new Motor((std::uint8_t) driver1Port, E_MOTOR_GEARSET_18, driver1Reverse, E_MOTOR_ENCODER_ROTATIONS);

	driver1 = (Motor*) malloc(sizeof(Motor));

	memcpy(driver1, driver1Motor, sizeof(*driver1Motor));

	bool driver2Reverse = driver2Port < 0;
	if(driver2Port < 0) driver2Port *= -1;

	Motor* driver2Motor = new Motor((std::uint8_t) driver2Port, E_MOTOR_GEARSET_18, driver2Reverse, E_MOTOR_ENCODER_ROTATIONS);

	driver2 = (Motor*) malloc(sizeof(Motor));

	memcpy(driver2, driver2Motor, sizeof(*driver2Motor));
}

void Shooter::set(int speed)
{
	driver1->move(speed);
	driver2->move(speed);
}