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
#include "delay.h"
#include "main.h"

static void pulse(const u8 pin) {
	GPIO_WriteHigh(AD9850_PORT, pin);
	delay_10us(1);
	GPIO_WriteLow(AD9850_PORT, pin);
	delay_10us(1);
}

static void send_byte(u8 byte) {

	u8 i;

	for (i = 0; i < 8; i++) {
		if (byte & 1)
			GPIO_WriteHigh(AD9850_PORT, DATA);
		else
			GPIO_WriteLow(AD9850_PORT, DATA);
		pulse(W_CLK);
		byte >>= 1;
	}
}

void ad9850_freq(const u32 frequency) {

	float freq;
	u32 word;
	u8 i;

	freq = (float)4294967295 / AD9850_CLOCK;
	freq *= frequency;
	word = (u32)freq;

	for (i = 0; i < 4; i++) {
		send_byte((u8) (word & 0xff));
		word >>= 8;
	}
	send_byte(0);

	pulse(FQ_UD);
}

void ad9850_init(void) {

	GPIO_DeInit(AD9850_PORT );
	GPIO_Init(AD9850_PORT, W_CLK | FQ_UD | DATA | RESET,
			GPIO_MODE_OUT_PP_LOW_FAST);

	pulse(RESET);
	pulse(W_CLK);
	pulse(FQ_UD);
}
