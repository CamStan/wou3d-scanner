#include "laser.h"
#include <stdio.h>
#include <stdlib.h>

float value = 0.5;

void initializeLazer(struct Laser *laser){
	laser -> laser_power = mraa_gpio_init(POWER);
	laser -> laser_vmod = mraa_pwm_init(VMOD);
	mraa_gpio_dir(laser -> laser_power, MRAA_GPIO_OUT );
}

void setPwmParameters(struct Laser *laser){
	mraa_pwm_period_us(laser -> laser_vmod, HERTZ);
}

void laserEnable(struct Laser *laser){
	mraa_pwm_enable (laser -> laser_vmod, 1);
}

void laserDisable(struct Laser *laser){
	mraa_pwm_enable (laser -> laser_vmod, 0);
}

void laserOn(struct Laser *laser){
	mraa_gpio_write(laser -> laser_power,1);
}

void laserOff(struct Laser *laser){
	mraa_gpio_write(laser -> laser_power,0);
}

void laser_setBrightness(struct Laser *laser, float value){
	mraa_pwm_write(laser -> laser_vmod, value);
}

void laser_setBrightnessLevelUp(struct Laser *laser){
	if(value >= 1.0)
	{
		value = 1.0;
	}
	else
		{
			value = value + 0.1;
		}
	mraa_pwm_write(laser -> laser_vmod, value);
}

void setBrightnessLevelDown(struct Laser *laser){
	// note that if brightness changed to quickly it will not function properly
	if(value <= 0.0)
	{
		value = 0.0;
	}
	else
		{
			value = value - 0.1;
		}
	mraa_pwm_write(laser -> laser_vmod, value);
}

void laser_close(struct Laser *laser){
	mraa_gpio_close(laser -> laser_power);
	mraa_pwm_close(laser -> laser_vmod);
}



