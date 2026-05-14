#ifndef __OLED_H
#define __OLED_H

#include "stm32f1xx_hal.h"

#define OLED_WIDTH   128
#define OLED_HEIGHT  64

void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_WriteString(uint8_t x, uint8_t y, const char *str);
void OLED_Display(void);

#endif
