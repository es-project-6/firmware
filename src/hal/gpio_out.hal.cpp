#include "hal/gpio_out.hal.hpp"
#include "stm32l0xx_hal.h"

namespace HAL
{
  GPIO_Out::GPIO_Out(uint32_t pin, GPIO_TypeDef *port)
      : GPIO(pin, port)
  {
  }

  void GPIO_Out::toggle()
  {
    HAL_GPIO_TogglePin(this->port, this->pin);
  }
}