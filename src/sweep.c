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

#include <stm8s_conf.h>
#include "ad9850.h"
#include "config.h"
#include "main.h"
#include "screen.h"
#include "sweep.h"

s8 Sweep_Dir;
s32 Sweep_Mode = SWEEP_FIXED;
bool Sweeping = FALSE;
s32 Freq = 10000000;

void TIM3_UPD_OVF_BRK_IRQHandler(void) interrupt 15 {

	sweep_update();
	TIM3_ClearITPendingBit(TIM3_IT_UPDATE);
}

void sweep_update(void) {

	bool trigger = FALSE;

	if (Sweep_Mode == SWEEP_FIXED)
		return;

	switch (Sweep_Mode) {
	case SWEEP_FIXED:
		return;
	case SWEEP_RAMP:
		if (Freq + Config.step >= Config.stop) {
			Freq = Config.start;
			trigger = TRUE;
		} else
			Freq += Config.step;
		break;
	case SWEEP_TRIANGLE:
		if (Freq + (Config.step * Sweep_Dir) >= Config.stop) {
			Sweep_Dir = -1;
			trigger = TRUE;
		} else if (Freq + (Config.step * Sweep_Dir) <= Config.start) {
			Sweep_Dir = 1;
			trigger = TRUE;
		}
		Freq += Config.step * Sweep_Dir;
		break;
	}

	if (trigger)
		TIM2_Cmd(ENABLE);

	ad9850_freq(Freq);
}

void sweep_stop(void) {

	GPIO_Init(BUTTONS_PORT, ENT, GPIO_MODE_IN_PU_NO_IT);
	TIM3_Cmd(DISABLE);
	Sweeping = FALSE;
	Sweep_Mode = SWEEP_FIXED;
}

void sweep_start(void) {

	Freq = Config.start;
	Sweep_Dir = 1;
	Sweeping = TRUE;
	GPIO_Init(BUTTONS_PORT, ENT, GPIO_MODE_IN_PU_IT);
	TIM3_Cmd(ENABLE);
}

void sweep_init(void) {

	disableInterrupts();

	// Sweep timer
	// 16MHz/128 = 125kHz
	// Period = ( 10ms * 125kHz ) - 1  = 1249
	TIM3_DeInit();
	ITC_SetSoftwarePriority(ITC_IRQ_TIM3_OVF, ITC_PRIORITYLEVEL_1);
	TIM3_TimeBaseInit(TIM3_PRESCALER_128, 1249);
	TIM3_ClearFlag(TIM3_FLAG_UPDATE);
	TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE);

	// Trigger pulse
	TIM2_DeInit();
	TIM2_TimeBaseInit(TIM2_PRESCALER_1, 18355);
	TIM2_OC1Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE, 1,
			TIM2_OCPOLARITY_HIGH);
	TIM2_SelectOnePulseMode(TIM2_OPMODE_SINGLE);
	TIM2_OC1PreloadConfig(ENABLE);
	TIM2_ARRPreloadConfig(ENABLE);
	TIM2_Cmd(ENABLE);

	enableInterrupts();
}

