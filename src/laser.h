/**
 * @file
 * @brief - this code initializes a struct laser that can be used to set brightness and turn on and off lasers
 * @authors Kim Marberry, Jared Staben, Matthew Stroud, Clara Pratt
 */
#ifndef LASER_H
#define LASER_H
#ifdef ___cplusplus
extern "C"{
#endif

#include "mraa.h"


/**
 * This is our struct for our Laser.
 * Our struct has two context pins needed for the functionality to work
 * There are two integer values to allow for turning the Laser on and off.
 * laser_vmod and laser_poer contain the pin numbers.
 */
struct Laser
{
        mraa_pwm_context laser_vmod;
        mraa_gpio_context laser_power;
       // initial brightness of laser
        int period;// this is value for the period
        int ON;
        int OFF;
};


// Function Prototypes


/**
 * This is our function that initializes our Laser struct.
 * It takes in two integers for the Laser module vMod and MOSFET gate power.
 * It creates a Laser struct, allocates memory for it, and set the pins to the two
 * pin contexts in the Laser struct.
 * It also sets the direction of the Laser.
 * @param power is the pin initializer.
 */
struct Laser* laser_init(int vMOD, int power);

/**
 * This function sets the period for the laser struct.
 * @param period sets the value for the PWM.
 */
void laser_setPeriod(struct Laser *laser, int period);

/**
 * Enables laser functionality.
 * @param laser, enable laser functionality on the given pin.
 */
void laser_enable(struct Laser *laser);

/**
 * Disables laser functionality.
 * @param disables the laser functionality on the given pin.
 */
void laser_disable(struct Laser *laser);

/**
 * Turns the power to the laser on.
 * @param turns the power to the pin on.
 */
void laser_on(struct Laser *laser);

/**
 * Turns the power to the laser off
 * @param turns the power of the pin to off
 */
void laser_off(struct Laser *laser);

/**
 * set desired scan brightness
 * set brightness value from 0.1 to 1.0
 * @param brightness is float value that can be adjusted between the given period to adjust the brightness of the laser.
 */
void laser_setBrightness(struct Laser *laser, float brightness);

/**
 * Zeros out the program
 * @param closes the pins of the GPIO and PWM, along with freeing up the memory used by the struct.
 */
void laser_close(struct Laser* laser);

#ifdef __cplusplus
}
#endif


#endif /* LASER_H */





