#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

using namespace okapi;

void autonomous()
{
	pros::Vision vision_sensor = makeVisionSensor();

	//pros::lcd::initialize();
	//pros::lcd::clear();
	const double visionKP = 0.01;

	uint32_t startTime = pros::millis();

	bool allignedWithFlag = false;

	switch(autonomousInfoStruct.mode)
	{
		case(DO_NOTHING):

		break;
		case(TEST):
			robotDrive.moveDistance(60);
			robotDrive.turnAngle(90);
			robotDrive.turnAngle(-90);
			robotDrive.moveDistance(-50);
		break;
		case(MOTION_PROFILE):

		break;
		case(SHOOT_2):
			startTime = pros::millis();

			while(!allignedWithFlag && pros::millis() - startTime > 3000)
			{
				int16_t flagX = getFlagX(vision_sensor);

				std::cout << "Flag X: " << (int) flagX << std::endl;

				double turn = flagX * visionKP;

				if(flagX > 5 || flagX < -5)
				{
					robotDrive.arcadeDrive(0, (int) (turn * 127));
				}
				else
				{
					robotDrive.arcadeDrive(0, 0);
				}

				pros::delay(20);
			}

			robotShooter.set(127);
			pros::delay(1000);
			robotShooter.set(0);

			robotIntake.set(127);

			robotDrive.moveDistance(48, 127);

			/*autoDrive.turnAngleAsync(180_deg);

			autoDrive.waitUntilSettled();

			pros::delay(500);

			robotIntake.set(127);
			autoDrive.moveDistanceAsync(36_in);
			robotIntake.set(0);
			autoDrive.waitUntilSettled();

			autoDrive.turnAngleAsync(-180_deg);
			autoDrive.waitUntilSettled();
			pros::delay(500);

			autoDrive.moveDistanceAsync(72_in);
			autoDrive.waitUntilSettled();

			allignedWithFlag = false;
			while(!allignedWithFlag)
			{
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

				double turn = flagX * visionKP;

				if(flagX > 5 || flagX < -5)
				{
					autoDrive.arcade(0, turn);
				}
				else
				{
					autoDrive.arcade(0, 0);
					allignedWithFlag = true;
				}

				pros::delay(20);
			}

			robotShooter.set(127);
			pros::delay(1000);
			robotShooter.set(0);*/
		break;
		default:
		// Do nothing
		break;
	}
}
