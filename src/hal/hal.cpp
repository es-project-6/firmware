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
    MX_GPIO_Init();
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

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
}
