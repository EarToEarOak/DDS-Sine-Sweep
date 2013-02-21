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

#ifndef __SWEEP_H
#define __SWEEP_H

// Sweep Modes
#define SWEEP_FIXED		0
#define SWEEP_RAMP		1
#define SWEEP_TRIANGLE	2
#define SWEEP_RESTORE	3

extern s32 Sweep_Mode;
extern bool Sweeping;

void sweep_update(void);
void sweep_stop(void);
void sweep_start(void);
void sweep_init(void);

#endif
