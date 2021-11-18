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
  HAL::AdConverter *adc = new HAL::AdConverter();

  char str[100];

  while (1)
  {
    onboardLED->toggle();

    int val = adc->getValue();

    sprintf(str, "Analog Value:%d\r\n", val);
    HAL::USART::print(str);

    HAL_Delay(200);
  }
}

void firmwareLoop()
{
}
