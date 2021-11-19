#include "hal/usart.hal.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

namespace HAL
{
  USART_HandleTypeDef USART::husart;

  void USART::init(uint32_t baudRate)
  {
    husart.Instance = USART2;
    husart.Init.BaudRate = 115200;
    husart.Init.WordLength = USART_WORDLENGTH_8B;
    husart.Init.StopBits = USART_STOPBITS_1;
    husart.Init.Parity = USART_PARITY_NONE;
    husart.Init.Mode = USART_MODE_TX_RX;
    husart.Init.CLKPolarity = USART_POLARITY_LOW;
    husart.Init.CLKPhase = USART_PHASE_1EDGE;
    husart.Init.CLKLastBit = USART_LASTBIT_DISABLE;
    if (HAL_USART_Init(&husart) != HAL_OK)
    {
      HAL::Error_Handler("HAL_USART_Init failed");
    }
  }

  HAL_StatusTypeDef USART::print(const char data[], size_t size)
  {
    return HAL_USART_Transmit(&USART::husart, (uint8_t *)data, size, 1000);
  }

  HAL_StatusTypeDef USART::print(const char *str)
  {
    return print((char *)str, strlen(str));
  }

  HAL_StatusTypeDef USART::printf(const char *format, ...)
  {
    char buff[100];
    va_list va;
    va_start(va, format);
    vsprintf(buff, format, va);
    va_end(va);

    return print((char *)buff, strlen(buff));
  }

  void USART::serialClearScreen()
  {
    print("\033c");
  }

}
