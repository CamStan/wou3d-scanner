
#include "mraa.h"
#include <stdio.h>
#include <unistd.h>
#include "laser.h"

#include "hardware.h"

int main()
{
	struct Laser * laser = laser_init(LASER_VMOD,LASER_POWER);

	laser_setPeriod(laser, 10);
	laser_setBrightness(laser, 0.1);
	laser_on(laser);
	laser_enable(laser);
	sleep(2);
	laser_setBrightness(laser, 0.5);
	sleep(2);
	laser_setBrightness(laser, 0.8);
	sleep(2);
	laser_setBrightness(laser, 1.0);
	sleep(2);
	laser_setBrightness(laser, 0.5);
	sleep(2);
	laser_setBrightness(laser, 0.1);
	sleep(2);
	laser_disable(laser);
	laser_off(laser);
	laser_close(laser);

	return MRAA_SUCCESS;
}
