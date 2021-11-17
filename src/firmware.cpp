#include "firmware.hpp"

void LED_Init();

void firmwareSetup()
{
  HAL_Init();
  LED_Init();
}

void firmwareLoop()
{
  HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
  HAL_Delay(200);
}

void LED_Init()
{
  LED_GPIO_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}
