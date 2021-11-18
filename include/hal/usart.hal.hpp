#pragma once

#include <cstdint>
#include "stm32l0xx_hal.h"

namespace HAL
{
  class USART
  {
  private:
    inline static UART_HandleTypeDef huart;

  public:
    static void init(uint32_t = 115200);
    static HAL_StatusTypeDef print(char[], size_t);
    static HAL_StatusTypeDef print(char *);
    static void serialClearScreen();
  };
}