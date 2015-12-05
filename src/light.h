//		struct definitions (or union)
//		shared variables
 
/**
* This file implements an API to operate a light
* through Intels MRAA library.
* @authors Howard Passmore, Danielle Sikich, Lauren Ryan
*/

#ifndef LIGHT_H
#define LIGHT_H
 
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
* Set the parameters in the light struct
* Set the parameters in the light struct. Note this
* function does not modify the brightness of the light.
* @param  light The light you wish to set up
* @param  period Length of desired PWM period
* @return               N/A
*/
void light_setBrightness(struct Light * light, float brightness);
 
/**
* Disable the light output, and close the pin
* Disable the light output. Note this only shuts the light completely
* off, but the pin for the light will still be initialized. To close the
* pin, make a call to light_close
* @param  light Light that will be disabled
* @return           N/A
*/
void light_disable(struct Light * light);
 
/**
* Enable the light
* Turns the light back on. 
* @param  light Light that will be enabled.
* @return           N/A
*/
void light_enable(struct Lihgt * light);
 
/**
* De-initializes (closes) the pin associated with the passed in
* light context.
* @param light Light that will be closed.
* @return	    N/A
*/
void light_close(struct Light * light);
 
#ifdef __cplusplus
}
