#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"

class Drive{
private:
	
public:
	Drive(int8_t frontLeft, int8_t frontRight, int8_t rearLeft, int8_t rearRight);
	void tankDrive(int left, int right);
};

extern Drive robotDrive;

#endif