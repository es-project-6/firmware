#include "util/c_wrapper.util.hpp"

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