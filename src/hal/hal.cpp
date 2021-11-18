#include "hal/hal.hpp"
#include "stm32l0xx_hal.h"

namespace HAL
{
  void init()
  {
    HAL_Init();
  }

  /**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
  void Error_Handler(void)
  {

    __disable_irq();
    while (1)
    {
    }
  }
}