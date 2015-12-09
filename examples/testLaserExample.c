
#include "mraa.h"
#include <stdio.h>
#include <unistd.h>
#include "laser.h"



int main()
{
	struct Laser * laser;
	initializeLazer(&laser);
	setPwmParameters(&laser);
	laserEnable(&laser);
	laserOn(&laser);
	laser_setBrightness(&laser, 0.5);
	sleep(2);
	laser_setBrightnessLevelUp(&laser);
	sleep(1);
	laser_setBrightnessLevelUp(&laser);
	sleep(1);
	laser_setBrightnessLevelUp(&laser);
	sleep(2);
	setBrightnessLevelDown(&laser);
	sleep(1);
	setBrightnessLevelDown(&laser);
	sleep(1);
	setBrightnessLevelDown(&laser);
	sleep(1);
	setBrightnessLevelDown(&laser);
	sleep(2);
	laserDisable(&laser);
	sleep(1);
	laserOff(&laser);
	sleep(1);
	laser_close(&laser);

	return MRAA_SUCCESS;
}
