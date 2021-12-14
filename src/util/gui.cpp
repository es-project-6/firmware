#include "util/gui.hpp"

#include <math.h>

uint16_t round(uint16_t d)
{
  return floor(d + 0.5);
}

uint16_t mapValToRange(uint16_t val, uint16_t valMin, uint16_t valMax, uint16_t rangeMin, uint16_t rangeMax)
{
  return (val - valMin) * (rangeMax - rangeMin) / (valMax - valMin) + rangeMin;
}

void GUI::getPressureDisplayStr(char *buf, uint16_t val, uint16_t maxVal, uint8_t width, uint16_t thresholdOrigin, uint16_t thresholdWidth)
{
  uint16_t mappedVal = mapValToRange(val, 0, maxVal, 0, width);
  uint16_t mappedThresLower = mapValToRange(thresholdOrigin - thresholdWidth, 0, maxVal, 0, width);
  uint16_t mappedThresUpper = mapValToRange(thresholdOrigin + thresholdWidth, 0, maxVal, 0, width);
  uint16_t mappedThresOrigin = mapValToRange(thresholdOrigin, 0, maxVal, 0, width);

  for (uint8_t i = 0; i < width; i++)
  {
    if (i == mappedVal)
    {
      buf[i] = 'o';
    }
    else if (i == mappedThresOrigin)
    {
      buf[i] = '|';
    }
    else if (i == mappedThresLower)
    {
      buf[i] = '>';
    }
    else if (i == mappedThresUpper)
    {
      buf[i] = '<';
    }
    else
    {
      buf[i] = ' ';
    }
  }
}
