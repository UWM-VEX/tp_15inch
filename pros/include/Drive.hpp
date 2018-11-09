#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

class Drive{
private:
	pros::Motor* frontLeft;
	pros::Motor* frontRight;
	pros::Motor* rearLeft;
	pros::Motor* rearRight;

public:
	Drive();
	void makeDrive (int frontLeftPort, int frontRightPort, int rearLeftPort, int rearRightPort);
	void tankDrive (int left, int right);
};

extern Drive robotDrive;

#endif