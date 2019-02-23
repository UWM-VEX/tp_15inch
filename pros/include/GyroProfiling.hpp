#ifndef GYRO_PROFILING_H_
#define GYRO_PROFILING_H_

#include "main.h"
#include "okapi/api/control/async/asyncMotionProfileController.hpp"

class GyroProfiling : public okapi::AsyncMotionProfileController{
private:
	int gyroPort;
public:
	GyroProfiling(const okapi::TimeUtil &itimeUtil,
				  const double imaxVel,
				  const double imaxAccel,
				  const double imaxJerk,
				  const std::shared_ptr<okapi::ChassisModel> &imodel,
				  const okapi::ChassisScales &iscales,
				  okapi::AbstractMotor::GearsetRatioPair ipair)
				   : okapi::AsyncMotionProfileController(
					  itimeUtil,
					  imaxVel,
					  imaxAccel,
					  imaxJerk,
					  imodel,
					  iscales,
					  ipair)
	{};
	void setGyroPort(int port);
	void executeSinglePath(const TrajectoryPair &path, std::unique_ptr<okapi::AbstractRate> rate);
};

#endif