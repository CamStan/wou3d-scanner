/*
 * An example of the light being used.
 * Leave the light on for 3 seconds, and then turn it off
 */

#include "light.c"

int main()
{
	struct Light * light = light_init(LIGHT_SOURCE_PIN);

    /* You don't have to set the period and brightness because
	it will default to 100% brightness, and a period of 5kHZ.
	I am just doing it here to show that you can (if you so desire) */
	light_setPeriod(light, 2000);
	light_setBrightness(light, 0.5);

	light_enable(light);

	sleep(3);

	light_disable(light);
	light_close(light);

	return 0;
}
