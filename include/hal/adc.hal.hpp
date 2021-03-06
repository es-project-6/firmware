#pragma once

#include "stm32l0xx_hal.h"

#include <cstdint>

namespace HAL
{
  class AdConverter
  {
  private:
    static ADC_HandleTypeDef hadc;

  public:
    static void init();
    static uint32_t getValue();
  };
}