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

void turnAngleGyro(double angle, ChassisControllerIntegrated* drive)
{
	pros::lcd::initialize();
	const double kP = 0.05;
	const double kI = 0;
	const double kD = 0;;

	uint32_t timeAtAngle = 0;

	auto controller = IterativeControllerFactory::posPID(kP, kI, kD);
	ADIGyro gyro(2, 0.092);
	gyro.reset();

	controller.setTarget(angle);
	
	do
	{
		double newInput = gyro.get();
		double newOutput = controller.step(newInput);
		drive->arcade(0, newOutput);


		pros::lcd::print(0, "Gyro: %f", newInput);
		pros::Task::delay(20);

		if(std::abs(newInput - angle) < 1 && timeAtAngle == 0)
		{
			timeAtAngle = pros::millis();
		}
		else if(std::abs(newInput - angle) >= 1)
		{
			timeAtAngle = 0;
		}
	}while(!(pros::millis() - timeAtAngle > 250 && timeAtAngle != 0));

	drive->stop();
}

void autonomous()
{
	pros::Vision vision_sensor = makeVisionSensor();

	//pros::lcd::initialize();
	//pros::lcd::clear();
	const double visionKP = 0.01;

	uint32_t startTime = pros::millis();

	bool allignedWithFlag = false;

	ChassisControllerIntegrated autoDrive = robotDrive.makeDrive();

	AsyncMotionProfileController* profileController;

	profileController = new AsyncMotionProfileController(
		TimeUtilFactory::create(),
		1.0,  // Maximum linear velocity of the Chassis in m/s
		1.0,  // Maximum linear acceleration of the Chassis in m/s/s
		10.0, // Maximum linear jerk of the Chassis in m/s/s/s
		autoDrive.getChassisModel(), // Chassis Controller
		autoDrive.getChassisScales(),
		autoDrive.getGearsetRatioPair()
	);

	profileController->startThread();

	switch(autonomousInfoStruct.mode)
	{
		case(DO_NOTHING):

		break;
		case(TEST):
			/*profileController->generatePath({
			  okapi::Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{5_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "A" // Profile name
			);

			profileController->setTarget("A");

			profileController->waitUntilSettled();*/

			turnAngleGyro(90, &autoDrive);
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
					autoDrive.arcade(0, turn * 127);
				}
				else
				{
					autoDrive.arcade(0, 0);
				}

				pros::delay(20);
			}

			robotShooter.set(127);
			pros::delay(1000);
			robotShooter.set(0);

			robotIntake.set(127);

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
