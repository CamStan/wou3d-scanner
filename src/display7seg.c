
/**
 * @display7seg.c
 * @author  Christopher Howard, Sam Wytoski, Charles
 * @version 1.0
 * @section DESCRIPTION
 *
 * Functionality for the Display 7-Segment Library
 * through uart serial control on a single pin.
 */
#include "display7seg.h"
#include <stdint.h>

/*----- DEFINES SECTION -----*/

/*-- CMD --*/
#define clear 0x76
#define dec_control 0x77
#define reset 0x81
#define bright_cont 0x7A

/***VARS***/
static char display[4];
static uint8_t dec_control[2];
static uint8_t err;
static mraa_uart_context uart;

/**
Reset

Sends factory reset code to the display
*/
void display7seg_reset(){
	mraa_uart_write(uart, reset);
}
/**
Clear Screen

Sends the clear screen command to the display
*/
void display7seg_clear(){
	mraa_uart_write(uart, clear);
}
/**
Init with custom BAUD

Allows initialization with a non-default Baud rate
useful in case a hardware change has altered the
default baud rate.

@param rx The Serial rx pin to use
@param BAUD Override for the BAUD rate
*/
void display7seg_init(uint8_t rx, uint8_t BAUD){
	uart = mraa_uart_init(rx);
	mraa_uart_set_baudrate(uart, BAUD);
}
/**
Initializer

Initializes the uart with a default baud rate of 9600
on the selected serial pin using the MRAA library.

@param  rx Serial pin to use
*/
void display7seg_init(uint8_t rx){
	uart = mraa_uart_init(rx);
	mraa_uart_set_baudrate(uart, 9600);
}

/**
Set Digit 1

Sets the digit 1 character in the array for
later display. This allows time delay and only
having to change a single digit for more dynamic
code ability.

@param  d Character to set this digit to
*/
void display7seg_setD1(char d){
	display[0] = d;
	display7seg_setDisplay(display);
}
/**
Set Digit 2

Sets the digit 2 character in the array for
later display. This allows time delay and only
having to change a single digit for more dynamic
code ability.

@param  d Character to set this digit to
*/
void display7seg_setD2(char d){
	display[1] = d;
	display7seg_setDisplay(display);
}
/**
Set Digit 3

Sets the digit 3 character in the array for
later display. This allows time delay and only
having to change a single digit for more dynamic
code ability.

@param  d Character to set this digit to
*/
void display7seg_setD3(char d){
	display[2] = d;
	display7seg_setDisplay(display);
}
/**
Set Digit 4

Sets the digit 4 character in the array for
later display. This allows time delay and only
having to change a single digit for more dynamic
code ability.

@param  d Character to set this digit to
*/
void display7seg_setD4(char d){
	display[3] = d;
	display7seg_setDisplay(display);
}
/**
Set Brightness of display

Sets the displays brightness using values from 0
to 255.

@param  Brightness value to set brightness
*/
void display7seg_setBright(uint8_t Brightness){
	display7seg_sendCmd(bright_cont, Brightness);
}

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
void display7seg_setDecimal(uint8_t on){
	if(on == 1){
		dec_control[0] = 0x10;
	}
	if(on == 0){
		dec_control[0] = 0x00;
	}
	if(on <= -1 || on >= 1){
		// Go to hell
		display7seg_setErrorState(1);
	}
}
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
void display7seg_setDegree(uint8_t on){
	if(on == 1){
		dec_control[0] = 0x20;
	}
	if(on == 0){
		dec_control[0] = 0x00;
	}
	if(on <= -1 || on >= 1){
		//Set the error state if incorrect boolean found
		display7seg_setErrorState(1);
	}
}

/**
Send Command

Allows for direct commands to be sent to the
screen. Useful if the hardware command set adds
new functionality in the future.

@param  cmdType The value of the command type to be sent to the display
@param cmd The actual command to be sent.
*/
void display7seg_sendCmd(uint8_t cmdType, uint8_t cmd){
	mraa_uart_write(uart,cmdType);
	mraa_uart_write(uart,cmd);
}
/**
Display

Takes the values in the character array and 
the triggers for decimal and degree and sets
the display accordingly to show the information.
*/
void display7seg_Display(){
	mraa_uart_write(uart,display[0]);
	mraa_uart_write(uart,display[1]);
	mraa_uart_write(uart,display[2]);
	mraa_uart_write(uart,display[3]);
	mraa_uart_write(uart,dec_control);
	mraa_uart_write(uart,(dec_control[0] | dec_control[1]));
}

/**
Set Error Code

Any non zero value as an error code will display
thet there is an error that has happened. Functionality
to get the code was planned but not completed, should
be simple to update later for code retrieval. As for 
now just set this to a non zero state to signal error.

@param  errorSet Error code to be set
*/
void display7seg_setErrorState(uint8_t errorSet){
	err = errorSet;
	display7seg_error();
}
/**
Display Error

If any error state is detected this function will
display on the screen an error has occurred.
*/
void display7seg_error(){
	if(err != 0){
		display[0] = 0x00;
		display[1] = 'E';
		display[2] = 'r';
		display[3] = 'r';
		dec_control[0] = 0x00;
		dec_control[1] = 0x00;
		display7seg_Display();
	}
}
/**
De-Initializer

This function closes the uart via the methods
described in the MRAA library.
*/
void display7seg_close(){
		mraa_uart_stop(uart);
		mraa_uart_deinit();
}