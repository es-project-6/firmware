#pragma once

#define HAL_ADC_MODULE_ENABLED
#include "stm32l0xx_hal.h"

#include <cstdint>

namespace HAL
{
  class AdConverter
  {
  private:
    ADC_HandleTypeDef hadc;
    void init();

  public:
    AdConverter();
    ~AdConverter();
    uint32_t getValue();
  };
}