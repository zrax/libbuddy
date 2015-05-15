/* vim: set sts=4 sw=4 noet : */

/*      buddy.c
 *
 *      Copyright 2011 Francesc Gordillo i Cortínez <frangor@lavabit.com>
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

#include <stdlib.h>
#include <libusb.h>
#include "buddy.h"
#include "protocol.h"

typedef struct buddy_tp {
	libusb_context *ctx;
	libusb_device *dev;
	libusb_device_handle *udev;
	struct buddy_tp *next;
} buddy_tp;

static int buddy_act(struct buddy_tp *buddy);
static int buddy_deact(struct buddy_tp *buddy);

buddy_t* buddy_init()
{
	libusb_context *ctx;
	libusb_device *dev, **devices;
	struct libusb_device_descriptor desc;
	struct buddy_tp *bd, *new, *aux;
	ssize_t devcnt, i;

	bd = NULL;

	if (libusb_init(&ctx) != 0)
		return NULL;

	devcnt = libusb_get_device_list(ctx, &devices);

	for (i = 0; i < devcnt; ++i) {
		dev = devices[i];
		libusb_get_device_descriptor(dev, &desc);
		if (desc.idVendor != 4400)
			continue;
		new = (struct buddy_tp *) malloc(sizeof (struct buddy_tp));
		new->ctx = ctx;
		new->dev = libusb_ref_device(dev);
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

	libusb_free_device_list(devices, 1);

	return (buddy_t*) bd;
}

static void buddy_free_r(buddy_tp *bd)
{
	if (bd->next != NULL)
		buddy_free_r(bd->next);

	buddy_deact((buddy_t*) bd);
	libusb_unref_device(bd->dev);
	free(bd);
}

void buddy_free(buddy_t *buddy)
{
	buddy_tp *bd = (buddy_tp*) buddy;
	libusb_context *ctx;
	if (bd == NULL)
		return;

	ctx = bd->ctx;
	buddy_free_r(bd);
	libusb_exit(ctx);
}

int buddy_count(buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	struct buddy_tp *aux;
	int count;

	count = 0;

	for (aux = bd; aux; aux = aux->next)
		count++;

	return count;
}

int buddy_act(struct buddy_tp *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	int configValue;
	struct libusb_config_descriptor *config;

	if(bd->udev != NULL)
		return BUDDY_CORRECT;

	if (libusb_open(bd->dev, &bd->udev) != 0)
		return BUDDY_ERROR_USB;

	libusb_detach_kernel_driver(bd->udev, 0);
	libusb_detach_kernel_driver(bd->udev, 1);
	if (! libusb_get_configuration(bd->udev, &configValue))
		return BUDDY_ERROR_USB;
	if (! libusb_set_configuration(bd->udev, configValue))
		return BUDDY_ERROR_USB;

	libusb_get_active_config_descriptor(bd->dev, &config);
	if (! libusb_claim_interface(bd->udev,
			config->interface->altsetting->bInterfaceNumber))
		return BUDDY_ERROR_USB;
	if (! libusb_set_interface_alt_setting(bd->udev,
			config->interface->altsetting->bInterfaceNumber,
			config->interface->altsetting->bAlternateSetting))
		return BUDDY_ERROR_USB;
	
	return BUDDY_CORRECT;
}

int buddy_deact(struct buddy_tp *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	struct libusb_config_descriptor *config;

	if(bd->udev == NULL)
		return BUDDY_CORRECT;

	libusb_get_active_config_descriptor(bd->dev, &config);
	if(! libusb_release_interface(bd->udev,
			config->interface->altsetting->bInterfaceNumber))
		return BUDDY_ERROR_USB;
	libusb_close(bd->udev);
	bd->udev = NULL;

	return BUDDY_CORRECT;
}

int buddy_activate(buddy_t *buddy, int device)
{
	buddy_tp* bd = (buddy_tp*) buddy;

	if (device < 0)
		return BUDDY_ERROR_DEVICE_OUT;
	else if (device == 0)
	{
		buddy_act(bd);
		return BUDDY_CORRECT;
	} else
		return buddy_activate((buddy_t*) bd->next, --device);
}

int buddy_activate_all(buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if(bd == NULL)
		return BUDDY_CORRECT;

	if (! buddy_act(bd))
		return BUDDY_ERROR_USB;

	return buddy_activate_all((buddy_t*) bd->next);
}

int buddy_deactivate(buddy_t *buddy, int device)
{
	buddy_tp* bd = (buddy_tp*) buddy;

	if (device < 0)
		return BUDDY_ERROR_DEVICE_OUT;
	else if (device == 0)
	{
		if (! buddy_deact(bd))
			return BUDDY_ERROR_USB;
		return BUDDY_CORRECT;
	} else
		return buddy_deactivate((buddy_t*) bd->next, device--);
}

int buddy_deactivate_all(buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if (bd == NULL)
		return BUDDY_CORRECT;

	if (! buddy_deact(bd))
		return BUDDY_ERROR_USB;
	return buddy_deactivate_all((buddy_t*) bd->next);
}

int buddy_state(buddy_t *buddy,
		buddy_heart heart, 
		buddy_light light,
		buddy_wing wing,
		buddy_position position)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if (bd == NULL)
		return BUDDY_CORRECT;
	
	if (heart < 0 || heart > 1)
		return BUDDY_ERROR_HEART_OUT;

	if (light < 0 || light > 7)
		return BUDDY_ERROR_LIGHT_OUT;

	if (wing < 0 || wing > 2)
		return BUDDY_ERROR_WING_OUT;

	if (position < 0 || position > 2)
		return BUDDY_ERROR_POSITION_OUT;

	unsigned char msg;
	
	msg = 0xFF;
	msg ^= heart << 7;
	msg ^= light << 4;
	msg ^= wing << 2;
	msg ^= position;

	buddy_msg(bd->udev, msg);

	return buddy_state((buddy_t*) bd->next, heart, light, wing, position);
}

void buddy_reset(buddy_t *buddy)
{
	buddy_tp* bd = (buddy_tp*) buddy;
	if (bd == NULL)
		return;

	buddy_msg(bd->udev, 0xFF);
}

