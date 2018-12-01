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

	autoDrive.setMaxVelocity(125);

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

	//pros::lcd::initialize();
	//pros::lcd::clear();
	pros::vision_object_s_t flagToTrack;

	const double visionKP = 0.01;

	auto profileController = AsyncControllerFactory::motionProfile(
	  0.5,  // Maximum linear velocity of the Chassis in m/s
	  2.0,  // Maximum linear acceleration of the Chassis in m/s/s
	  10.0, // Maximum linear jerk of the Chassis in m/s/s/s
	  autoDrive // Chassis Controller
	);

	bool allignedWithFlag = false;

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
		case(SHOOT_2):
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
			robotShooter.set(0);

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
