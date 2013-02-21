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

#include <string.h>
#include "stm8s_conf.h"
#include "ad9850.h"
#include "config.h"
#include "delay.h"
#include "lcd.h"
#include "main.h"
#include "screen.h"
#include "sweep.h"

code u8 Main_X[] = LOC_MAIN_X
code u8 Main_Y[] = LOC_MAIN_Y
code u8 Freq_X[] = LOC_FREQ_X
code u8 Freq_Y[] = LOC_FREQ_Y
code u8 Period_X[] = LOC_PERIOD_X
code u8 Period_Y[] = LOC_PERIOD_Y

u8 Pos_X[10];
u8 Pos_Y[10];
u8 Last_Button = 0xff;
bool Stop = FALSE;

void EXTI_PORTC_IRQHandler(void)
interrupt 5 {

	sweep_stop();
	Stop = TRUE;
}

static u8 num_digits(const s32 value) {
	if (value < 10)
		return 1;
	return (u8) (1 + num_digits(value / 10));
}

static s32 pow10(const u8 power) {

	u8 i;
	u32 result = 1;

	for (i = 0; i < power; i++)
		result *= 10;

	return result;
}

static u8 read_button(void) {

	u8 input;
	u8 button;

	input = GPIO_ReadInputData(BUTTONS_PORT );
	if ((input & INC) == 0)
		button = BT_INC;
	else if ((input & DEC) == 0)
		button = BT_DEC;
	else if ((input & ENT) == 0)
		button = BT_ENT;
	else
		button = 0xff;

	return button;

}

static u8 get_button(void) {

	u8 press1;
	u8 press2;
	u8 button = 0xff;

	while (button == 0xff && !Stop) {
		press1 = read_button();
		if (press1 != 0xff) {
			delay_1ms(100);
			press2 = read_button();
			if (press1 == press2) {
				if (press1 != BT_ENT || Last_Button != BT_ENT)
					button = press2;
			}
		}
		Last_Button = press1;
	}

	if (Stop) {
		button = 0xff;
		Stop = FALSE;
	}

	return button;
}

static void locate(const u8 index) {

	lcd_position(Pos_X[index], Pos_Y[index]);

}

void screen_print_number(const s32 value, const u8 width) {

	lcd_position(0, 1);
	if (width == 8)
		lcd_printf("%08ldHz", value);
	else
		lcd_printf("%05ldms", value);
	lcd_home();
}

static void print_ok(void) {

	lcd_position(13, 1);
	lcd_char(LCD_ARROW);
	lcd_print("OK");

}

static void screen_period(void) {

	lcd_char(LCD_ARROW);
	lcd_print("Period");
	screen_print_number(Config.period, 5);
	print_ok();
}

static void screen_freq(const char *prompt, const s32 freq) {

	lcd_print(prompt);
	screen_print_number(freq, 8);

	print_ok();
}

static void screen_main(void) {

	lcd_char(LCD_ARROW);
	switch (Sweep_Mode) {
	case SWEEP_FIXED:
		lcd_print("Fixed         ");
		break;
	case SWEEP_RAMP:
		lcd_print("Ramp sweep    ");
		break;
	case SWEEP_TRIANGLE:
		lcd_print("Triangle sweep");
		break;
	case SWEEP_RESTORE:
		lcd_print("Load defaults ");
		break;
	}
	if (Sweeping) {
		lcd_position(0, 1);
		lcd_print("Running...");
		lcd_position(0, 0);
	} else
		screen_print_number(Config.freq, 8);
}

static void screen_update(const u8 screen) {

	lcd_clear();
	switch (screen) {
	case SCREEN_MAIN:
		screen_main();
		break;
	case SCREEN_START:
		screen_freq("Start", Config.start);
		break;
	case SCREEN_STOP:
		screen_freq("Stop", Config.stop);
		break;
	case SCREEN_PERIOD:
		screen_period();
		break;
	}
}

static u8 screen_switch(const u8 screen, u8 *limit, s8 *index) {

	void *source_x;
	void *source_y;

	lcd_clear();
	switch (screen) {
	case SCREEN_MAIN:
		source_x = &Main_X;
		source_y = &Main_Y;
		*limit = sizeof(Main_X) / sizeof(Main_X[0]) - 1;
		*index = 1;
		break;
	case SCREEN_START:
	case SCREEN_STOP:
		source_x = &Freq_X;
		source_y = &Freq_Y;
		*limit = sizeof(Freq_X) / sizeof(Freq_X[0]) - 1;
		*index = 8;
		break;
	case SCREEN_PERIOD:
		source_x = &Period_X;
		source_y = &Period_Y;
		*limit = sizeof(Period_X) / sizeof(Period_X[0]) - 1;
		*index = 6;
		break;
	default:
		return 0xff;
	}

	memcpy(Pos_X, source_x, *limit + 1);
	memcpy(Pos_Y, source_y, *limit + 1);

	screen_update(screen);

	return screen;
}

static void edit(const u8 dialog,
		s32 *value,
		const s32 min,
		const s32 max,
		const u8 index,
		const u8 location,
		const u8 width) {

	s32 step;
	u8 button = 0xff;
	bool updated;

	step = pow10(width - index + location - 1);

	lcd_cursor(FALSE, TRUE);

	while (button != BT_ENT) {
		locate(index);
		updated = FALSE;
		button = get_button();
		switch (button) {
		case BT_DEC:
			if (*value + step <= max) {
				(*value) += step;
				updated = TRUE;
			}
			break;
		case BT_INC:
			if (*value - step >= min) {
				(*value) -= step;
				updated = TRUE;
			}
			break;
		}

		if (updated) {
			if (dialog == SCREEN_MAIN)
				ad9850_freq(Config.freq);
			screen_update(dialog);
		}
	}
	lcd_cursor(TRUE, FALSE);
}

void screen(void) {

	u8 dialog;
	s8 index;
	u8 limit;
	u8 button;
	s32 min_period;
	s32 max_period;
	u32 freq_old = Config.freq;

	config_load();

	ad9850_freq(Config.freq);

	dialog = screen_switch(SCREEN_MAIN, &limit, &index);

	while (1) {
		locate(index);
		lcd_cursor(TRUE, FALSE);
		button = get_button();
		switch (button) {
		case BT_INC:
			if (dialog == SCREEN_MAIN && Sweep_Mode != SWEEP_FIXED) {
				index = 0;
				break;
			}
			index--;
			break;
		case BT_DEC:
			if (dialog == SCREEN_MAIN && Sweep_Mode != SWEEP_FIXED) {
				index = 0;
				break;
			}
			index++;
			break;
		case BT_ENT:
			switch (dialog) {
			case SCREEN_MAIN:
				if (index > 0) {
					edit(dialog, &Config.freq, F_MIN, F_MAX, index, 1, 8);
					config_save();
				} else if (index == 0)
					edit(dialog, &Sweep_Mode, SWEEP_FIXED, SWEEP_RESTORE, index,
							0, 1);
				if (Sweep_Mode == SWEEP_RESTORE) {
					config_restore();
					Sweep_Mode = SWEEP_FIXED;
					dialog = screen_switch(SCREEN_MAIN, &limit, &index);
				} else if (Sweep_Mode != SWEEP_FIXED) {
					dialog = screen_switch(SCREEN_START, &limit, &index);
				}
				break;
			case SCREEN_START:
				if (index < 8)
					edit(dialog, &Config.start, F_MIN, F_MAX - 1, index, 0, 8);
				else if (index == 8) {
					if (Config.start >= Config.stop)
						Config.stop = Config.start + 1;
					dialog = screen_switch(SCREEN_STOP, &limit, &index);
				}
				break;
			case SCREEN_STOP:
				if (index < 8)
					edit(dialog, &Config.stop, Config.start + 1, F_MAX, index,
							0, 8);
				else if (index == 8) {
					if (Config.step > Config.stop - Config.start)
						Config.step = Config.stop - Config.start;
					min_period = (Config.stop - Config.start) * 10 / 65535;
					max_period = (Config.stop - Config.start) * 10;
					if (Config.period < min_period)
						Config.period = min_period;
					if (Config.period > max_period)
						Config.period = max_period;
					dialog = screen_switch(SCREEN_PERIOD, &limit, &index);
				}
				break;
			case SCREEN_PERIOD:
				Config.step = (Config.stop - Config.start) * 10 / Config.period;
				if (index < 5)
					edit(dialog, &Config.period, min_period, max_period, index,
							0, 5);
				else if (index == 5) {
					Sweeping = TRUE;
					dialog = screen_switch(SCREEN_MAIN, &limit, &index);
					index = 0;
					freq_old = Config.freq;
					Config.step = (Config.stop - Config.start) * 10
							/ Config.period;
					config_save();
					sweep_start();
				}
				break;
			}
			break;
		default:
			Config.freq = freq_old;
			ad9850_freq(Config.freq);
			Sweep_Mode = SWEEP_FIXED;
			dialog = screen_switch(SCREEN_MAIN, &limit, &index);
			break;
		}

		if (index > limit)
			index = limit;
		else if (index < 0)
			index = 0;
	}
}
