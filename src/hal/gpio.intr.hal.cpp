#include "hal/gpio.intr.hal.hpp"
#include "stm32l0xx_hal.h"

namespace HAL
{
  GPIO_INTERRUPT::GPIO_INTERRUPT(uint32_t pin)
  {
    this->pin = pin;
    // Interruptline nur für Port B nutzbar
    this->port = GPIOB;
    this->init();
  }

  void GPIO_INTERRUPT::init()
  {
    // Pin init
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = this->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(this->port, &GPIO_InitStruct);

    
    HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);
  }
}