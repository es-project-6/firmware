#pragma once

#include <cstdint>
#include "stm32l0xx_hal.h"

namespace HAL
{
  class LED
  {
  private:
    uint32_t pin;
    GPIO_TypeDef *port;

    void init();

  public:
    LED(uint32_t, GPIO_TypeDef *);
    ~LED();
    void toggle();
  };
}