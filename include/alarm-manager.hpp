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
const int POSSIBLE_THRESHOLD_WIDTHS[POSSIBLE_THRESHOLD_WIDTHS_LENGTH] = {500, 1000, 1500};

class AlarmManager
{
private:
  static AlarmStatus status;
  static uint16_t thresholdWidth;
  static uint16_t thresholdOrigin;

public:
  static void setStatus(AlarmStatus newStatus);
  static AlarmStatus getStatus();
  static void setThresholdWidth(uint16_t newWidth);
  static uint16_t getThresholdWidth();
  static void toggleThresholdWidth();
  static void setThresholdOrigin(uint16_t newOrigin);
  static uint16_t getThresholdOrigin();
  static void checkThresholdExceeded(uint16_t newValue);
};
