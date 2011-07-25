/* vim: set sts=4 sw=4 noet : */

/*      buddy.h
 *
 *      Copyright 2010 Francesc Gordillo <frangor+dev@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/**
 * @file buddy.h
 * @brief Main header file for libbuddy.
 */

#ifndef BUDDY_H
#define BUDDY_H 1

/**
 * Array of I-Buddy devices.
 */
typedef void buddy_t;

/**
 * Define the state of the heart.
 */
enum heart{
	HEART_OFF,
	HEART_ON
};

/**
 * Defines the color of the light.
 */
enum light{
	LIGHT_OFF,
	LIGHT_RED,
	LIGHT_GREEN,
	LIGHT_YELLOW,
	LIGHT_BLUE,
	LIGHT_MAGENTA,
	LIGHT_CYAN,
	LIGHT_WHITE
};

/**
 * Defines the position of the wings.
 */
enum wing{
	WING_STOP,
	WING_DOWN,
	WING_UP
};

/**
 * Defines the position of the boddy.
 */
enum body{
	BODY_STOP,
	BODY_RIGHT,
	BODY_LEFT
};

/**
 * Allocate and init a buddy array. The buddy array holds usb information
 * of all I-Buddy devices. You need to activate the devices you want to work.
 *
 * @see buddy_free
 */
struct buddy_t* buddy_init();

/**
 * Count the number of I-Buddy devices on a buddy array.
 *
 * @param buddy Buddy array.
 * @return Number of devices.
 */
int buddy_count(struct buddy_t *buddy);

/**
 * Enables all devices specified in the buddy array.
 *
 * @param buddy Buddy array.
 */
void buddy_activate_all(struct buddy_t *buddy);

/**
 * Enables a device specified.
 *
 * @param buddy Buddy.
 * @param device Device number to enable (0 the first device).
 * @return 0 to indicate proper operation.
 */
int buddy_activate(struct buddy_t *buddy, int device);

/**
 * Change the state of the actived i-Buddy devices specified on buddy array.
 *
 * @param buddy Buddy array.
 * @param h State of the heart.
 * @param l Color of the light.
 * @param w Position of the wings.
 * @param b Position of the boddy.
 */
void buddy_state(struct buddy_t *buddy,
		enum heart h, enum light l, enum wing w, enum body b);


/**
 * Reset the state of the actived i-Buddy devices specified on buddy array.
 *
 * @param buddy Buddy array.
 */
void buddy_reset(struct buddy_t *buddy);

/**
 * Disable a devices specified.
 *
 * @param buddy Buddy.
 * @param device Device number to deactivate (0 the first device).
 * @return 0 to indicate proper operation.
 */
int buddy_deactivate(struct buddy_t *buddy, int device);

/**
 * Disable all devices specified in the buddy array.
 *
 * @param buddy Buddy array.
 */
void buddy_deactivate_all(struct buddy_t *buddy);

/**
 * Completely free resources allocated of a buddy array.
 *
 * @param buddy Buddy array.
 */
void buddy_free(struct buddy_t *buddy);

#endif
