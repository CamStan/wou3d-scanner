/**
 * Test the stepper.h and stepper.c code.  Shows a simple example of using
 * stepper motors.
 */

#include <stdio.h>
#include <stdlib.h>

#include "stepper.h"

#define MOTOR1_STEP			7
#define MOTOR1_DIR			6
#define MOTOR1_EN			4

#define MOTOR2_STEP			10
#define MOTOR2_DIR			9
#define MOTOR2_EN			8

int main()
{
  struct StepperMotor * mot1 = stepper_init(MOTOR1_STEP,MOTOR1_DIR,MOTOR1_EN,400,16);
  stepper_setMotionParams(mot1,360,200,100);
  stepper_enable(mot1);

  struct StepperMotor * mot2 = stepper_init(MOTOR2_STEP,MOTOR2_DIR,MOTOR2_EN,200,16);
  stepper_setMotionParams(mot2,360,400,100);
  stepper_enable(mot2);

  int i;
  for (i = 0; i < 20; ++i)
  {
	  printf("%d\n",i);
	  stepper_rotate(mot1,360,CLOCKWISE);
      stepper_rotate(mot2,360,CLOCKWISE);
	  sleep(1);
	  stepper_rotate(mot1,360,COUNTERCLOCKWISE);
      stepper_rotate(mot2,360,COUNTERCLOCKWISE);
	  sleep(1);
  }

  stepper_close(mot1);
  stepper_close(mot2);
  return 0;
}
