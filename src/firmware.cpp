#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/led.hal.hpp"
#include "hal/usart.hal.hpp"

void firmwareSetup()
{
  HAL::init();

  HAL::LED *onboardLED = new HAL::LED(ONBOARD_LED_PIN, ONBOARD_LED_GPIO_PORT);
  HAL::USART::init();

  while (1)
  {
    onboardLED->toggle();
    HAL::USART::print("Moin Moin!\r\n");

    HAL_Delay(200);
  }
}

void firmwareLoop()
{
}
