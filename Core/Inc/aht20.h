#ifndef __AHT20_H
#define __AHT20_H

#include "stm32f1xx_hal.h"

#define AHT20_ADDR          (0x38 << 1)

void     AHT20_Init(I2C_HandleTypeDef *hi2c);
uint8_t  AHT20_Read(I2C_HandleTypeDef *hi2c, float *temp, float *humi);

#endif
