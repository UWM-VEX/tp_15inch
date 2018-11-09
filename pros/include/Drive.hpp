#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"

class Drive{
private:
	ChassisControllerIntegrated* chassis;
public:
	//Drive(int8_t frontLeft, int8_t frontRight, int8_t rearLeft, int8_t rearRight);
	Drive();
	void tankDrive(int left, int right);
	void makeDrive(int8_t frontLeft, int8_t frontRight, int8_t rearLeft, int8_t rearRight);
};

extern Drive robotDrive;

#endif