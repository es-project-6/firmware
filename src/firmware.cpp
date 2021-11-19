#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/gpio_out.hal.hpp"
#include "hal/usart.hal.hpp"
#include "hal/adc.hal.hpp"
#include "hal/i2c.hal.hpp"
#include "hal/lcd.hal.hpp"
#include "hal/piezo.hal.hpp"

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
  HAL::Piezo::init(PIEZO_PIN, PIEZO_GPIO_PORT);
  HAL::Piezo::setFrequency(1000);
  HAL::Piezo::setBlink(200);

  uint8_t sensorValue;

  while (1)
  {
    onboardLED->toggle();
    sensorValue = HAL::AdConverter::getValue();
    HAL::LcDisplay::clearDisplay();

    HAL::Piezo::setEnabled(sensorValue > 3500);

    HAL_Delay(100);
  }
}

void firmwareLoop()
{
}
