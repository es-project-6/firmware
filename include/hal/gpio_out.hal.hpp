#include "hal/gpio.hal.hpp"

namespace HAL
{
  class GPIO_Out : public GPIO
  {
  public:
    GPIO_Out(uint32_t, GPIO_TypeDef *);
    ~GPIO_Out();
    void toggle();
  };
}