#include "hal/nvic.h"

void EXTI2_3_IRQHandler(void)
{
  debounce(MODE_BUTTON_PIN, MODE_BUTTON_PORT);
  HAL_GPIO_EXTI_IRQHandler(MODE_BUTTON_PIN);
  buttonPressed(MODE_BUTTON_PIN);
}

void EXTI4_15_IRQHandler(void)
{
  debounce(ARM_BUTTON_PIN, ARM_BUTTON_PORT);
  HAL_GPIO_EXTI_IRQHandler(ARM_BUTTON_PIN);
  buttonPressed(ARM_BUTTON_PIN);
}