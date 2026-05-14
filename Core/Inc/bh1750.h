#ifndef __BH1750_H
#define __BH1750_H

#include "stm32f1xx_hal.h"

#define BH1750_ADDR         (0x23 << 1)
#define BH1750_POWER_ON     0x01
#define BH1750_RESET        0x07
#define BH1750_CONT_H_RES   0x10

void     BH1750_Init(I2C_HandleTypeDef *hi2c);
uint8_t  BH1750_ReadLight(I2C_HandleTypeDef *hi2c, float *lux);

#endif
