/**
 * @file oled.cpp
 * @brief Implementation of oled.h
 */

#include "oled.h"


void oled_test()
{
	edOLED * oled = new edOLED();
	oled->begin();
	oled->clear(ALL);
	oled->display();

	oled->clear(PAGE);
	oled->print("Hello, world!");
	oled->print("This is more text.");
	oled->print("\n");
	oled->display();
	usleep(2000000);
	oled->clear(PAGE);
	oled->display();

	delete oled;
}


