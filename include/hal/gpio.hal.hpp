#pragma once

#include <cstdint>
#include "stm32l0xx_hal.h"

namespace HAL
{
  class GPIO
  {
  protected:
    uint32_t pin;
    GPIO_TypeDef *port;
    void init();

  public:
    GPIO(uint32_t, GPIO_TypeDef *);
    ~GPIO();
  };
}