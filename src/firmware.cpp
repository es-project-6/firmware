#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/led.hal.hpp"
#include "hal/usart.hal.hpp"
#include "hal/adc.hal.hpp"

#include "stdio.h"

void firmwareSetup()
{
  HAL::init();

  HAL::LED *onboardLED = new HAL::LED(ONBOARD_LED_PIN, ONBOARD_LED_GPIO_PORT);
  HAL::USART::init();
  // HAL::AdConverter *adc = new HAL::AdConverter();
  HAL::AdConverter::init();

  while (1)
  {
    onboardLED->toggle();

    int val;
    val = HAL::AdConverter::getValue();

    HAL::USART::serialClearScreen();
    HAL::USART::printf("Analog Value:%d\r\n", val);

    char str[150];
    for (size_t i = 0; i < 150; i++)
    {
      if (((float)val / (float)4000) * 150 > i)
      {
        str[i] = '#';
      }
      else
      {
        str[i] = '\0';
        break;
      }
    }

    HAL::USART::print(str);

    HAL_Delay(80);
  }
}

void firmwareLoop()
{
}
