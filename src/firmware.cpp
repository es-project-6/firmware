#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/led.hal.hpp"
#include "hal/usart.hal.hpp"
#include "hal/adc.hal.hpp"
#include "hal/i2c.hal.hpp"
#include "hal/lcd.hal.hpp"

#include "stdio.h"

void firmwareSetup()
{
  HAL::init();
  HAL::USART::init();
  HAL::AdConverter::init();
  HAL::I2C::init();
  HAL::LcDisplay::init();
  HAL::USART::print("Setup done\r\n");

  HAL::GPIO_Out *onboardLED = new HAL::GPIO_Out(ONBOARD_LED_PIN, ONBOARD_LED_GPIO_PORT);
  while (1)
  {
    onboardLED->toggle();

    HAL::LcDisplay::clearDisplay();
    HAL::LcDisplay::printf("Wert: %d", HAL::AdConverter::getValue());

    HAL_Delay(500);
  }
}

void firmwareLoop()
{
}
