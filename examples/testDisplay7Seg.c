#include 'display7seg.h'
#include <unistd.h>
#include <stdio.h>
int main()
{
	//Initialize the 7-seg display on RX pin 2
	display7seg_init(2);
	//Set the digits to be used and colon/degree symbols on
    display7seg_setD1('A');
	display7seg_setD2('B');
	display7seg_setD3('C');
	display7seg_setD4('D');
	display7seg_setDegree(1);
	DISPLAY7_setDecimal(1);
	//Turn set the values to show
	display7seg_Display();
	//Leave for 4 seconds on screen so we know it worked
	sleep(4);
	//Clear the screen
	display7seg_clear();
	//Deinit 7SEG 
	display7seg_close();
	return 0;
}