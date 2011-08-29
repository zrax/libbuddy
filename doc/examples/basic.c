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
	buddy_state(buddy, BUDDY_OFF, BUDDY_BLUE, BUDDY_DOWN, BUDDY_OFF);
	sleep(1);
	buddy_state(buddy, BUDDY_ON, BUDDY_GREEN, BUDDY_OFF, BUDDY_RIGHT);
	sleep(1);
	buddy_state(buddy, BUDDY_OFF, BUDDY_RED, BUDDY_OFF, BUDDY_LEFT);
	sleep(1);
	buddy_state(buddy, BUDDY_ON, BUDDY_YELLOW, BUDDY_UP, BUDDY_RIGHT);
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

