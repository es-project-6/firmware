#include "hal/btns.hal.hpp"
#include "hal/pins.hal.hpp"
#include "alarm-manager.hpp"

namespace HAL
{
  void Buttons::handle(uint16_t pin)
  {
    switch (pin)
    {
    case MODE_BUTTON_PIN:
      AlarmManager::toggleThresholdWidth();
      break;

    case ARM_BUTTON_PIN:
      if (AlarmManager::getStatus() != AlarmStatus::DISARMED)
      {
        AlarmManager::setStatus(AlarmStatus::DISARMED);
      }
      else
      {
        AlarmManager::setStatus(AlarmStatus::ARMED);
      }
      break;

    default:
      break;
    }
  }
}
