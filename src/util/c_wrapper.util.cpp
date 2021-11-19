#include "util/c_wrapper.util.hpp"
#include "firmware.hpp"
#include "hal/hal.hpp"

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

#ifdef __cplusplus
}
#endif