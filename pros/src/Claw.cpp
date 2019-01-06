#include "main.h"

using namespace pros;

Claw robotClaw;

Claw::Claw() {};

void Claw::initClaw(int motor1Port, int motor2Port)
{
	motor1 = new Motor((std::uint8_t) abs(motor1Port), E_MOTOR_GEARSET_18, motor1Port < 0, E_MOTOR_ENCODER_ROTATIONS);
	motor2 = new Motor((std::uint8_t) abs(motor2Port), E_MOTOR_GEARSET_18, motor2Port < 0, E_MOTOR_ENCODER_ROTATIONS);
}

void Claw::set(int speed)
{
	motor1->move(speed);
	motor2->move(speed);
}

void Claw::printMotorTemps()
{
	lcd::print(0, "Motor 1: %f", motor1->get_temperature());
	lcd::print(1, "Motor 2: %f", motor2->get_temperature());
}