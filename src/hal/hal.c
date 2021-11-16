#include "hal/hal.h"

void SysTick_Handler(void)
{
  HAL_IncTick();
}
