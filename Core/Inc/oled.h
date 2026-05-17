#ifndef __OLED_H
#define __OLED_H

#include "stm32f1xx_hal.h"

/* Driver targets a 1.3" ST7789 240x240 IPS panel over SPI.
 * The legacy "OLED_*" names are preserved so the rest of the
 * application (main.c) does not need to change. */

#define OLED_WIDTH   240
#define OLED_HEIGHT  240

/* RGB565 colors */
#define COLOR_BLACK     0x0000
#define COLOR_WHITE     0xFFFF
#define COLOR_RED       0xF800
#define COLOR_GREEN     0x07E0
#define COLOR_BLUE      0x001F
#define COLOR_YELLOW    0xFFE0
#define COLOR_CYAN      0x07FF
#define COLOR_MAGENTA   0xF81F
#define COLOR_GREY      0x8410

/* High-level (legacy compatible) API.
 * The 6x8 font is rendered at 2x scale -> each glyph is 12x16. */
void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_WriteString(uint8_t x, uint8_t y, const char *str);
void OLED_Display(void);

/* Optional helpers for advanced use */
void OLED_FillScreen(uint16_t color);
void OLED_SetColors(uint16_t fg, uint16_t bg);
void OLED_BacklightOn(void);
void OLED_BacklightOff(void);

#endif
