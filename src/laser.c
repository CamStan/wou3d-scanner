#include "laser.h"
#include "mraa.h"
//Add a comment to this line
#include <stdio.h>
#include <stdlib.h>


struct Laser* laser_init(int vMOD, int power){

	struct Laser * laser = (struct Laser*) calloc(1, sizeof(struct Laser));
	laser->period = 10;
	laser -> laser_power = mraa_gpio_init(power);
	laser -> laser_vmod = mraa_pwm_init(vMOD);
	mraa_gpio_dir(laser -> laser_power, MRAA_GPIO_OUT );

	return laser;
}

void laser_setPeriod(struct Laser *laser, int period){
	mraa_pwm_period_us(laser -> laser_vmod, laser->period);
}

void laser_enable(struct Laser *laser){
	mraa_pwm_enable (laser -> laser_vmod, 1);
}

void laser_disable(struct Laser *laser){
	mraa_pwm_enable (laser -> laser_vmod, 0);
}

void laser_on(struct Laser *laser){
	mraa_gpio_write(laser -> laser_power,1);
}

void laser_off(struct Laser *laser){
	mraa_gpio_write(laser -> laser_power,0);
}

void laser_setBrightness(struct Laser *laser, float brightness){
	mraa_pwm_write(laser -> laser_vmod, brightness);
}


void laser_close(struct Laser *laser){
    mraa_gpio_close(laser -> laser_power);
	mraa_pwm_close(laser -> laser_vmod);
	free(laser);
}




