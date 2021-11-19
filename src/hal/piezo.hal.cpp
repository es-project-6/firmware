#include "hal/piezo.hal.hpp"

namespace HAL
{
  void Piezo::init(uint32_t pin, GPIO_TypeDef *port, unsigned int frequency)
  {
    gpioPin = new HAL::GPIO_Out(pin, port);
    setFrequency(frequency);
  }

  void Piezo::update()
  {
    if (blinkPeriod && HAL_GetTick() > lastBlink + blinkPeriod)
    {
      lastBlink = HAL_GetTick();
      muted = !muted;
    }
    if (!enabled || muted)
    {
      return;
    }

    if (HAL_GetTick() * 1000 > lastPeriod + period)
    {
      lastPeriod = HAL_GetTick() * 1000;
      gpioPin->toggle();
    }
  }

  void Piezo::setFrequency(unsigned int frequency)
  {
    period = 1000000 / frequency;
  }

  void Piezo::setBlink(unsigned int period)
  {
    if (!period)
    {
      muted = false;
    }

    blinkPeriod = period;
  }

  void Piezo::setEnabled(bool enabled)
  {
    Piezo::enabled = enabled;
  }
}
