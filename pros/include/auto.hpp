#ifndef AUTO_H_
#define AUTO_H_

struct AutonomousInfo {

	int mode;
	int alliance;

}typedef AutonomousInfo;

extern AutonomousInfo autonomousInfoStruct;

#define DO_NOTHING 0
#define TEST 1
#define MOTION_PROFILE 2
#define SHOOT_2 3

#endif