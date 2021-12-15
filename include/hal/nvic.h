#ifndef _VVC_INTERRUPTS_H
#define _VVC_INTERRUPTS_H
#include "stm32l0xx_hal.h"
#include "hal/pins.hal.hpp"
#include "hal/debounce.h"

void EXTI2_3_IRQHandler(void);
void EXTI4_15_IRQHandler(void);

#endif