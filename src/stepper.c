/*
 * stepper.c
 *
 */

#include "stepper.h"

#include <stdlib.h>			// for calloc
#include <unistd.h>         // for usleep
#include <stdio.h>


struct StepperMotor * stepper_init(int stepPin, int dirPin, int enPin, int stepsPerRevolution, int microstep)
{
	// allocate memory for one stepper motor struct (calloc fills memory with zeros)
	struct StepperMotor * mot = (struct StepperMotor *) calloc(1,sizeof(struct StepperMotor));
	if (mot == NULL)
	{
		fprintf(stderr, "stepper: Failed to allocate memory for StepperMotor\n");
		return NULL;
	}

	mot->pinContextSTEP = mraa_gpio_init(stepPin);
	mot->pinContextDIR = mraa_gpio_init(dirPin);
	mot->pinContextEN = mraa_gpio_init(enPin);
	if( mot->pinContextSTEP == NULL || mot->pinContextDIR == NULL || mot->pinContextEN == NULL )
	{
		fprintf(stderr, "stepper: Failed to initialize one or more pins for StepperMotor\n");
		free(mot);
		return NULL;
	}

	mraa_gpio_dir(mot->pinContextSTEP, MRAA_GPIO_OUT);
	mraa_gpio_dir(mot->pinContextDIR,  MRAA_GPIO_OUT);
	mraa_gpio_dir(mot->pinContextEN,   MRAA_GPIO_OUT);

	mraa_gpio_write(mot->pinContextEN, 1);			// active low
	mraa_gpio_write(mot->pinContextSTEP,0);
	mraa_gpio_write(mot->pinContextDIR,0);

	mot->stepsPerRevolution = stepsPerRevolution;
    mot->microstep = microstep;
	mot->maxDegreesPerSecond = DEFAULT_MAX_DEGREES_PER_SECOND;
	mot->degreesPerSecond = DEFAULT_DEGREES_PER_SECOND;
	mot->acceleration = DEFAULT_ACCELERATION;
	return mot;
}

void stepper_setMotionParams(struct StepperMotor * stepper, float maxSpeed, float speed, float accel)
{
    stepper->maxDegreesPerSecond = maxSpeed;
    stepper->degreesPerSecond = speed;
    stepper->acceleration = accel;
}

void stepper_setSpeed(struct StepperMotor * stepper, float speed)
{
    if(speed <= DEFAULT_MAX_DEGREES_PER_SECOND)
        stepper->degreesPerSecond = speed;
}

void stepper_setAcceleration( struct StepperMotor * stepper, float accel)
{
    stepper->acceleration = accel;
}

void stepper_enable( struct StepperMotor * stepper)
{
    mraa_gpio_write(stepper->pinContextEN, 0);			// active low
}

void stepper_disable( struct StepperMotor * stepper)
{
    mraa_gpio_write(stepper->pinContextEN, 1);			// active low
}

// TODO: should keep track of current error
// and add that back in for the next rotation, to avoid increasing cumulative error
// TODO: also add acceleration support
void stepper_rotate( struct StepperMotor * stepper, float degrees, enum StepDirection direction)
{
    if(direction == CLOCKWISE)
    {
        mraa_gpio_write(stepper->pinContextDIR,0);		// low is CW, high is CCW
    }
    else //if(direction == COUNTERCLOCKWISE)
    {
        mraa_gpio_write(stepper->pinContextDIR,1);
    }
    // need 200ns delay after setting dir
    int steps = (int)(stepper->stepsPerRevolution * stepper->microstep * degrees / 360.0f);
	unsigned int sleepTime = (unsigned int) (degrees / stepper->degreesPerSecond / steps / 2 / 1e-6);
    int i = 0;
    // Allegro A4988 moves motors on rising edge of step pin
    mraa_gpio_write(stepper->pinContextSTEP,0);

    for(i = 0; i < steps; ++i)
    {
        // motor driver advances one step on each rising edge of STEP
        mraa_gpio_write(stepper->pinContextSTEP,1);
        usleep(sleepTime);
        mraa_gpio_write(stepper->pinContextSTEP,0);
        usleep(sleepTime);
    }
}

void stepper_close( struct StepperMotor * stepper)
{
    mraa_gpio_write(stepper->pinContextEN,1);
    mraa_gpio_close(stepper->pinContextEN);
    mraa_gpio_write(stepper->pinContextDIR,0);  // don't leave output pins set to high
    mraa_gpio_close(stepper->pinContextDIR);
    mraa_gpio_write(stepper->pinContextSTEP,0);
    mraa_gpio_close(stepper->pinContextSTEP);
    free(stepper);                              // TELL USER NOT TO USE THIS NOW
}
