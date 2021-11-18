#pragma once

namespace HAL
{
  void init();
  void Error_Handler();
  void Error_Handler(const char[]);
};

void MX_GPIO_Init(void);