#include "stm32l0xx_hal.h"
#include "util/delay.hpp"

void delay(uint32_t ms)
{
  return HAL_Delay(ms);
}

void delayMicros(uint32_t us)
{
  uint32_t start_us = getMicroseconds();
  while ((getMicroseconds() - start_us) < us)
  {
  }
}

uint32_t getMicroseconds()
{
  const uint32_t us_since_last_interrupt = 1000 - ((SysTick->VAL & SysTick_VAL_CURRENT_Msk) / 16u);
  return (HAL_GetTick() * 1000) + us_since_last_interrupt;
}