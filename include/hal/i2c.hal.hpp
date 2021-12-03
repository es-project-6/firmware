#pragma once

#include "stm32l0xx_hal.h"

#include <cstdint>

namespace HAL
{
  class I2C
  {
  private:
    static I2C_HandleTypeDef hi2c1;

  public:
    static void init();
    static void send(uint16_t, uint8_t *, uint16_t, uint32_t = 1000);
  };
}