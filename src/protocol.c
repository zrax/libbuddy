/* vim: set sts=4 sw=4 noet : */

/*      libuddy.c
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

#include <usb.h>
#include "protocol.h"


void buddy_msg(struct usb_dev_handle *udev, unsigned char msg)
{
	if(udev == NULL)
		return;

	unsigned char setup[] = {0x22, 0x09, 0x00, 0x02,
				0x01, 0x00, 0x00, 0x00};
	unsigned char header[] = {0x55, 0x53, 0x42, 0x43,
				0x00, 0x40, 0x02, 0xFF};
	header[7] = msg;
	
	usb_control_msg(udev, 0x21, 0x09, 0x02, 0x01, (char *) setup,
			sizeof(setup), 0);
	usb_control_msg(udev, 0x21, 0x09, 0x02, 0x01, (char *) header,
			sizeof(header), 0);
}
