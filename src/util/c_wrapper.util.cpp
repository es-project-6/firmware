#include "util/c_wrapper.util.hpp"
#include "firmware.hpp"

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

#ifdef __cplusplus
}
#endif