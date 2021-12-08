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
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(this->port, &GPIO_InitStruct);

    SYSCFG->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI1_Msk);
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB;
    
    // Enable triggers for edge detection
    EXTI->IMR |= (1 << pin);
    // mask out falling edge
    EXTI->RTSR &= ~(1 << pin);
    // Trigger on rising edge
    EXTI->FTSR |= (1 << pin);

    // buuton interrup is low priorty
    NVIC_SetPriority(EXTI0_1_IRQn, 0x03);
    NVIC_EnableIRQ(EXTI0_1_IRQn);
  }
}