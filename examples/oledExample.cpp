/**
 * @file oledExample.cpp
 * @brief Test the functionality of the oled.h interface.
 *
 * @author Aaron Carson, Joseph Shin, Jason Gersztyn
 */

#include <cstdio>   // for printf
#include <unistd.h> // for usleep
#include "oled.h"   // to test interface

#define DEBUG

//----------------------------------------------------------------
// Testing method.
//----------------------------------------------------------------

/**
 * A test method using our OLED interface demonstrating a sequence of function
 * calls.
 *
 * NOTE: Use DEBUG macro to see print statements in console when the 
 * oled_printf() or oled_update() are called.
 */
void oled_test_interface()
{
	//---------------------
	// Initialize.
	//---------------------

	oled_init();
	oled_enable();
	printf("LCD Width:  %d\n", oled_getWidth());
	printf("LCD Height: %d\n", oled_getHeight());

	//-------------------------------
	// write and display some stuff.
	//-------------------------------
	oled_printf("Aaron ***\n"
				"Joseph\n"
				"This is a test.\n"
				"Jason!\n"
				"       lol\n");
	oled_setCursor(6, 1);
	oled_printf("Shin");
	oled_update();
	sleep(5);

	//---------------------
	// draw a box.
	//---------------------
	oled_clear();

	// draw sides.
	for (int i = 0; i < oled_getHeight(); i++)
	{
		oled_setCursor(i + 1, i);
		oled_printf("%d", i);
		oled_setCursor(0, i);
		oled_printf("|");
		oled_setCursor(9, i);
		oled_printf("|");
	}

	// draw top and bottom.
	oled_setCursor(0,0);
	oled_printf("+--------+");
	oled_setCursor(0,5);
	oled_printf("+--------+");

	oled_update();
	sleep(5);

	//---------------------------
	// turn screen on and off.
	//---------------------------
	for(int i = 0; i < 10; i++)
	{
		oled_disable();
		usleep(100000);

		// turn it back on.
		oled_enable();
		usleep(100000);

	}

	//---------------------
	// stop.
	//---------------------
	oled_close();
}


/**
 * Run the test.
 */
int main() {
	oled_test_interface();
	return 0;
}
