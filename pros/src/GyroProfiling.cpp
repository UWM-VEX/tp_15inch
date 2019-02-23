#include "main.h"

using namespace okapi;

GyroProfiling::setGyroPort(int port)
{
	gyroPort = port;
}

void GyroProfiling::executeSinglePath(const TrajectoryPair &path, std::unique_ptr<AbstractRate> rate)
{
	const auto reversed = direction.load(std::memory_order_acquire);

	ADIGyro gyro(gyroPort, 0.092);
	gyro.reset();

	double gyroAngle;

    for (int i = 0; i < path.length && !isDisabled(); ++i) {
	    const auto leftRPM = convertLinearToRotational(path.left[i].velocity * mps).convert(rpm);
	    const auto rightRPM = convertLinearToRotational(path.right[i].velocity * mps).convert(rpm);

	    gyroAngle = gyro.get();

	    if(gyroAngle > 2)
	    {
	    	leftRPM -= 20;
	    	rightRPM += 20;
	    }
	    else if(gyroAngle < 2)
	    {
	    	leftRPM += 20;
	    	rightRPM -= 20;
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