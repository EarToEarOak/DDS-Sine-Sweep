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
#include "delay.h"

u16 Delay_Count;

void TIM4_UPD_OVF_IRQHandler(void) interrupt 23 {

	delay_dec();
	TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
}

void delay_dec() {

	Delay_Count--;
}

void delay_10us(u16 time) {

	Delay_Count = time;
	while (Delay_Count)
		;
}

void delay_1ms(u16 time) {

	u16 i;

	for (i = 0; i < time; i++)
		delay_10us(100);
}

void delay_init(void) {

	disableInterrupts();

	// 16MHz/32 = 500kHz
	// Period = ( 0.01ms * 125kHz ) - 1  = 4
	TIM4_DeInit();
	ITC_SetSoftwarePriority(ITC_IRQ_TIM4_OVF, ITC_PRIORITYLEVEL_3);
	TIM4_TimeBaseInit(TIM4_PRESCALER_32, 4);
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
	TIM4_Cmd(ENABLE);
	enableInterrupts();
}
