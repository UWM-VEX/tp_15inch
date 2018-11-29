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
	ChassisControllerIntegrated autoDrive = robotDrive.makeDrive();

	auto profileController = AsyncControllerFactory::motionProfile(
	  0.5,  // Maximum linear velocity of the Chassis in m/s
	  2.0,  // Maximum linear acceleration of the Chassis in m/s/s
	  10.0, // Maximum linear jerk of the Chassis in m/s/s/s
	  autoDrive // Chassis Controller
	);

	switch(autonomousInfoStruct.mode)
	{
		case(DO_NOTHING):

		break;
		case(TEST):
			autoDrive.moveDistance(5_ft);
			autoDrive.turnAngle(90_deg);
			autoDrive.turnAngle(-90_deg);
			autoDrive.moveDistance(-5_ft);
		break;
		case(MOTION_PROFILE):
			profileController.generatePath({
			  okapi::Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{3_ft, 3_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "A" // Profile name
			);

			profileController.setTarget("A");

			profileController.waitUntilSettled();
		break;
		default:
		// Do nothing
		break;
	}
}
