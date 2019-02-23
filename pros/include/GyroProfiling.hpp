#ifndef GYRO_PROFILING_H_
#define GYRO_PROFILING_H_

#include "main.h"
#include "okapi/api/control/async/asyncMotionProfileController.hpp"

class GyroProfiling : public AsyncMotionProfileController{
private:
	int gyroPort;
public:
	void setGyroPort(int port);
	void executeSinglePath(const TrajectoryPair &path, std::unique_ptr<AbstractRate> rate);
};

#endif