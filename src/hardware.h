#ifndef HARDWARE_H_DEFS
#define HARDWARE_H_DEFS

/**
 * @file
 * @brief Shared project definitions, hardware setup
 *
 * Values that define the specific hardware setup of this
 * project and that need to be shared amongst files.
 * Included are:
 * 		Pin numbers
 * 		Default and starting values
 *
 * Pins used are Arduino expansion board pin numbers unless
 * otherwise noted
 */

// Stepper motors
// These pins go to individual BigEasy Driver boards/
#define MOTOR1_STEP         7
#define MOTOR1_DIR	        6
#define MOTOR1_EN	        4

#define MOTOR2_STEP         10
#define MOTOR2_DIR          9
#define MOTOR2_EN           8

/**
 *  LED light source MOSFET gate power supply pin -- drive high to power
 *  on the light source, or use PWM to dim
 */
#define LIGHT_SOURCE_PIN	    5
#define LIGHT_SOURCE_PERIOD         200 //default represents 5kHZ (period is in microseconds)
#define LIGHT_SOURCE_BRIGHTNESS     1 //default light brightness is 1 (100% brightness)
/**
 * Laser module MOSFET gate power supply pin -- drive high to power on
 * the laser module
 */
#define LASER_POWER 		2
/**
 * Laser module Vmod input (analog modulation signal) -- set fixed value
   to set fixed brightness or use PWM to dim
 */
#define LASER_VMOD  		3

#endif /* end of include guard: HARDWARE_H_DEFS */
