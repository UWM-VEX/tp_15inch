#ifndef _VISION_H_
#define _VISION_H_

#define VISION_PORT 2

const uint8_t redFlagId = 1;
const uint8_t blueFlagId = 2;

pros::Vision makeVisionSensor();
int16_t getFlagX(pros::Vision vision_sensor);

#endif