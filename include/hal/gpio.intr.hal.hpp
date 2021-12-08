#pragma once

#include <cstdint>
#include "stm32l0xx_hal.h"
#include "hal/nvic.h"

namespace HAL
{
  class GPIO_INTERRUPT
  {
  protected:
    uint32_t pin;
    GPIO_TypeDef *port;
    void init();

  public:
    GPIO_INTERRUPT(uint32_t);
    ~GPIO_INTERRUPT();
  };
}