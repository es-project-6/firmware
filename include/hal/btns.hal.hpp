#pragma once
#include <stdint.h>

namespace HAL
{
  class Buttons
  {
  public:
    static void handle(uint16_t pin);
  };
}
