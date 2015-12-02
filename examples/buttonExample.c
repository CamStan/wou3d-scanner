
#include "button.c"


//Function Prototypes
void f1();
void f2();
void closeButtons();
struct button_context * buttonA;
struct button_context * buttonB;
struct button_context * buttonSelect;
int flag;
int main() {
	/* Setup your example here, code that should run once
	 */
	buttonA = button_init(PIN_A, &f1);
	buttonB = button_init(PIN_B, &f2);
	buttonSelect = button_init(PIN_SELECT, &closeButtons);
	flag = 0;
	/* Code in this loop will run repeatedly
	 */
	while(flag == 0) {
		//contiue until close()
	}
	button_close(buttonSelect);
	printf("Select closed\n");
	return 0;
}

void f1(){
	printf("A button pressed\n");
}

void f2(){
	printf("B button pressed\n");
}

void closeButtons(){
	printf("Select button pressed\n");
	button_close(buttonA);
	printf("A closed\n");
	button_close(buttonB);
	printf("B closed\n");
	flag = 1;
}