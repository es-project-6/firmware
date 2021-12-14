#include "util/c_wrapper.util.hpp"
#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/btns.hal.hpp"

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

  void wrappedFirmwareSetup()
  {
    firmwareSetup();
  }

  void wrappedFirmwareLoop()
  {
    firmwareLoop();
  }

  void wrappedFirmwareSysTick()
  {
    HAL::SystickHandler();
  }

  void buttonPressed(uint16_t pin)
  {
    HAL::Buttons::handle(pin);
  }

#ifdef __cplusplus
}
#endif