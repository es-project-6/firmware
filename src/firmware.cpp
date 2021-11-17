#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/led.hal.hpp"

#include "stm32l0xx_hal.h"

HAL::LED *onboardLED;

void firmwareSetup()
{
  HAL_Init();
  HAL::init();
  onboardLED = new HAL::LED(ONBOARD_LED_PIN, ONBOARD_LED_GPIO_PORT);
}

void firmwareLoop()
{
  onboardLED->toggle();
  HAL_Delay(200);
}
