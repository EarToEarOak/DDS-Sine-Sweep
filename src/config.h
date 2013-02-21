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

#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm8s_conf.h"

#define CONFIG_BASE		0x004000
#define CONFIG_SAVED	0xAA

typedef struct Config_Struct {
	u8 saved;
	s32 freq;
	s32 start;
	s32 stop;
	s32 step;
	s32 period;
} t_Config;

extern t_Config Config;

void config_load(void);
void config_save(void);
void config_restore(void);
void config_init(void);

#endif
