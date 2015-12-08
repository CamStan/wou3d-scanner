
#include "button.c"

// variables
struct button_context * buttonA;
struct button_context * buttonB;
struct button_context * buttonSelect;
int flag;

// Function Prototypes
void f1();
void f2();
void closeButtons();

int main() {
    // initialize buttons with desired fucntions
	buttonA = button_init(PIN_A, &f1);
	buttonB = button_init(PIN_B, &f2);
	buttonSelect = button_init(PIN_SELECT, &closeButtons);

	flag = 0;

	while(flag == 0) {
		//contiue until close()
	}
    
    // close select button after it has triggered the flag
	button_close(buttonSelect);
	printf("Select closed\n");

	return 0;
}

/**
 * Function passsed to the A button. Prints when A button is pressed.
 */
void f1(){
	printf("A button pressed\n");
}

/**
 * Function passed to the B button. Prints when B button is pressed
 */
void f2(){
	printf("B button pressed\n");
}

/**
 * Function passed to the select button. Closes all other buttons, frees their
 * memory and triggers the flag to exit the continued while loop.
 */
void closeButtons(){
	printf("Select button pressed\n");
	button_close(buttonA);
	printf("A closed\n");
	button_close(buttonB);
	printf("B closed\n");
	flag = 1;
}
