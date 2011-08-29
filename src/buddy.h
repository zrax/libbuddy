/* vim: set sts=4 sw=4 noet : */

/*      buddy.h
 *
 *      Copyright 2011 Francesc Gordillo i Cortínez <frangor@gawab.com>
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
typedef unsigned int buddy_heart;

#define	BUDDY_OFF 0
#define	BUDDY_ON 1

/**
 * Defines the color of the light.
 */
typedef unsigned int buddy_light;

#define BUDDY_RED 1
#define BUDDY_GREEN 2
#define BUDDY_YELLOW 3
#define BUDDY_BLUE 4
#define BUDDY_MAGENTA 5
#define BUDDY_CYAN 6
#define BUDDY_WHITE 7

/**
 * Defines the position of the wings.
 */
typedef unsigned int buddy_wing;
 
#define BUDDY_DOWN 1
#define	BUDDY_UP 2

/**
 * Defines the position of the body.
 */
typedef unsigned int buddy_position;

#define BUDDY_RIGHT 1
#define BUDDY_LEFT 2

/**
 * Error handling.
 */
#define BUDDY_CORRECT 0
#define BUDDY_ERROR_USB -1
#define BUDDY_ERROR_DEVICE_OUT -2
#define BUDDY_ERROR_HEART_OUT -3
#define BUDDY_ERROR_LIGHT_OUT -3
#define BUDDY_ERROR_WING_OUT -4
#define BUDDY_ERROR_POSITION_OUT -5

/**
 * Allocate and init a buddy array. The buddy array holds usb information
 * of all I-Buddy devices. You need to activate the devices you want to work.
 * 
 * @return Buddy array.
 * @see buddy_free
 */
buddy_t* buddy_init();

/**
 * Count the number of I-Buddy devices on a buddy array.
 *
 * @param buddy Buddy array.
 * @return Number of devices.
 */
int buddy_count(buddy_t *buddy);

/**
 * Enables all devices specified in the buddy array.
 *
 * @param buddy Buddy array.
 * @return Error handling.
 */
int buddy_activate_all(buddy_t *buddy);

/**
 * Enables a device specified.
 *
 * @param buddy Buddy.
 * @param device Device number to enable (0 the first device).
 * @return Error handling.
 */
int buddy_activate(buddy_t *buddy, int device);

/**
 * Change the state of the actived i-Buddy devices specified on buddy array.
 *
 * @param buddy Buddy array.
 * @param heart State of the heart.
 * @param light Color of the light.
 * @param wing Position of the wings.
 * @param position Position of the boddy.
 * @return Error handling.
 */
int buddy_state(buddy_t *buddy,
		buddy_heart heart,
		buddy_light light,
		buddy_wing wing,
		buddy_position position);


/**
 * Reset the state of the actived i-Buddy devices specified on buddy array.
 *
 * @param buddy Buddy array.
 */
void buddy_reset(buddy_t *buddy);

/**
 * Disable a devices specified.
 *
 * @param buddy Buddy.
 * @param device Device number to deactivate (0 the first device).
 * @return 0 to indicate proper operation.
 */
int buddy_deactivate(buddy_t *buddy, int device);

/**
 * Disable all devices specified in the buddy array.
 *
 * @param buddy Buddy array.
 * @return Error handling.
 */
int buddy_deactivate_all(buddy_t *buddy);

/**
 * Completely free resources allocated of a buddy array.
 *
 * @param buddy Buddy array.
 */
void buddy_free(buddy_t *buddy);

#endif
