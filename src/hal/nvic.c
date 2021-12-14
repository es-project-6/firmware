#include "hal/nvic.h"

void EXTI2_3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(MODE_BUTTON_PIN);
  buttonPressed(MODE_BUTTON_PIN);
}

void EXTI4_15_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(ARM_BUTTON_PIN);
  buttonPressed(ARM_BUTTON_PIN);
}