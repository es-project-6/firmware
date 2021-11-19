#pragma once

#include "hal/gpio_out.hal.hpp"

#include <cstdint>
#include "stm32l0xx_hal.h"

namespace HAL
{
  class Piezo
  {
  private:
    static inline HAL::GPIO_Out *gpioPin;
    static inline unsigned int period;
    static inline unsigned int blinkPeriod;
    static inline bool enabled;
    static inline bool muted = false;
    static inline unsigned long lastPeriod;
    static inline unsigned long lastBlink;

  public:
    static void init(uint32_t pin, GPIO_TypeDef *port, unsigned int = 400);
    static void setFrequency(unsigned int frequency);
    static void setBlink(unsigned int period);
    static void setEnabled(bool enabled);
    static void update();
  };
}