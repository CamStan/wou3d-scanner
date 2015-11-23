/**
 * @file oled.cpp
 * @brief Implementation of oled.h
 */

#include "oled.h"


void test()
{
	edOLED * oled = new edOLED();
	oled->begin();
	oled->clear(ALL);
	oled->display();

	oled->clear(PAGE);
	oled->print("Hello, world!");
	oled->display();
	usleep(2000000);
	oled->clear(PAGE);
	oled->display();

	delete oled;
}
