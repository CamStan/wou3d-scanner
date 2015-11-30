
#include "button.c"


//Function Prototypes
void f1();
void f2();

int main() {
	/* Setup your example here, code that should run once
	 */
	button_init(49, &f1);
	button_init(46, &f2);
	
	/* Code in this loop will run repeatedly
	 */
	for (;;) {
		//
	}

	return 0;
}

void f1(){
	printf("A button pressed\n");
}

void f2(){
	printf("B button pressed\n");
}