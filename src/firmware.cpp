#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/gpio.intr.hal.hpp"
#include "hal/gpio_out.hal.hpp"
#include "hal/usart.hal.hpp"
#include "hal/adc.hal.hpp"
#include "hal/i2c.hal.hpp"
#include "hal/lcd.hal.hpp"
#include "hal/lcd-font.hal.hpp"
#include "hal/piezo.hal.hpp"
#include "util/gui.hpp"
#include "alarm-manager.hpp"

#include "stdio.h"

constexpr uint16_t SENSOR_MAX = 4096;

void firmwareSetup()
{
  AlarmManager::setStatus(AlarmStatus::SETUP);

  HAL::init();
  HAL::USART::init();
  HAL::AdConverter::init();
  HAL::I2C::init();
  HAL::LcDisplay::init();
  HAL::LcDisplay::clearCustomChars();
  HAL::LcDisplay::addCustomChar(CUSTOM_CHAR_BELL, HAL::LcdFont::BELL);

  new HAL::GPIO_INTERRUPT(MODE_BUTTON_PIN, MODE_BUTTON_PORT, EXTI2_3_IRQn);
  new HAL::GPIO_INTERRUPT(ARM_BUTTON_PIN, ARM_BUTTON_PORT, EXTI4_15_IRQn);

  HAL::GPIO_Out *onboardLED = new HAL::GPIO_Out(ONBOARD_LED_PIN, ONBOARD_LED_GPIO_PORT);
  HAL::Piezo::init(PIEZO_PIN, PIEZO_GPIO_PORT);
  HAL::Piezo::setFrequency(1000);
  HAL::Piezo::setBlink(200);

  uint16_t sensorValue;

  HAL::USART::print("Setup done\r\n");
  AlarmManager::setStatus(AlarmStatus::DISARMED);

  while (1)
  {
    HAL_Delay(100);
    onboardLED->toggle();

    HAL::USART::clearScreen();
    HAL::LcDisplay::clearDisplay();

    sensorValue = HAL::AdConverter::getValue();
    AlarmManager::checkThresholdExceeded(sensorValue);

    switch (AlarmManager::getStatus())
    {
    case AlarmStatus::TRIPPED:
      HAL::USART::print("ALARM!\r\n");
      HAL::LcDisplay::printf(" \x1 \x1 ALARM! \x1 \x1 ");
      HAL::LcDisplay::printf("press any key...");
      continue;
      break;

    case AlarmStatus::DISARMED:
      AlarmManager::setThresholdOrigin(sensorValue);
      HAL::USART::printf("Not Armed\r\n");
      HAL::LcDisplay::printf("   Not Armed   ");
      break;

    case AlarmStatus::ARMED:
      HAL::USART::printf("!! ARMED !!\r\n");
      HAL::LcDisplay::printf("   !! ARMED !!   ");
      break;

    default:
      break;
    }

    char bar[LCD_CHARACTERS_PER_LINE];
    GUI::getPressureDisplayStr(bar, sensorValue, SENSOR_MAX, LCD_CHARACTERS_PER_LINE, AlarmManager::getThresholdOrigin(), AlarmManager::getThresholdWidth());
    HAL::LcDisplay::setCursor(1, 0);
    HAL::LcDisplay::print(bar);

    HAL::USART::print(bar, LCD_CHARACTERS_PER_LINE);
  }
}

void firmwareLoop()
{
}
