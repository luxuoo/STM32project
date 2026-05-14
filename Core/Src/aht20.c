#include "aht20.h"

static uint8_t AHT20_CRC8(uint8_t *data, uint8_t len)
{
  uint8_t crc = 0xFF;
  for (uint8_t i = 0; i < len; i++)
  {
    crc ^= data[i];
    for (uint8_t j = 0; j < 8; j++)
    {
      if (crc & 0x80)
        crc = (crc << 1) ^ 0x31;
      else
        crc <<= 1;
    }
  }
  return crc;
}

void AHT20_Init(I2C_HandleTypeDef *hi2c)
{
  HAL_Delay(40);
  uint8_t status;
  HAL_I2C_Master_Receive(hi2c, AHT20_ADDR, &status, 1, 100);
  if ((status & 0x08) == 0)
  {
    uint8_t init_cmd[3] = {0xBE, 0x08, 0x00};
    HAL_I2C_Master_Transmit(hi2c, AHT20_ADDR, init_cmd, 3, 100);
    HAL_Delay(10);
  }
}

uint8_t AHT20_Read(I2C_HandleTypeDef *hi2c, float *temp, float *humi)
{
  uint8_t cmd[3] = {0xAC, 0x33, 0x00};
  uint8_t data[7];

  if (HAL_I2C_Master_Transmit(hi2c, AHT20_ADDR, cmd, 3, 200) != HAL_OK)
    return 1;

  HAL_Delay(80);

  if (HAL_I2C_Master_Receive(hi2c, AHT20_ADDR, data, 7, 200) != HAL_OK)
    return 1;

  if (data[0] & 0x80)
    return 1;

  if (AHT20_CRC8(data, 7) != 0)
    return 1;

  uint32_t raw_humi = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((uint32_t)data[3] >> 4);
  uint32_t raw_temp = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | (uint32_t)data[5];

  *humi = ((float)raw_humi / 1048576.0f) * 100.0f;
  *temp = ((float)raw_temp / 1048576.0f) * 200.0f - 50.0f;

  return 0;
}
