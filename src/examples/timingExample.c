#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "mraa.h"

/*
 * This example shows how to access a high resolution timer in Linux
 * in order to do useful time-controlled things.  Here that means
 * controlling the width of a pulse output on a particular pin.
 *
 * Run this on the base station and set the pin for the built-in LED,
 * the laser or the light source.
 *
 * This code needs to be linked against librt by adding -lrt to
 * the linker args.
 *
 */

#define PIN			7			// 7 is the red LED in Lab 2, 13 for on-board LED
#define FREQUENCY	1000		// in Hz

//#define SHOW_LEVELS

// Exit nicely
void quitHandler(int);		// handle SIGINT  signal

// shared variables
mraa_gpio_context pin;

int main()
{
	signal(SIGINT, quitHandler);
	pin = mraa_gpio_init(PIN);
	mraa_gpio_dir(pin, MRAA_GPIO_OUT);

	float level = 0;
	float changeAMT = 0.1;
	float change = changeAMT;

	// let's assume time interval is less than one second
	struct timespec t1, t2;
	unsigned int period = (unsigned int)(1.0/FREQUENCY/1.0e-9);
	unsigned int on;
	unsigned int t;

	printf("period = %d\n",period);

	for (;;)
	{
		on  = (unsigned int)(period*level/100);

		// get start time
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
		// pin HIGH
		mraa_gpio_write(pin, 1);
		t = 0;
		while( t < on )			// wait for on # of nanoseconds
		{
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
			t = t2.tv_nsec-t1.tv_nsec;
		}
		// pin LOW
		mraa_gpio_write(pin, 0);
		while( t < period )		// wait until period nanoseconds is up
		{
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
			t = t2.tv_nsec-t1.tv_nsec;
		}
		// increment and roll over level for dramatic effect
		level += change;
		if(level > 100.0)
			change = -changeAMT;
		else if( level < 0 )
			change = +changeAMT;
#ifdef SHOW_LEVELS
		if((int)level % 10 == 0)
			printf("Level = %f\n",level);
#endif
	}

	return EXIT_SUCCESS;
}

/* Receive the SIGINT (CTRL+C) signal.  Clean up and quit. */
void quitHandler(int sig)
{
	if (sig == SIGINT)
	{
		 printf("Exiting");
		 mraa_gpio_close(pin);
	}
	exit(EXIT_SUCCESS);
}
