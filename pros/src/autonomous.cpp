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

void turnAngleGyro(double angle, ChassisControllerIntegrated* drive, double maxSpeed = 0.5)
{
	pros::lcd::initialize();

	uint32_t timeAtAngle = 0;

	ADIGyro gyro(2, 0.092);
	gyro.reset();

	double newOutput;
	double newInput;
	
	do
	{
		newInput = gyro.get();

		if(std::abs(newInput - angle) > 10)
		{
			newOutput = 0.5;
		}
		else if(std::abs(newInput - angle) > 1)
		{
			newOutput = 0.2;
		}
		else
		{
			newOutput = 0;
		}

		if(angle - newInput < 0)
		{
			newOutput *= -1;
		}

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

	GyroProfiling* profileController;

	profileController = new GyroProfiling(
		TimeUtilFactory::create(),
		1.0,  // Maximum linear velocity of the Chassis in m/s
		0.5,  // Maximum linear acceleration of the Chassis in m/s/s
		5.0, // Maximum linear jerk of the Chassis in m/s/s/s
		autoDrive.getChassisModel(), // Chassis Controller
		autoDrive.getChassisScales(),
		autoDrive.getGearsetRatioPair()
	);

	profileController->setGyroPort(2);

	profileController->startThread();

	switch(autonomousInfoStruct.mode)
	{
		case(DO_NOTHING):

		break;
		case(TEST):
			profileController->generatePath({
			  okapi::Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{5_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "A" // Profile name
			);

			profileController->setTarget("A");

			profileController->waitUntilSettled();

			//turnAngleGyro(90, &autoDrive);
		break;
		case(SHOOT_2):
			/*startTime = pros::millis();

			while(!allignedWithFlag && pros::millis() - startTime < 3000)
			{
				int16_t flagX = getFlagX(vision_sensor);

				std::cout << "Flag X: " << (int) flagX << std::endl;

				double turn = flagX * visionKP;

				if(flagX > 5 || flagX < -5)
				{
					autoDrive.arcade(0, turn);
				}
				else
				{
					autoDrive.arcade(0, 0);
				}

				pros::delay(20);
			}*/

			robotShooter.set(127);
			pros::delay(1000);
			robotShooter.set(0);

			turnAngleGyro(-170, &autoDrive);

			profileController->generatePath({
			  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{30_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "lowFlag" // Profile name
			);

			profileController->setTarget("lowFlag", true);
			profileController->waitUntilSettled();

			profileController->removePath("lowFlag");

			robotFlipper.downBlocking();
			robotFlipper.upBlocking();

			profileController->generatePath({
			  okapi::Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{7_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "ball" // Profile name
			);

			robotIntake.set(127);
			profileController->setTarget("ball", false);
			profileController->waitUntilSettled();

			profileController->removePath("ball");

			turnAngleGyro(180, &autoDrive);

			profileController->generatePath({
			  okapi::Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{6_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "midFlag" // Profile name
			);

			profileController->setTarget("midFlag", false);
			profileController->waitUntilSettled();

			profileController->removePath("midFlag");

			startTime = pros::millis();

			allignedWithFlag = false;

			while(!allignedWithFlag && pros::millis() - startTime < 3000)
			{
				int16_t flagX = getFlagX(vision_sensor);

				std::cout << "Flag X: " << (int) flagX << std::endl;

				double turn = flagX * visionKP;

				if(flagX > 5 || flagX < -5)
				{
					autoDrive.arcade(0, turn);
				}
				else
				{
					autoDrive.arcade(0, 0);
				}

				pros::delay(20);
			}

			robotIntake.set(0);
			robotShooter.set(127);
			pros::delay(1000);
			robotShooter.set(0);

			robotFlipper.downBlocking();

			turnAngleGyro(90, &autoDrive);

			/*profileController->generatePath({
			  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{4_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "cap1" // Profile name
			);

			profileController->setTarget("cap1", true);
			profileController->waitUntilSettled();

			profileController->removePath("cap1");*/

			robotFlipper.upBlocking();

			turnAngleGyro(90, &autoDrive, 0.3);

			profileController->generatePath({
			  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{24_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "driveCap2" // Profile name
			);

			profileController->setTarget("driveCap2", false);
			profileController->waitUntilSettled();

			profileController->removePath("driveCap2");

			turnAngleGyro(70, &autoDrive);

			robotIntake.set(127);

			profileController->generatePath({
			  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{40_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "cap2" // Profile name
			);

			profileController->setTarget("cap2", false);
			profileController->waitUntilSettled();

			profileController->removePath("cap2");

			pros::delay(1000);

			profileController->generatePath({
			  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{24_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "back" // Profile name
			);

			profileController->setTarget("back", true);
			profileController->waitUntilSettled();

			profileController->removePath("back");

			turnAngleGyro(45, &autoDrive);

			robotIntake.set(0);

			startTime = pros::millis();

			allignedWithFlag = false;

			while(!allignedWithFlag && pros::millis() - startTime < 3000)
			{
				int16_t flagX = getFlagX(vision_sensor);

				std::cout << "Flag X: " << (int) flagX << std::endl;

				double turn = flagX * visionKP;

				if(flagX > 5 || flagX < -5)
				{
					autoDrive.arcade(0, turn);
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
		break;
		default:
		// Do nothing
		break;
	}
}
