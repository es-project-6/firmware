#pragma once

#include <cstdint>
#include "stm32l0xx_hal.h"

namespace HAL
{
  class USART
  {
  private:
    static USART_HandleTypeDef husart;

  public:
    static void init(uint32_t = 115200);
    static HAL_StatusTypeDef print(const char[], size_t);
    static HAL_StatusTypeDef print(const char *);
    static HAL_StatusTypeDef printf(const char *format, ...);
    static void serialClearScreen();
  };
}