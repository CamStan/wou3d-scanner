/**
 * @file oled.cpp
 * @brief Control the OLED display: initialize, enable, disable, display
 * certain things, close.
 *
 * This is designed to be a simple interface for controlling the Edison OLED
 * display.
 *
 * @author Aaron Carson, Joseph Shin, Jason Gersztyn
 */

#include "oled.h"
#include <cstdio>   // for printf
#include <cstdlib>  // for malloc
#include <cstdarg>  // for vsnprintf, etc
#include <cstring>  // for memcpy
#include <cctype>   // for isprint
#include <unistd.h> // for sleep, usleep


//----------------------------------------------------------------
// our singleton OLED data
//----------------------------------------------------------------
edOLED * oled;
char * buffer; // copy of text on screen
int columns;   // width in characters
int rows;      // height in characters
int bufferIndex;    // index in buffer (equal column + row * columns)

//----------------------------------------------------------------
// private helper functions.
//----------------------------------------------------------------


/**
 * Helper function to find the minimum of 2 integers.
 * @param a The first integer.
 * @param v The second integer.
 * @return The minimum of both integers.
 */
int min(int a, int b)
{
	return a < b ? a : b;
}

/**
 * Set the value within the range of values
 * @param min the minimum value, inclusive.
 * @param max the maximum value, inclusive
 * @param n   The number to set.
 * @return If n is between min and max, it returns N.  Otherwise, min or max is
 *        returned if n < min or n > max. (if max < min then 0 is returned).
 */
int setWithinRange(int min, int max, int n)
{
	if (max < min) return 0;
	else return (n < min) ? min : (n > max) ? max : n;
}

/**
 * Helper function to calculate the index of the cursor based on
 * the column and row.  (by calculating column + row * columns)
 *
 * @param column The horizontal position of the cursor.
 * @param row    The vertical position of the cursor.
 */
int get_cursor_index(int column, int row)
{
	return column + row * columns;
}

/**
 * Helper function to clear the character buffer and reallocate with spaces.
 */
void clear_buffer()
{
	// free memory if allocated.
	if(buffer != NULL) free(buffer);
	//buffer = (char *)calloc(columns * rows + 1, sizeof(char));

	// buffer size is columns * rows + 1 for '\0' termination.
	int size = oled_calcBufferSize();
	//printf("buffer size: %d\n", size);
	buffer = (char *)malloc(size);

	// fill buffer with spaces.
	char blank = ' ';
	for(int i = 0; i < size - 1; i++)
	{
		buffer[i] = blank;
	}

	// null terminate the string.
	buffer[size - 1] = '\0';

}

//----------------------------------------------------------------
// oled.h implementation.
//----------------------------------------------------------------

/**
 * Initialize all memory needed.  Only call this once ultil oled_close().
 * Successive calls to oled_init() before calling oled_close() will have no effect.
 */
void oled_init()
{
	// only initialize oled if it is NULL.
	if (oled == NULL)
	{
		oled = new edOLED();
		oled->begin();
		columns = 10;
		rows    = 6;
		oled_clear(); // clear OLED display, set buffer, reset cursor.
	}
}

/**
 * Get the width of the OLED display, in columns (number of characters)
 * @return The width.
 */
int oled_getWidth()
{
	return columns;
}

/**
 * Get the height of the OLED display, in rows (number of characters)
 * @return The height.
 */
int oled_getHeight()
{
	return rows;
}

/**
 * Turns the OLED screen on, and displays the current info in the buffer.
 */
void oled_enable()
{
	//oled->clear(ALL);
	oled->clear(PAGE);

	// write prev text back to screen.
	oled_update();
}

/**
 * Turns the OLED screen off, but saves the data in the buffer.
 */
void oled_disable()
{
	// clear the screen, then update.
	oled->clear(PAGE);
	oled->display();
}

/**
 * Accepts arguments equivalent to printf and treats the OLED display as a
 * display.  The Final String when formatted cannot be larger than
 * calc_buffer_size(). (NOTE: use DEBUG macro for print statements in console)
 *
 * @param args The format string and optional arguments.
 */
void oled_printf(const char * format, ...)
{
	// 1. create tmp format buffer.
	int buffer_size = oled_calcBufferSize();
	char * newText = (char *) malloc(buffer_size);

	// 2. format the new string using the variable number of arguments.
	va_list args;
    va_start(args,format);
    vsnprintf(newText, buffer_size, format, args);
    va_end(args);

    // --------------------------------------------------------
    // if there is at least one newline, tokenize on newlines.
    // --------------------------------------------------------
    if(strchr(newText, '\n'))
    {
    	char * delimiter = "\n";
    	char * token = strtok(newText, delimiter);

    	// do up to "rows" times
    	while(token != NULL)
    	{
    		// write current token.
            int n = min(buffer_size - bufferIndex, strlen(token));
            memcpy(buffer + bufferIndex, token, n);

    		// advance cursor index to beginning of next row.
    		bufferIndex = ((bufferIndex + n) / columns + 1) * columns;
			#ifdef DEBUG
    		printf("token: \"%s\" length: %d\n", token, strlen(token));
    		printf("bufferIndex: %d\n", bufferIndex);
			#endif
    		// update x/y values.
    		//x = bufferIndex % columns;

    		int row = bufferIndex / columns;
    		if (row >= rows) break;                // Stop if below the screen.
    		else token = strtok(NULL, delimiter);  // Otherwise, get next token.
    	}
    }

    // --------------------------------------------------------
    // otherwise, write text directly, once.
    // --------------------------------------------------------
    else
    {
        int n = min(buffer_size - bufferIndex, strlen(newText));
        memcpy(buffer + bufferIndex, newText, n);
        bufferIndex += n;
    }

    //NOTE: edOLED is only updated from calls to oled_update().
	free(newText);
}

/**
 * Disable the screen, then free all allocated memory and release all resources.
 * After calling this function, oled_init() must be called again before the
 * OLED screen will function.
 */
void oled_close()
{
	oled_disable();
	delete oled;
}

/**
 * Clear the screen buffer, and set the cursor to 0,0.  Call this any time you
 * want to display something on a blank background.
 */
void oled_clear()
{
	// clear the buffer to blanks.
	clear_buffer();

	// clear the OLED buffer.
	oled->clear(PAGE);

	// reset OLED cursor and buffer cursor.
	oled_setCursor(0,0);
}

/**
 * Update the OLED display with the current screen buffer.
 */
void oled_update()
{
	// cursor must be at 0,0 to write entire buffer to screen.
	oled->setCursor(0,0);

	// write the buffer char by char.
	int length = strlen(buffer);
	for (int i=0; i<length; i++)
	{
		char c = buffer[i];
		if(isprint(c)) oled->write(c);
		else	       oled->write(' ');
	}

	// update the OLED display.
	oled->display();

	#ifdef DEBUG
	//see all characters in buffer.
	for(int i = 0; i < oled_calcBufferSize(); i++){
		char c = buffer[i];
		if (c!= '\n' && !isprint(c)) printf("\\0");
		else                         printf("%c", buffer[i]);
	}
	printf("\n");
	#endif
}

/**
 * @return The text currently in the buffer.
 */
char * oled_getBuffer()
{
	return buffer;
}

/**
 * Set the cursor position based on font width and height, not by pixel.
 *  @param column The horizontal cursor position.
 *  @param row    The vertical cursor position.
 */
void oled_setCursor(int column, int row)
{
	// ensure parameters are valid.
	column = setWithinRange(0, columns - 1, column);
	row    = setWithinRange(0, rows - 1, row);

	// update our bufferIndex representing the cursor.
	bufferIndex = get_cursor_index(column, row);

	// NOTE: edOLED cursor is only set when oled_update() is called.
}

/**
 * Calculate the buffer size (The max number of characters displayable on the
 * OLED screen).
 * @return The buffer size.
 */
int oled_calcBufferSize()
{
	return columns * rows * sizeof(char) + 1;
}

//----------------------------------------------------------------
// Initial test method.
//----------------------------------------------------------------

/**
 * A test method to check if the OLED screen is working.
 */
void oled_test()
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
	oled_printf("Aaron****\n"
				"Joseph\n"
				"This is a test.\n"
				"Jason!\n"
				"lol\n");
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

	//---------------------
	// turn on and off.
	//---------------------
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
