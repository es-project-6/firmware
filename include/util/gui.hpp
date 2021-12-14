#pragma once

#include <stdint.h>

class GUI
{
public:
  static void getPressureDisplayStr(char *buf, uint16_t val, uint16_t maxVal, uint8_t width, uint16_t constrLower, uint16_t constrUpper);
};
