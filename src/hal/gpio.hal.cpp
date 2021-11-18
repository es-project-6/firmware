#include "hal/gpio.hal.hpp"
#include "stm32l0xx_hal.h"

namespace HAL
{
  GPIO::GPIO(uint32_t pin, GPIO_TypeDef *port)
  {
    this->pin = pin;
    this->port = port;
    this->init();
  }

  void GPIO::init()
  {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = this->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(this->port, &GPIO_InitStruct);
  }
}