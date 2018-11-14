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
	okapi::ChassisControllerIntegrated opcontrolDrive = robotDrive.makeDrive();

	bool lastTurnerRotate = false;
	bool turnerAuto = false;

	while (true) {
		::std::cout << "Driving" << ::std::endl;
		opcontrolDrive.tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
		
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			robotShooter.set(127);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			robotShooter.set(-127);
		}
		else
		{
			robotShooter.set(0);
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			robotIntake.setRoller(127);
			robotIntake.setElevator(127);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			robotIntake.setRoller(-127);
			robotIntake.setElevator(-127);
		}
		else
		{
			robotIntake.setRoller(0);
			robotIntake.setElevator(0);
		}

		/*if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			robotLift.set(127);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			robotLift.set(-127);
		}
		else
		{
			robotLift.set(0);
		}*/

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			turnerAuto = false;
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
			turnerAuto = true;

		if(turnerAuto)
		{
			robotTurner.rotate180(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && ! lastTurnerRotate);

			lastTurnerRotate = master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
		}
		else
		{
			if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			{
				robotTurner.set(-30);
			}
			else
			{
				robotTurner.set(0);
			}
		}
		
	}
}
