/**
 * @file oled.h
 * @brief Control the OLED display: initialize, enable, disable, display certain things, close.
 *
 * This is designed to be a simple interface for controling the Edison OLED display.
 */

#ifndef WOU_3D_SCANNER_OLED_H
#define WOU_3D_SCANNER_OLED_H
#include "sparkfun/oled/Edison_OLED.h"
#include <unistd.h>


/**
 * A temporary test method to ensure our setup works.
 */
void oled_test();


/**
 * Initialize all memory needed
 */
void oled_init();

/**
 * Turns the OLED screen on, and displays the current info in the buffer.
 */
void oled_enable();

/**
 * Turns the OLED screen off, but saves the data in the buffer.,
 */
void oled_disable();

/**
 * Accepts arguments equivalent to printf and treats the OLED display as a display.
 * @param args The format string and optional arguments.
 */
void oled_printf(const char * args, ...);

/**
 * Free all allocated memory and release all resources.
 */
void oled_close();

/**
 * Clear the screen buffer.  Call this any time you want to display something on a blank
 * background.
 */
void oled_clear();

/**
 * Not sure yet.
 */
void oled_append();

/**
 * Update the OLED display with the current screen buffer.
 */
void oled_update();


/**
 * @return The text currently in the buffer.
 */
char * oled_getBuffer();



#endif /* WOU_3D_SCANNER_OLED_H */
