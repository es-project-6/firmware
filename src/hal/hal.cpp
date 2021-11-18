#include "hal/hal.hpp"
#include "stm32l0xx_hal.h"
#include "hal/usart.hal.hpp"
#include "hal/clock.hal.hpp"
#include <string.h>

namespace HAL
{
  void init()
  {
    HAL_Init();
    Clock::init();
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }

  void Error_Handler()
  {
    USART::print("Error_Handler called!\r\n");
    __disable_irq();
    while (1)
    {
    }
  }

  void Error_Handler(const char err[])
  {
    USART::print("ERR: ");
    USART::print(err);
    USART::print("\r\n");

    __disable_irq();
    while (1)
    {
    }
  }
}

/* MSP FUnctions */

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}