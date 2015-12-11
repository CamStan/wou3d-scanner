/**
 * @display7seg.h
 * @author  Christopher Howard, Sam Wytoski, Charles
 * @version 1.0
 * @section DESCRIPTION
 *
 * Header for the Display 7-Segment Library
 * through uart serial control on a single pin.
 */

#ifndef display7seg_H_
#define display7seg_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
/**
Reset

Sends factory reset code to the display
*/
void display7seg_reset();

/**
Clear Screen

Sends the clear screen command to the display
*/
void display7seg_clear();

/**
Init with custom BAUD

Allows initialization with a non-default Baud rate
useful in case a hardware change has altered the
default baud rate.

@param rx The Serial rx pin to use
@param BAUD Override for the BAUD rate
*/
//***----- Nix make does not like overload, assuming different C version issue here -----**//
//void display7seg_init(uint8_t rx, uint8_t baud);

/**
Initializer

Initializes the uart with a default baud rate of 9600
on the selected serial pin using the MRAA library.

@param  rx Serial pin to use
*/
void display7seg_init(uint8_t rx);
/**
Set Digit 1

Sets the digit 1 character in the array for
later display. This allows time delay and only
having to change a single digit for more dynamic
code ability.

@param  d Character to set this digit to
*/
void display7seg_setD1(char d);

/**
Set Digit 2

Sets the digit 2 character in the array for
later display. This allows time delay and only
having to change a single digit for more dynamic
code ability.

@param  d Character to set this digit to
*/
void display7seg_setD2(char d);

/**
Set Digit 3

Sets the digit 3 character in the array for
later display. This allows time delay and only
having to change a single digit for more dynamic
code ability.

@param  d Character to set this digit to
*/
void display7seg_setD3(char d);

/**
Set Digit 4

Sets the digit 4 character in the array for
later display. This allows time delay and only
having to change a single digit for more dynamic
code ability.

@param  d Character to set this digit to
*/
void display7seg_setD4(char d);

/**
Set Brightness of display

Sets the displays brightness using values from 0
to 255.

@param  Brightness value to set brightness
*/
void display7seg_setBright(uint8_t Brightness);

/**
Set Decimal Point on/off

Sets the decimal point to either on or off
1 = ON
0 = OFF
If an incorrect use of this function is found
sets an error state that can be viewed on the 
screen as " Err" for easy debugging.

@param  on Value of on or off
*/
void display7seg_setDecimal(uint8_t on);
/**
Set Degree Symbol on/off

Sets the degree symbol to either on or off
1 = ON
0 = OFF
If an incorrect use of this function is found
sets an error state that can be viewed on the 
screen as " Err" for easy debugging.

@param  on Value of on or off
*/
void display7seg_setDegree(uint8_t on);

/**
Send Command

Allows for direct commands to be sent to the
screen. Useful if the hardware command set adds
new functionality in the future.

@param  cmdType The value of the command type to be sent to the display
@param cmd The actual command to be sent.
*/
void display7seg_sendCmd(char cmdType, char cmd);
/**
Display

Takes the values in the character array and 
the triggers for decimal and degree and sets
the display accordingly to show the information.
*/
void display7seg_Display();

/**
Set Error Code

Any non zero value as an error code will display
thet there is an error that has happened. Functionality
to get the code was planned but not completed, should
be simple to update later for code retrieval. As for 
now just set this to a non zero state to signal error.

@param  errorSet Error code to be set
*/
void display7seg_setErrorState(uint8_t errorSet);
/**
Display Error

If any error state is detected this function will
display on the screen an error has occurred.
*/
void display7seg_error();
/**
De-Initializer

This function closes the uart via the methods
described in the MRAA library.
*/
void display7seg_close();

#ifdef __cplusplus
}
#endif

#endif  /* display7seg_H */
