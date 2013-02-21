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

#include <stdio.h>
#include <string.h>
#include "stm8s_conf.h"
#include "ad9850.h"
#include "delay.h"
#include "config.h"
#include "lcd.h"
#include "main.h"
#include "screen.h"
#include "sweep.h"

// Initialise STM8S
static void init(void) {

	// XTAL Clock
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, ENABLE, DISABLE);
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_ITConfig(CLK_IT_CSSD | CLK_IT_SWIF, DISABLE);

	// Led
	GPIO_DeInit(GPIOD );
	GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_WriteLow(GPIOD, GPIO_PIN_0);

	// Buttons
	GPIO_DeInit(BUTTONS_PORT );
	GPIO_Init(BUTTONS_PORT, INC | DEC | ENT, GPIO_MODE_IN_PU_NO_IT);

	// External interrupt
	disableInterrupts();
	EXTI_DeInit();
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY);
	enableInterrupts();
}

// UDG
static void init_cgram(void) {
	char arrow[8] = { 0x10, 0x18, 0x1c, 0x1e, 0x1c, 0x18, 0x10, 0x00 };
	char sine[8] = { 0x08, 0x14, 0x14, 0x14, 0x05, 0x05, 0x02, 0x00 };
	lcd_cgram(LCD_ARROW, arrow);
	lcd_cgram(LCD_SINE, sine);
}

// Splash screen
static void splash(void) {

	lcd_clear();
	lcd_print("Sine Generator");
	lcd_position(7, 1);
	lcd_char(LCD_SINE);
	lcd_printf(" 0-%iMHz", (int) (F_MAX / 1e6));
	delay_1ms(1500);
	lcd_clear();
}

void main(void) {

	init();
	delay_init();
	delay_1ms(100);
	config_init();
	sweep_init();

	lcd_init(LCD_2LINE | LCD_5x8DOTS);
	init_cgram();
	splash();
	ad9850_init();
	screen();

	// Needed for vsprintf
	printf("%u", 0);

}

#ifdef USE_FULL_ASSERT

void assert_failed(u8* file, u32 line) {
	while (1) {
	}
}
#endif

