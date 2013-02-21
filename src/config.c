/*
 * DDS Sine Sweeper
 *
 * Copyright 2013 Al Brown
 *
 * http://eartoearoak.com/hardware/dds-sine-sweeper
 *
 * This file is part of DDS Sine Sweeper.
 *
 * DDS Sine Sweeper is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DDS Sine Sweeper is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DDS Sine Sweeper.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "sweep.h"
#include "stm8s_conf.h"
#include <string.h>

t_Config Config;

void config_load(void) {

	t_Config config;
	u8 *ptr = (u8 *) &config;
	u8 i;

	for (i = 0; i < sizeof(t_Config); i++) {
		*(ptr + i) = FLASH_ReadByte(CONFIG_BASE + i);
	}

	if (config.saved == CONFIG_SAVED) {
		memcpy(&Config, &config, sizeof(Config));
	}
}

void config_save(void) {

	u8 *ptr = (u8 *) &Config;
	u8 i;

	Config.saved = CONFIG_SAVED;

	for (i = 0; i < sizeof(t_Config); i++) {
		FLASH_ProgramByte(CONFIG_BASE + i, *(ptr + i));
	}
}

void config_restore(void) {

	Config.freq = 10000000;
	Config.start = 20;
	Config.stop = 20000;
	Config.step = 10;
	Config.period = 1000;
}

void config_init(void) {

	FLASH_Unlock(FLASH_MEMTYPE_DATA);
	config_restore();
}
