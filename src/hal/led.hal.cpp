#include "hal/led.hal.hpp"
#include "stm32l0xx_hal.h"

#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

namespace HAL
{
  LED::LED(uint32_t pin, GPIO_TypeDef *port)
  {
    this->pin = pin;
    this->port = port;
    this->init();
  }

  void LED::init()
  {
    LED_GPIO_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = this->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(this->port, &GPIO_InitStruct);
  }

  void LED::toggle()
  {
    HAL_GPIO_TogglePin(this->port, this->pin);
  }

}