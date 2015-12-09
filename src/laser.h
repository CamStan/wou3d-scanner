/**
 * @authors Kim Marberry, Jared Staben, Matthew Stroud, Clara Pratt
 */
#ifndef LASER_H
#define LASER_H
#ifdef ___cplusplus
extern "C"{
#endif

#include "mraa.h"

// Laser Vmod (digital input to laser controller)
#define VMOD 3 // laser-controller depth of field maybe?
// Laser Power (MOSFET gate)
#define POWER 2 // gate
#define HERTZ 10 //sets the Hz to 100Hz
//sets contexts
struct Laser
{
        mraa_pwm_context laser_vmod;
        mraa_gpio_context laser_power;
        // initial brightness of laser
        float brightness; //this is a set starting brightness
        float step; //is the amount which you want to step the brightness
        int ON;
        int OFF;
};


// Function Prototypes


/**
 * InitialzerLazer
 * 
 */
void initializeLazer(struct Laser *laser);

/**
 * Sets the hertz
 * 
 */
void setPwmParameters(struct Laser *laser);

/**
 * Enables laser functionality
 * 
 */
void laserEnable(struct Laser *laser);

/**
 * Disables laser functionality
 * 
 */
void laserDisable(struct Laser *laser);

/**
 * Turns the power to the laser on
 * 
 */
void laserOn(struct Laser *laser);

/**
 * Turns the power to the laser off
 * 
 */
void laserOff(struct Laser *laser);

/**
 * set desired scan brightness
 * set brightness value from 0.1 to 1.0
 */

void laser_setBrightness(struct Laser *laser, float value);

/**
 * Increases the period to a maximum of 1.0
 * brightness = mraa_pwm_write(laser, brightness); brightness is can change by 0.1 + value
 */
void laser_setBrightnessLevelUp(struct Laser *laser);

/**
 * Decreases the period to a minimum of 0.1
 * brightness = mraa_pwm_write(laser, brightness); brightness is can change by 0.1 - value
 */
void setBrightnessLevelDown(struct Laser *laser);
/**
 * Zeros out the program
 * 
 */
void laser_close();

#ifdef __cplusplsu
}
#endif


#endif /* LASER_H */
