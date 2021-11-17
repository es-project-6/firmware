#pragma once

#include "stm32l0xx_hal.h"

void SystemConf_Init(void);

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void Error_Handler(void);
