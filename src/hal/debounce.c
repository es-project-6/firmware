#include "hal/debounce.h"

void debounce(uint32_t pin, GPIO_TypeDef *port)
{
    delay_ms(2);
    if (port -> IDR & pin)
    {
        delay_us(100);
    }
}

// Custom delay because ISR has higer priority than HAL

void delay_us(uint32_t delay_us)
{
  volatile uint32_t num;
  volatile uint32_t t;


  for (num = 0; num < delay_us; num++)
  {
    t = HAL_RCC_GetHCLKFreq() / 1000000;
    while (t != 0)
    {
      t--;
    }
  }
}

void delay_ms(uint16_t delay_ms)
{
  volatile unsigned int num;
  for (num = 0; num < delay_ms; num++)
  {
    delay_us(1000);
  }
}