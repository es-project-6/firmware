#pragma once
#include "stm32l0xx_hal.h"

void debounce(uint32_t pin, GPIO_TypeDef *port);
void delay_us(uint32_t delay_us);
void delay_ms(uint16_t delay_ms);