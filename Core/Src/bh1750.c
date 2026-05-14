#include "bh1750.h"

void BH1750_Init(I2C_HandleTypeDef *hi2c)
{
  uint8_t cmd;
  cmd = BH1750_POWER_ON;
  HAL_I2C_Master_Transmit(hi2c, BH1750_ADDR, &cmd, 1, 100);
  cmd = BH1750_RESET;
  HAL_I2C_Master_Transmit(hi2c, BH1750_ADDR, &cmd, 1, 100);
  cmd = BH1750_CONT_H_RES;
  HAL_I2C_Master_Transmit(hi2c, BH1750_ADDR, &cmd, 1, 100);
}

uint8_t BH1750_ReadLight(I2C_HandleTypeDef *hi2c, float *lux)
{
  uint8_t buf[2];
  if (HAL_I2C_Master_Receive(hi2c, BH1750_ADDR, buf, 2, 200) != HAL_OK)
    return 1;
  *lux = ((float)((buf[0] << 8) | buf[1])) / 1.2f;
  return 0;
}
