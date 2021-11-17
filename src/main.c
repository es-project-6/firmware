#include "util/c_wrapper.util.hpp"
#include "stm32l0xx_hal.h"

int main(void)
{
  wrappedFirmwareSetup();

  while (1)
  {
    wrappedFirmwareLoop();
  }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}