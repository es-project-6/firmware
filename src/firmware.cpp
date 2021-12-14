#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/gpio.intr.hal.hpp"
#include "hal/gpio_out.hal.hpp"
#include "hal/usart.hal.hpp"
#include "hal/adc.hal.hpp"
#include "hal/i2c.hal.hpp"
#include "hal/lcd.hal.hpp"
#include "hal/piezo.hal.hpp"
#include "alarm-manager.hpp"

#include <math.h>
#include "stdio.h"

constexpr uint16_t SENSOR_MAX = 4096;

uint16_t round(uint16_t d)
{
  return floor(d + 0.5);
}

uint16_t mapValToRange(uint16_t val, uint16_t valMin, uint16_t valMax, uint16_t rangeMin, uint16_t rangeMax)
{
  return (val - valMin) * (rangeMax - rangeMin) / (valMax - valMin) + rangeMin;
}

void getPressureDisplayStr(char *buf, uint16_t val, uint16_t maxVal, uint8_t width, uint16_t constrLower, uint16_t constrUpper)
{
  uint16_t mappedVal = mapValToRange(val, 0, SENSOR_MAX, 0, width);
  uint16_t mappedConstrLower = mapValToRange(constrLower, 0, SENSOR_MAX, 0, width);
  uint16_t mappedConstrUpper = mapValToRange(constrUpper, 0, SENSOR_MAX, 0, width);

  for (uint8_t i = 0; i < width; i++)
  {
    if (i == mappedVal)
    {
      buf[i] = '|';
    }
    else if (i == mappedConstrLower)
    {
      buf[i] = '>';
    }
    else if (i == mappedConstrUpper)
    {
      buf[i] = '<';
    }
    else
    {
      buf[i] = ' ';
    }
  }
}

void firmwareSetup()
{
  AlarmManager::setStatus(AlarmStatus::SETUP);

  HAL::init();
  HAL::USART::init();
  HAL::AdConverter::init();
  HAL::I2C::init();
  HAL::LcDisplay::init();
  HAL::USART::print("Setup done\r\n");
  new HAL::GPIO_INTERRUPT(MODE_BUTTON_PIN, MODE_BUTTON_PORT, EXTI2_3_IRQn);
  new HAL::GPIO_INTERRUPT(ARM_BUTTON_PIN, ARM_BUTTON_PORT, EXTI4_15_IRQn);

  HAL::GPIO_Out *onboardLED = new HAL::GPIO_Out(ONBOARD_LED_PIN, ONBOARD_LED_GPIO_PORT);
  HAL::Piezo::init(PIEZO_PIN, PIEZO_GPIO_PORT);
  HAL::Piezo::setFrequency(1000);
  HAL::Piezo::setBlink(200);

  uint16_t sensorValue;

  AlarmManager::setStatus(AlarmStatus::DISARMED);

  while (1)
  {
    HAL_Delay(100);
    onboardLED->toggle();

    HAL::USART::clearScreen();
    HAL::LcDisplay::clearDisplay();

    sensorValue = HAL::AdConverter::getValue();

    char bar[LCD_CHARACTERS_PER_LINE];
    getPressureDisplayStr(bar, sensorValue, SENSOR_MAX, LCD_CHARACTERS_PER_LINE, .2 * SENSOR_MAX, .8 * SENSOR_MAX);

    if (sensorValue > 3500)
    {
      AlarmManager::setStatus(AlarmStatus::TRIPPED);
    }

    if (AlarmManager::getStatus() == AlarmStatus::TRIPPED)
    {
      HAL::Piezo::setEnabled(true);
      HAL::USART::print("ALARM!\r\n");
      HAL::LcDisplay::printf("ALARM!");
      continue;
    }

    HAL::USART::printf("%d, %d, %d\r\n", AlarmManager::getStatus(), AlarmManager::getThresholdOrigin(), AlarmManager::getThresholdWidth());
    HAL::LcDisplay::printf("%d, %d, %d", AlarmManager::getStatus(), AlarmManager::getThresholdOrigin(), AlarmManager::getThresholdWidth());
    char bar[LCD_CHARACTERS_PER_LINE];
    for (size_t i = 0; i < LCD_CHARACTERS_PER_LINE; i++)
    {
      bar[i] = sensorValue * LCD_CHARACTERS_PER_LINE / 4096u > i ? 0xFF : 0x00;
    }
    HAL::LcDisplay::setCursor(1, 0);
    HAL::LcDisplay::print(bar);
    
    HAL::USART::print(bar, LCD_CHARACTERS_PER_LINE);
  }
}

void firmwareLoop()
{
}
