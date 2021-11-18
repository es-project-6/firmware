#include "hal/hal.hpp"
#include "hal/i2c.hal.hpp"
#include "stm32l0xx_hal.h"

namespace HAL
{
  I2C_HandleTypeDef I2C::hi2c1;

  void I2C::init()
  {
    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x00000708;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
      HAL::Error_Handler("HAL_I2C_Init failed");
    }
    /** Configure Analogue filter
  */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
      HAL::Error_Handler("HAL_I2CEx_ConfigAnalogFilter failed");
    }
    /** Configure Digital filter
  */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
    {
      HAL::Error_Handler("HAL_I2CEx_ConfigAnalogFilter failed");
    }
  }

  HAL_StatusTypeDef I2C::send(uint16_t address, uint8_t *data, uint16_t size, uint32_t timeout)
  {
    return HAL_I2C_Master_Transmit(&hi2c1, address << 1, data, size, timeout);
  }
}
