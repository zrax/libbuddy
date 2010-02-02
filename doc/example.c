/*
 * Example file.
 */

#include <stdio.h>
#include <lib-buddy/buddy.h>

int main()
{
	struct buddy *bd;
	
	// Initialize buddy array of devices.
	bd = buddy_init();
	
	// Activate all buddy devices.
	buddy_activate_all(bd);
	
	// Send effects to all activated buddys.
	buddy_state(bd, HEART_OFF, LIGHT_BLUE, WING_DOWN, BODY_LEFT);
	sleep(1);
	buddy_state(bd, HEART_ON, LIGHT_WHITE, WING_UP, BODY_RIGHT);
	sleep(1);
	
	// Reset effects of all activated buddys.
	buddy_reset(bd);

	// Free buddy array.
	buddy_free(bd);
	return 0;
}
