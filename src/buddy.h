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

#ifndef BUDDY_H
#define BUDDY_H 1

typedef struct buddy{
	struct usb_device *dev;
	struct usb_dev_handle *udev;
	struct buddy *next;
}buddy;

enum heart{
	HEART_OFF,
	HEART_ON
};

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

enum wing{
	WING_DOWN = 1,
	WING_UP = 2
};

enum body{
	BODY_RIGHT = 1,
	BODY_LEFT = 2
};

struct buddy * buddy_init();

int buddy_count(struct buddy *bd);

void buddy_activate_all(struct buddy *bd);
void buddy_activate(struct buddy *bd);

void buddy_state(struct buddy *bd, 
		enum heart h, enum light l, enum wing w, enum body b);

void buddy_deactivate(struct buddy *bd);
void buddy_deactivate_all(struct buddy *bd);

void buddy_free(struct buddy *bd);

#endif
