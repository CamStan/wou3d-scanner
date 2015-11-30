#include <mraa.h>


// pins associated with each button
#define PIN_A  		49
#define PIN_B  		46
#define PIN_UP  	47
#define PIN_DOWN	44
#define PIN_LEFT 	165
#define PIN_RIGHT  	45
#define PIN_SELECT  48


#define BIT_MASK	0x80

//set thresholds
#define PRESS_THRESHOLD 	0x3F
#define RELEASE_THRESHOLD 	0xFC


/**
 * Function used to run buttons on each thread.
 */
void * buttonThread(void*);
/**
 * This struct will be passed into a button's thread.
 */
struct button_context{
	mraa_gpio_context gpio_button_context;
	void (*action)();
	unsigned char bits;
	pthread_t * thread;
};


/**
 * Initialize the button on a pin to operate on a thread and run a function when pressed.
 * For example: If you want the A Button pressed to excute the function *move_mtr(),
 * 		write:		button_init(PIN_A, buttonA, move_mtr);
 *
 */
struct button_context * button_init(int, void*);

/**
 * Change the callback function used with a button_context.
 */
void button_update_function(struct button_context*, void*);

/**
 * deallocate memory for a button_context and its members.
 */
void button_close(struct button_context*);
