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

#ifndef __STM8S_CONF_H
#define __STM8S_CONF_H

#include "stm8s.h"

//#define USE_FULL_ASSERT 1

#define HSE_VALUE ((u32)16000000)

#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((u8 *)__FILE__, __LINE__))
void assert_failed(u8* file, u32 line);
#else
#define assert_param(expr) ((void)0)
#endif

#include <stm8s_clk.h>
#include <stm8s_exti.h>
#include <stm8s_flash.h>
#include <stm8s_gpio.h>
#include <stm8s_itc.h>
#include <stm8s_tim2.h>
#include <stm8s_tim3.h>
#include <stm8s_tim4.h>

#endif

