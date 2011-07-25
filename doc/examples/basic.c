#include <libbuddy/buddy.h>

int main(void)
{
	/**
	 * Create variable "buddy".
	 */
	buddy_t* buddy;

	/**
	 * Initialize "buddy" variable.
	 */
	buddy = buddy_init();
	
	/**
	 * Activate all i-Buddy gadgets avalaible.
	 */
	buddy_activate_all(buddy);

	/**
	 * Changes the states of all i-Buddy gadgets every second.
	 */
	buddy_state(buddy, HEART_OFF, LIGHT_BLUE, WING_DOWN, BODY_STOP);
	sleep(1);
	buddy_state(buddy, HEART_ON, LIGHT_GREEN, WING_STOP, BODY_RIGHT);
	sleep(1);
	buddy_state(buddy, HEART_OFF, LIGHT_RED, WING_STOP, BODY_LEFT);
	sleep(1);
	buddy_state(buddy, HEART_ON, LIGHT_YELLOW, WING_UP, BODY_RIGHT);
	sleep(1);

	/**
	 * Reset all i-Buddy gadgets.
	 */
	buddy_reset(buddy);

	/**
	 * Free memory used.
	 */
	buddy_free(buddy);
}

/**
 * gcc $(pkg-config libbuddy --cflags --libs) basic.c -o basic_example
 * ./basic_example
 */

