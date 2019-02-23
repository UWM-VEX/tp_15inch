#include "main.h"

using namespace okapi;

/*GyroProfiling::GyroProfiling(const TimeUtil &itimeUtil,
				  const double imaxVel,
				  const double imaxAccel,
				  const double imaxJerk,
				  const std::shared_ptr<ChassisModel> &imodel,
				  const ChassisScales &iscales,
				  AbstractMotor::GearsetRatioPair ipair) 
				  : okapi::AsyncMotionProfileController(
				  const TimeUtil &itimeUtil,
				  const double imaxVel,
				  const double imaxAccel,
				  const double imaxJerk,
				  const std::shared_ptr<ChassisModel> &imodel,
				  const ChassisScales &iscales,
				  AbstractMotor::GearsetRatioPair ipair)
				  {

				  }*/

void GyroProfiling::setGyroPort(int port)
{
	gyroPort = port;
}

void GyroProfiling::executeSinglePath(const TrajectoryPair &path, std::unique_ptr<AbstractRate> rate)
{
	const auto reversed = direction.load(std::memory_order_acquire);

	pros::lcd::initialize();
	pros::lcd::print(0, "Reversed %d", reversed);

	ADIGyro gyro(gyroPort, 0.092);
	gyro.reset();

	double gyroAngle;

    for (int i = 0; i < path.length && !isDisabled(); ++i) {
	    auto leftRPM = convertLinearToRotational(path.left[i].velocity * mps).convert(rpm);
	    auto rightRPM = convertLinearToRotational(path.right[i].velocity * mps).convert(rpm);

	    gyroAngle = gyro.get();

	    if(gyroAngle > 2)
	    {
	    	if(reversed < 0)
	    	{
	    		leftRPM += 5;
	    		rightRPM -= 5;
	    	}
	    	else
	    	{
	    		leftRPM -= 5;
	    		rightRPM += 5;
	    	}
	    }
	    else if(gyroAngle < -2)
	    {
	    	if(reversed < 0)
	    	{
	    		leftRPM -= 5;
	    		rightRPM += 5;
	    	}
	    	else
	    	{
	    		leftRPM += 5;
	    		rightRPM -= 5;
	    	}
	    	
	    }

	    if(leftRPM > 200)
	    {
	    	leftRPM = 200;
	    }
	    else if(leftRPM < -200)
	    {
	    	leftRPM = -200;
	    }

	    if(rightRPM > 200)
	    {
	    	rightRPM = 200;
	    }
	    else if(rightRPM < -200)
	    {
	    	rightRPM = -200;
	    }

	    model->left(leftRPM / toUnderlyingType(pair.internalGearset) * reversed);
	    model->right(rightRPM / toUnderlyingType(pair.internalGearset) * reversed);

	    rate->delayUntil(1_ms);
    }
}