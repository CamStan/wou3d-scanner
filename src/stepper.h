/**
 * @file
 * @brief Control a stepper motor using the MRAA library.  The stepper motor is controlled
 * by a BigEasyDriver circuit board.  This library assumes you have the following pins
 * connected:
 * 		STEP
 * 		DIR
 * 		EN
 * 		POWER
 * 		GND
 * Microstep selection pins are not implemented.
 *
 */

// Because of the inherent error in positioning, we should be able to get the current angle
// TODO: Add float stepper_getCurrentAngle(struct StepperMotor *)
// Use this to zero the angle, or set it to a known angle before use
// TODO: Add void stepper_setCurrentAngle(struct StepperMotor *, float currentAngle)

#ifndef STEPPER_H_
#define STEPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mraa.h"

// TODO: Move these to hardware.h?
#define DEFAULT_MAX_DEGREES_PER_SECOND 	360
#define DEFAULT_DEGREES_PER_SECOND		10
#define DEFAULT_ACCELERATION			100

/**
 * Select the direction for the current rotation.
 */
enum StepDirection
{
	CLOCKWISE,
	COUNTERCLOCKWISE
};

/**
 * The struct holding all persistant information for this motor.  All functions need
 * a pointer to one of these, which should have been correctly initialized.  Don't create
 * one of these yourself, get one by calling stepperInit()
 */
struct StepperMotor
{
	mraa_gpio_context pinContextSTEP;
	mraa_gpio_context pinContextDIR;
	mraa_gpio_context pinContextEN;
	int stepsPerRevolution;
    int microstep;
	float maxDegreesPerSecond;
	float degreesPerSecond;
	float acceleration;				// in degrees/second^2
};

/**
 * Initialize a StepperMotor.  Call this first to set up a motor on 3 pins. Uses sane values
 * 								for speed and acceleration if you don't provide them in a
 * 								subsequent call.
 * @param  stepPin            Non-raw pin number corresponding to the STEP pin
 * @param  dirPin             Non-raw pin number corresponding to the DIR pin
 * @param  enPin              Non-raw pin number corresponding to the EN (enable) pin
 * @param  stepsPerRevolution Steps per revolution for the stepper motor you're using, see
 *                            documentation that came with your motor, typical value is 400
 * @param  microstep          The microstep size (i.e. 1,,2,4,8,16)
 * @return                    returns a pointer to the StepperMotor struct or NULL if one of
 *                            the pins could not be initialized.  This code "owns" this pointer.
 *                            The close() function frees this pointer.  Don't do it yourself. Not
 *                            calling close() and discarding the pointer leads to a memory leak.
 */
struct StepperMotor * stepper_init(int stepPin, int dirPin, int enPin, int stepsPerRevolution, int microstep);

/**
 * Set the motion parameters for this stepper motor.  No checking is made on these numbers.
 * @param stepper  Pointer to a properly initialized stepper motor struct for this motor
 * @param maxSpeed The maximum speed that should be allowed for this motor, in degrees per second
 * @param speed    Speed for movements in degrees per second
 * @param accel    Acceleration in degrees/s^2 (NOT CURRENTLY IMPLEMENTED)
 */
void stepper_setMotionParams(struct StepperMotor * stepper, float maxSpeed, float speed, float accel);

/**
 * Set the roation speed for this motor
 * @param stepper Pointer to a properly initialized stepper motor struct for this motor
 * @param speed   Speed for movements in degrees per second
 */
void stepper_setSpeed(struct StepperMotor * stepper, float speed);

/**
 * Set the acceleration for this motor
 * ACCELERATION IS NOT CURRENTLY IMPLEMENTED
 * @param stepper Pointer to a properly initialized stepper motor struct for this motor
 * @param accel   The acceleration in degrees/s^2
 */
void stepper_setAcceleration( struct StepperMotor * stepper, float accel);

/**
 * Enable this motor.  This sets the enable pin to low (EN pin is active low).  When enabled
 * stepper motors drive current through the windings and have holding torque.
 * @param stepper Pointer to a properly initialized stepper motor struct for this motor
 */
void stepper_enable( struct StepperMotor * stepper);

/**
 * Disable this motor.  This sets the enable pin to high (EN pin is active low).  Disabling
 * the motor eliminates holding torque, but also keeps the motors cool.
 * @param stepper Pointer to a properly initialized stepper motor struct for this motor
 */
void stepper_disable( struct StepperMotor * stepper);

/**
 * Rotate this motor through a given number of degrees in the given direction.
 * @param stepper   Pointer to a properly initialized stepper motor struct for this motor
 * @param degrees   Number of degrees to rotate through.  If the degrees given is not a multiple
 *                  of the degrees per step (or degrees/step/microstep when microstepping is
 *                  implemented) then there will be error in the position achieved
 * @param direction Direction to rotate, either CLOCKWISE or COUNTERCLOCKWISE
 */
void stepper_rotate( struct StepperMotor * stepper, float degrees, enum StepDirection direction);

/**
 * Close this motor.  This frees the StepperMotor struct memory, and closes the GPIO pins
 * used.  Do not use the associated pointer after making this call.
 * @param stepper Pointer to a properly initialized stepper motor struct for this motor
 */
void stepper_close( struct StepperMotor * stepper);


#ifdef __cplusplus
}
#endif
#endif /* STEPPER_H_ */
