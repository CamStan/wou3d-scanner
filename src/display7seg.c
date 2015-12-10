
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
#include "mraa.h"
#include <stdint.h>

/*----- DEFINES SECTION -----*/

/*-- CMD --*/
#define CLEAR 0x76
#define DEC_CONTROL 0x77
#define RESET 0x81
#define BRIGHT_CONT 0x7A

/***VARS***/
static char display[4];
static char decimal_control[2];
static uint8_t err;
static mraa_uart_context uart;

/**
Reset

Sends factory RESET code to the display
*/
void display7seg_reset(){
	mraa_uart_write(uart, (char*) RESET, sizeof(RESET));
}
/**
Clear Screen

Sends the CLEAR screen command to the display
*/
void display7seg_clear(){
	mraa_uart_write(uart, (char*) CLEAR, sizeof(CLEAR));
}
/**
Init with custom BAUD

Allows initialization with a non-default Baud rate
useful in case a hardware change has altered the
default baud rate.

@param rx The Serial rx pin to use
@param BAUD Override for the BAUD rate
*/
//***----- Nix MAKE does not like overload, assuming this is a C89 vs C9x issue -----***//
//void display7seg_init(uint8_t rx, uint8_t baud){
//	uart = mraa_uart_init(rx);
//	mraa_uart_set_baudrate(uart, baud);
//}
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
}
/**
Set Brightness of display

Sets the displays brightness using values from 0
to 255.

@param  Brightness value to set brightness
*/
void display7seg_setBright(char Brightness){
	display7seg_sendCmd((char) BRIGHT_CONT, Brightness);
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
void display7seg_setDecimal(char on){
	if(on == 1){
		decimal_control[0] = 0x10;
	}
	if(on == 0){
		decimal_control[0] = 0x00;
	}
	if(on <= -1 || on >= 1){
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
void display7seg_setDegree(char on){
	if(on == 1){
		decimal_control[1] = 0x20;
	}
	if(on == 0){
		decimal_control[1] = 0x00;
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
void display7seg_sendCmd(char cmdType, char cmd){
	mraa_uart_write(uart, &cmdType,sizeof(cmdType));
	mraa_uart_write(uart, &cmd,sizeof(cmd));
}
/**
Display

Takes the values in the character array and 
the triggers for decimal and degree and sets
the display accordingly to show the information.
*/
void display7seg_Display(){
	mraa_uart_write(uart,&display[0],sizeof(display[0]));
	mraa_uart_write(uart,&display[1],sizeof(display[1]));
	mraa_uart_write(uart,&display[2],sizeof(display[2]));
	mraa_uart_write(uart,&display[3],sizeof(display[3]));
	mraa_uart_write(uart,(char*) DEC_CONTROL,sizeof(DEC_CONTROL));
	char dec = decimal_control[0] | decimal_control[1];
	mraa_uart_write(uart,&dec,sizeof(dec));
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
		decimal_control[0] = 0x00;
		decimal_control[1] = 0x00;
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
		//De-Init deprecated no longer in MRAA lib or needed.	
		//mraa_uart_deinit();
}
