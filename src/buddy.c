/* vim: set sts=4 sw=4 noet : */

/*      buddy.c
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

#include <usb.h>
#include "buddy.h"
#include "protocol.h"

typedef struct buddy_tp {
	struct usb_device *dev;
	struct usb_dev_handle *udev;
	struct buddy_tp *next;
}buddy_tp;

struct buddy_t* buddy_init()
{
	struct usb_bus *busses;
	struct usb_bus *bus;
	struct usb_device *dev;
	struct buddy_tp *bd, *new, *aux;

	bd = NULL;

	usb_init();
	usb_find_busses();
	usb_find_devices();
	
	busses = usb_get_busses();

    	for (bus = busses; bus; bus = bus->next) {
    		for (dev = bus->devices; dev; dev = dev->next) {
			if (dev->descriptor.idVendor != 4400)
				continue;
			new = (struct buddy_tp *) malloc(sizeof (struct buddy_tp));
			new->dev = dev;
			new->udev = NULL;
			new->next = NULL;

			if (bd == NULL)
			{
				bd = new;
				continue;
			}

			aux = bd;
			
			while (aux->next != NULL)
				aux = aux->next;
			
			aux->next = new;
		}
	}

	return (buddy_t*) bd;
}

void buddy_free(struct buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if (bd == NULL)
		return;

	if (bd->next != NULL)
		buddy_free((buddy_t*) bd->next);

	buddy_deactivate((buddy_t*) bd);
	free(bd);
}

int buddy_count(struct buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	struct buddy_tp *aux;
	int count;

	count = 0;

	for (aux = bd; aux; aux = aux->next)
		count++;

	return count;
}

void buddy_activate(struct buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if(bd->udev != NULL)
		return;

	bd->udev = usb_open(bd->dev);
	usb_detach_kernel_driver_np(bd->udev, 0);
	usb_detach_kernel_driver_np(bd->udev, 1);
	usb_set_configuration(bd->udev, bd->dev->config->bConfigurationValue);
	usb_claim_interface(bd->udev,
			bd->dev->config->interface->altsetting->bInterfaceNumber);
	usb_set_altinterface(bd->udev,
			bd->dev->config->interface->altsetting->bAlternateSetting);
}

void buddy_deactivate(struct buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if(bd->udev == NULL)
		return;

	usb_close((buddy_t*) bd->udev);
	bd->udev = NULL;
}

void buddy_activate_all(struct buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if(bd == NULL)
		return;

	buddy_activate_all((buddy_t*) bd->next);
	buddy_activate((buddy_t*) bd);
}

void buddy_deactivate_all(struct buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if(bd == NULL)
		return;

	buddy_deactivate_all((buddy_t*) bd->next);
	buddy_deactivate((buddy_t*) bd);
}

void buddy_state(struct buddy_t *buddy,
		enum heart h, enum light l, enum wing w, enum body b)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if(bd == NULL)
		return;
	
	buddy_state((buddy_t*) bd->next, h, l, w, b);

	unsigned char msg;
	
	msg = 0xFF;
	msg ^= h << 7;
	msg ^= l << 4;
	msg ^= w << 2;
	msg ^= b;

	buddy_msg(bd->udev, msg);
}

void buddy_reset(struct buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if(bd == NULL)
		return;

	buddy_msg(bd->udev, 0xFF);
}

