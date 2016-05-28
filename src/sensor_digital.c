/*
 * sensor_digital.c
 *
 * Copyright (C) 2016 Brian Masney <masneyb@onstation.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <wiringPi.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yadl.h"

static void _digital_init(__attribute__((__unused__)) yadl_config *config)
{
	if (wiringPiSetup() == -1)
		exit(1);
}

static yadl_result *_digital_read_data(yadl_config *config)
{
	int reading = digitalRead(config->gpio_pin);
	config->logger("Got digital reading %d from GPIO pin %d.\n",
			reading, config->gpio_pin);

	yadl_result *result;
	result = malloc(sizeof(*result));
	result->value = reading;
	return result;
}

sensor digital_sensor_funcs = {
	.init = &_digital_init,
	.read = _digital_read_data
};
