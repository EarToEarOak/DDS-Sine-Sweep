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

#ifndef __LCD_H
#define __LCD_H

// Functions
void lcd_clear(void);
void lcd_home(void);
void lcd_cursor(const bool enable, const bool blink);
void lcd_position(const u8 x, const u8 y);
void lcd_cgram(const u8 pos, const char row[8]);
void lcd_char(const char chr);
void lcd_print(const char *string);
void lcd_printf(const char *fmt, ...);
void lcd_init(const u8 function);

// commands
#define LCD_CLEARDISPLAY 		0x01
#define LCD_RETURNHOME 			0x02
#define LCD_ENTRYMODESET 		0x04
#define LCD_DISPLAYCONTROL 		0x08
#define LCD_CURSORSHIFT 		0x10
#define LCD_FUNCTIONSET 		0x20
#define LCD_SETCGRAMADDR 		0x40
#define LCD_SETDDRAMADDR 		0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT	 		0x00
#define LCD_ENTRYLEFT 			0x02
#define LCD_ENTRYSHIFTINCREMENT	0x01
#define LCD_ENTRYSHIFTDECREMENT	0x00

// flags for display on/off control
#define LCD_DISPLAYON 			0x0C
#define LCD_CURSORON 			0x0A
#define LCD_BLINKON 			0x09

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 		0x08
#define LCD_CURSORMOVE 			0x00
#define LCD_MOVERIGHT 			0x04
#define LCD_MOVELEFT 			0x00

// flags for function set
#define LCD_8BITMODE 			0x10
#define LCD_4BITMODE 			0x00
#define LCD_2LINE 				0x08
#define LCD_1LINE 				0x00
#define LCD_5x10DOTS 			0x04
#define LCD_5x8DOTS 			0x00

#endif
