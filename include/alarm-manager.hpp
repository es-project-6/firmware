#pragma once

#include <stdint.h>

enum AlarmStatus
{
  NONE,
  SETUP,
  DISARMED,
  ARMED,
  TRIPPED
};

const int POSSIBLE_THRESHOLD_WIDTHS_LENGTH = 3;
const int POSSIBLE_THRESHOLD_WIDTHS[POSSIBLE_THRESHOLD_WIDTHS_LENGTH] = {250, 500, 1000};

class AlarmManager
{
private:
  static AlarmStatus status;
  static uint16_t thresholdWidth;

public:
  static void setStatus(AlarmStatus newStatus);
  static AlarmStatus getStatus();
  static void setThresholdWidth(uint16_t newWidth);
  static uint16_t getThresholdWidth();
  static void toggleThresholdWidth();
};
