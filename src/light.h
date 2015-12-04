// light.h
// public interface file
// 		function declarations (prototypes)
// 		constants
//		struct definitions (or union)
//		shared variables

#ifndef LIGHT_H
#define LIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mraa.h"
#include "hardware.h"

/**
 * struct that holds information for a light.
 * Holds pointer to light pin, as well as the current
 * brightness and period of the light.
 */
struct Light
{
	mraa_pwm_context pin;	 // "instance variables"
	float currentBrightness; //duty cycle
    float period;
};

/**
 * light struct
 * @param  pinNumber Arduino pin number that this light is attached to
 * @return           A pointer to the light struct, or NULL if it failed
 */
struct Light * light_init(int pinNumber);

/**
 * Set the parameters in the light struct
 * @param  light The light you wish to set up
 * @param  period Length of desired PWM period
 * @return               N/A
 */
void light_setParameters(struct Light * light, float period);

/**
 * Set the duty cycle for the brightness of the light
 * @param  light The light whose brightness will be changed
 * @param  brightness The brightness the light will be set to.
 * @return           N/A
 */
void light_setBrightness(struct Light * light, float brightness);

/**
 * Disable the light output, and close the pin
 * @param  light Light that will be disabled
 * @return           N/A
 */
void light_disable(struct Light * light);

/**
 * Enable the light
 * @param  light Light that will be enabled.
 * @return           N/A
 */
void light_enable(struct Lihgt * light);


#ifdef __cplusplus
}
#endif

#endif  /* LIGHT_H */
