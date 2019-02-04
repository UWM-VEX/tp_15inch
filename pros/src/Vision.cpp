#include "main.h"

using namespace pros;

Vision makeVisionSensor()
{
	pros::Vision vision_sensor (VISION_PORT, pros::E_VISION_ZERO_CENTER);

	pros::vision_signature_s_t redFlag;
	redFlag.id = 1;
	redFlag.range = 7.3;
	redFlag.u_min = 7791;
	redFlag.u_max = 8107;
	redFlag.u_mean = 7949;
	redFlag.v_min = -1119;
	redFlag.v_max = -639;
	redFlag.v_mean = -879;
	redFlag.rgb = 9784645;
	redFlag.type = 0;

	vision_sensor.set_signature(redFlagId, &redFlag);

	pros::vision_signature_s_t blueFlag;
	blueFlag.id = 2;
	blueFlag.range = 5.6;
	blueFlag.u_min = -2353;
	blueFlag.u_max = -1969;
	blueFlag.u_mean = -2161;
	blueFlag.v_min = 7341;
	blueFlag.v_max = 8323;
	blueFlag.v_mean = 7832;
	blueFlag.rgb = 2503520;
	blueFlag.type = 0;

	vision_sensor.set_signature(blueFlagId, &blueFlag);

	vision_sensor.set_exposure(15);

	return vision_sensor;
}

int16_t getFlagX(pros::Vision vision_sensor)
{
	pros::vision_object_s_t flagToTrack;

	if(autonomousInfoStruct.alliance == RED)
	{
		flagToTrack = vision_sensor.get_by_sig(0, blueFlagId);
	}
	else
	{
		flagToTrack = vision_sensor.get_by_sig(0, redFlagId);
	}

	return flagToTrack.x_middle_coord;
}