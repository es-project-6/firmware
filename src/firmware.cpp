#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/led.hal.hpp"
#include "hal/usart.hal.hpp"
#include "hal/adc.hal.hpp"
#include "hal/i2c.hal.hpp"

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

    HAL_Delay(80);
  }
}

void firmwareLoop()
{
}
