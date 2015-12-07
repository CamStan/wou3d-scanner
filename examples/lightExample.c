/**
* This file implements an API to operate a light
* through Intels MRAA library.
* @authors Howard Passmore, Danielle Sikich, Lauren Ryan
*/

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
	mraa_pwm_context pin;
	float currentBrightness; //duty cycle
        float period;
};

/**
* light struct
* Initializes the light and returns a struct representing the light.
* The brightness will be set to a default of 100 percent brightness.
* The period will be set to a default of 1000, which represents 5kHZ
* These two fields can be modified directly through the struct, or updated
* through the setBrightness or setParameters functions.
* @param  pinNumber Arduino pin number that this light is attached to
* @return           A pointer to the light struct, or NULL if it failed
*/
struct Light * light_init(int pinNumber);

/**
 * Set the period in the light struct
 * @param  light The light you wish to set up
 * @param  period Length of desired PWM period (in microseconds)
 * @return               N/A
 */
void light_setPeriod(struct Light * light, int period);

/**
 * Set the duty cycle for the brightness of the light
 * @param  light The light whose brightness will be changed
 * @param  brightness The brightness the light will be set to (between 0 and 1)
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
void light_enable(struct Light * light);

/**
* De-initializes (closes) the pin associated with the passed in
* light context.
* Also, frees memory for the light struct
* @param light Light that will be closed, and memory deallocated
* @return	    N/A
*/
void light_close(struct Light * light);


#ifdef __cplusplus
}
#endif

#endif  /* LIGHT_H */
