#ifndef _TURNER_HPP_
#define _TURNER_HPP_

class Turner{
	pros::Motor* driver;
public:
	Turner();
	void makeTurner(int driverPort);
	void set(int speed);
};

extern Turner robotTurner;

#endif