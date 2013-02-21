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

/*
 *	STM8S-Discovery Connections
 *
 *		JP1			2-3		5v Selection
 *
 *		CN1-5		Vss		Gnd
 *		CN1-6		Vdd		5v
 *
 *		CN3-9		PB7		LCD RS
 *		CN3-8		PB6		LCD RW
 *		CN3-7		PB5 	LCD E
 *		CN3-6		PB4 	LCD D4
 *		CN3-5		PB3	 	LCD D5
 *		CN3-4		PB2	 	LCD D6
 *		CN3-3		PB1 	LCD D7
 *
 *		CN1-9		PA3		AD9850 W_CLK
 *		CN1-10		PA4		AD9850 FQ_UD
 *		CN1-11		PA5		AD9850 DATA
 *		CN1-12		PA6		AD9850 RESET
 *
 *		CN4-9		PD4		Trigger Out
 *
 *		CN2-5		PC4		INC Button
 *		CN2-6		PC5		DEC Button
 *		CN2-9		PC6		ENT Button
 *
 */

#ifndef __MAIN_H
#define __MAIN_H

// Frequency range
#define F_MIN			1
#define F_MAX			60000000

// LCD
#define LCD_PORT 		GPIOB
#define LCD_RS 			GPIO_PIN_1
#define LCD_RW 			GPIO_PIN_2
#define LCD_E 			GPIO_PIN_3
#define LCD_DATA		GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
// LCD UDG
#define LCD_ARROW 		0
#define LCD_SINE		1

// AD9850
#define AD9850_PORT 	GPIOA
#define W_CLK			GPIO_PIN_3
#define FQ_UD			GPIO_PIN_4
#define DATA			GPIO_PIN_5
#define RESET			GPIO_PIN_6

// Trigger Output
#define SWEEP_TRIG_PORT	GPIOC
#define SWEEP_TRIG		GPIO_PIN_7

#define AD9850_CLOCK	125000000

// Buttons
#define BUTTONS_PORT	GPIOC
#define INC				GPIO_PIN_4
#define DEC				GPIO_PIN_5
#define ENT				GPIO_PIN_6

void main(void);

#endif
