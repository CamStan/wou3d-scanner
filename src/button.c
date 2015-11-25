#include <stdio.h>
#include <stdlib.h>
#include "button.h"

int main() {
	/* Setup your example here, code that should run once
	 */

	/* Code in this loop will run repeatedly
	 */
	button_init(49, &f1);
	button_init(46, &f2);
	for (;;) {


	}

	return 0;
}

void f1(){
	printf("A button pressed\n");
}

void f2(){
	printf("B button pressed\n");
}




void * buttonThread(void * args) {
	int value;
	struct button_context * context = (struct button_context*) args;
	uint8_t shiftReg = 0xFF;

	for (;;) {

		value = mraa_gpio_read(context->gpio_button_context);

		shiftReg >>= 1;

		if (value == 1) {
			shiftReg |= BIT_MASK;
		}
		if (context->bits == 0) {
			if (shiftReg >= RELEASE_THRESHOLD) {
				//Button has been released.
				context->bits = 1;
			}
		} else {
			if (shiftReg <= PRESS_THRESHOLD) {
				//Button has been pressed.
				context->action();
				context->bits = 0;
			}
		}
		usleep(500);
	}

}


struct button_context * button_init(int pin, void * args){

	struct button_context * button_action = calloc(1, sizeof(button_action));

	button_action->gpio_button_context = mraa_gpio_init_raw(pin);
	if (mraa_gpio_dir(button_action->gpio_button_context, MRAA_GPIO_IN) != MRAA_SUCCESS)
	{
		fprintf(stderr, "Coulnd't initialize GPIO on pin %d, exiting", pin);
		exit(MRAA_ERROR_UNSPECIFIED);
	}

	button_action->action = args;
	button_action->bits = 1;
	button_action->thread = calloc(1, sizeof(button_action->thread));

	pthread_create(button_action->thread, NULL, &buttonThread, button_action);
	return button_action;
}

void button_update_function(struct button_context * context, void * args){
	pthread_create(context->thread, NULL, &buttonThread, args);
}

void button_close(struct button_context * context){
	 free(context->thread);
	 mraa_gpio_close(context->gpio_button_context);
	 free(context);
}