#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Controller partner(pros::E_CONTROLLER_PARTNER);

	int intakeState = INTAKE_STOP;
	bool lastIntakeInButton = false;
	bool lastIntakeOutButton = false;

	bool flipperAuto = false;

	pros::Vision vision_sensor = makeVisionSensor();

	const double visionKP = 0.01;

	while (true) {
		int16_t flagX = getFlagX(vision_sensor);

		std::cout << "Flag X: " << (int) flagX << std::endl;

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			double turn = flagX * visionKP;

			if(flagX > 5 || flagX < -5)
			{
				robotDrive.arcadeDrive(0, (int) (turn * 127));
			}
			else
			{
				robotDrive.arcadeDrive(0, 0);
			}
		}
		else
		{
			robotDrive.tankDrive(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) ||
			master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			robotShooter.set(127);
		}
		else
		{
			robotShooter.set(0);
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			intakeState = INTAKE_IN;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			intakeState = INTAKE_OUT;
		}
		else
		{
			intakeState = INTAKE_STOP;
		}

		if(intakeState == INTAKE_IN)
		{
			robotIntake.set(127);
		}
		else if(intakeState == INTAKE_OUT)
		{
			robotIntake.set(-127);
		}
		else
		{
			robotIntake.set(0);
		}

		if(std::abs(partner.get_analog(ANALOG_RIGHT_Y)) > 20)
		{
			robotFlipper.set(partner.get_analog(ANALOG_RIGHT_Y));
			flipperAuto = false;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			robotFlipper.up();
			flipperAuto = true;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			robotFlipper.down();
			flipperAuto = true;
		}
		else if(!flipperAuto)
		{
			robotFlipper.set(0);
		}

		/*if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			turnerAuto = false;
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
			turnerAuto = true;*/
		
		/*pros::vision_object_s_t rtn = vision_sensor.get_by_size(0);
		if(rtn.signature == redFlagId)
		{
			robotTurner.set(127);
		}
		else if(rtn.signature == blueFlagId)
		{
			robotTurner.set(30);
		}
		else
		{
			robotTurner.set(0);
		}*/
	    // Gets the largest object
	    //pros::lcd::print(0, "Signature: %d", rtn.signature);
	    //pros::lcd::set_text(0,"Hello");
	    //std::cout << "sig: " << rtn.signature << std::endl;
	}
}
