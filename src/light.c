#include "light.h"
#include <stdio.h>
#include <stdlib.h>


struct Light * light_init(int pinNumber)
{
    struct Light * light = (struct Light *) calloc(1,sizeof(struct Light));
    if( light == NULL )
    {
        fprintf(stderr, "light could not be initialized, memory allocation failure");
        return NULL;
    }

    light->pin = mraa_pwm_init(pinNumber);

    //set period and brightness to default values when light is initialized
    mraa_pwm_period_us(light->pin, LIGHT_SOURCE_PERIOD);
    mraa_pwm_write(light->pin, LIGHT_SOURCE_BRIGHTNESS);

    return light;
}


void light_setPeriod(struct Light * light, int period)
{
    mraa_pwm_period_us(light->pin, period);
}

void light_setBrightness(struct Light * light, float brightness)
{
	mraa_pwm_write(light->pin, brightness);
}

void light_disable(struct Light * light)
{
    mraa_pwm_enable(light->pin, 0);
}

void light_enable(struct Light * light)
{
	mraa_pwm_enable(light->pin, 1);
}

void light_close(struct Light * light)
{
	mraa_pwm_close(light->pin);
	free(light);
}
