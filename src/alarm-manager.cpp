#include "alarm-manager.hpp"

AlarmStatus AlarmManager::status = AlarmStatus::NONE;
uint16_t AlarmManager::thresholdWidth = POSSIBLE_THRESHOLD_WIDTHS[0];

void AlarmManager::setStatus(AlarmStatus newStatus)
{
  status = newStatus;
}

AlarmStatus AlarmManager::getStatus()
{
  return status;
}

void AlarmManager::setThresholdWidth(uint16_t newWidth)
{
  thresholdWidth = newWidth;
}

uint16_t AlarmManager::getThresholdWidth()
{
  return thresholdWidth;
}

void AlarmManager::toggleThresholdWidth()
{
  for (int i = 0; i < POSSIBLE_THRESHOLD_WIDTHS_LENGTH; i++)
  {
    if (POSSIBLE_THRESHOLD_WIDTHS[i] > thresholdWidth)
    {
      thresholdWidth = POSSIBLE_THRESHOLD_WIDTHS[i];
      return;
    }
  }
  thresholdWidth = POSSIBLE_THRESHOLD_WIDTHS[0];
}
