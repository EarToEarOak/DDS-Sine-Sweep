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

#ifndef __SCREEN_H
#define __SCREEN_H

// Screens
#define SCREEN_MAIN		0
#define SCREEN_START	1
#define SCREEN_STOP		2
#define SCREEN_PERIOD	3

// Screen Control Locations
#define LOC_MAIN_X		{0, 0, 1, 2, 3, 4, 5, 6, 7};
#define LOC_MAIN_Y		{0, 1, 1, 1, 1, 1, 1, 1, 1};

#define LOC_FREQ_X		{0, 1, 2, 3, 4, 5, 6, 7, 13};
#define LOC_FREQ_Y		{1, 1, 1, 1, 1, 1, 1, 1, 1};

#define LOC_PERIOD_X	{0, 1, 2, 3, 4, 13};
#define LOC_PERIOD_Y	{1, 1, 1, 1, 1, 1};

// Buttons
#define BT_INC			0
#define BT_DEC			1
#define BT_ENT			2

void screen_print_number(const s32 value, const u8 width);
void screen(void);

#endif
