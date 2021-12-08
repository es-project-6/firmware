#include "hal/nvic.h"

void EXTI2_3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(MODE_BUTTON_PIN);
  // Do ISR stuff and things
}