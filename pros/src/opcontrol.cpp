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

	bool lastTurnerRotate = false;
	bool turnerAuto = false;
	int intakeState = INTAKE_STOP;
	bool lastIntakeInButton = false;
	bool lastIntakeOutButton = false;

	const int VISION_PORT = 2;

	pros::Vision vision_sensor (VISION_PORT, pros::E_VISION_ZERO_CENTER);

	pros::vision_signature_s_t redFlag;
	redFlag.id = 1;
	redFlag.range = 7.3;
	redFlag.u_min = 7791;
	redFlag.u_max = 8107;
	redFlag.u_mean = 7949;
	redFlag.v_min = -1119;
	redFlag.v_max = -639;
	redFlag.v_mean = -879;
	redFlag.rgb = 9784645;
	redFlag.type = 0;

	const uint8_t redFlagId = 1;
	vision_sensor.set_signature(redFlagId, &redFlag);

	pros::vision_signature_s_t blueFlag;
	blueFlag.id = 2;
	blueFlag.range = 5.6;
	blueFlag.u_min = -2353;
	blueFlag.u_max = -1969;
	blueFlag.u_mean = -2161;
	blueFlag.v_min = 7341;
	blueFlag.v_max = 8323;
	blueFlag.v_mean = 7832;
	blueFlag.rgb = 2503520;
	blueFlag.type = 0;

	const uint8_t blueFlagId = 2;
	vision_sensor.set_signature(blueFlagId, &blueFlag);

	vision_sensor.set_exposure(15);

	//pros::lcd::initialize();
	//pros::lcd::clear();
	pros::vision_object_s_t flagToTrack;

	const double visionKP = 0.01;

	while (true) {
		
		
		if(autonomousInfoStruct.alliance == RED)
		{
			flagToTrack = vision_sensor.get_by_sig(0, blueFlagId);
		}
		else
		{
			flagToTrack = vision_sensor.get_by_sig(0, redFlagId);
		}

		int16_t flagX = flagToTrack.x_middle_coord;

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

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			turnerAuto = false;
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
			turnerAuto = true;
		
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
