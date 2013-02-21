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
#include <stdio.h>
#include "delay.h"
#include "lcd.h"
#include "main.h"

// Pulse enable line
static void lcd_pulse(void) {
	GPIO_WriteHigh(LCD_PORT, LCD_E);
	delay_10us(1);
	GPIO_WriteLow(LCD_PORT, LCD_E);
	delay_10us(1);
}

// Sent 4bits
static void lcd_write(const u8 value) {

	GPIO_WriteLow(LCD_PORT, GPIO_PIN_HNIB);
	GPIO_WriteHigh(LCD_PORT, value << 4);

	lcd_pulse();
}

// Send command
static void lcd_command(const u8 value, const bool rs) {

	if (rs) {
		GPIO_WriteHigh(LCD_PORT, LCD_RS);
	} else {
		GPIO_WriteLow(LCD_PORT, LCD_RS);
	}
	lcd_write(value >> 4);
	lcd_write(value & 0x0f);
	delay_10us(1);
}

// Clear
void lcd_clear() {

	lcd_command(LCD_CLEARDISPLAY, FALSE);
	delay_10us(200);
}

// Home
void lcd_home() {

	lcd_command(LCD_RETURNHOME, FALSE);
	delay_10us(200);
}

// Enable cursor
void lcd_cursor(const bool enable, const bool blink) {

	u8 command = LCD_DISPLAYON;

	if (enable)
		command |= LCD_CURSORON;
	if (blink)
		command |= LCD_BLINKON;

	lcd_command(command, FALSE);
	delay_10us(1);
}

// Cursor position
void lcd_position(const u8 x, const u8 y) {

	u8 row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	lcd_command(LCD_SETDDRAMADDR | (x + row_offsets[y]), FALSE);
	delay_10us(100);
}

// User defined characters
void lcd_cgram(const u8 pos, const char row[8]) {

	u8 i;

	if (pos > 7)
		return;

	// Select cgram
	lcd_command(0x40 | (pos << 3), FALSE);
	// Add
	for (i = 0; i < 8; i++)
		lcd_command(row[i], TRUE);

}

// Print character
void lcd_char(const char chr) {
	lcd_command(chr, TRUE);
}

// Print string
void lcd_print(const char *string) {
	u8 i = 0;

	while (string[i] != 0) {
		lcd_command(string[i], TRUE);
		i++;
	}
}

// Print formatted string
void lcd_printf(const char *fmt, ...) {
	u16 i;
	u16 size;
	u8 character;
	static char buffer[32];
	va_list args;

	va_start(args, fmt);
	size = vsprintf(buffer, fmt, args);

	// Process the string
	for (i = 0; i < size; i++) {
		character = buffer[i];

		if (character == 10)
			break;
		else {
			if ((character > 0x1F) && (character < 0x80))
				lcd_char(character);
		}
	}
}

// Initialise LCD
void lcd_init(const u8 function) {

	// Init GPIO
	GPIO_DeInit(LCD_PORT );
	//  Push-pull outputs
	GPIO_Init(LCD_PORT, LCD_RS | LCD_RW | LCD_E | LCD_DATA,
			GPIO_MODE_OUT_PP_HIGH_FAST);

	// Init LCD bus
	//delay_10us(1000);
	GPIO_WriteLow(LCD_PORT, LCD_RS);
	GPIO_WriteLow(LCD_PORT, LCD_RW);
	GPIO_WriteLow(LCD_PORT, LCD_E);
	delay_10us(500);

	// Reset sequence
	lcd_write(0x03);
	delay_10us(500);
	lcd_write(0x03);
	delay_10us(1);
	lcd_write(0x03);
	delay_10us(1);
	// 4 bit mode
	lcd_write(0x02);

	lcd_command(LCD_FUNCTIONSET | LCD_4BITMODE | function, FALSE);
	lcd_command(LCD_DISPLAYCONTROL | LCD_DISPLAYON, FALSE);
	lcd_command(LCD_ENTRYMODESET | LCD_ENTRYLEFT, FALSE);
	lcd_clear();
}
