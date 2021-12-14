#include "alarm-manager.hpp"
#include "hal/piezo.hal.hpp"

#include <math.h>

AlarmStatus AlarmManager::status = AlarmStatus::NONE;
uint16_t AlarmManager::thresholdWidth = POSSIBLE_THRESHOLD_WIDTHS[0];
uint16_t AlarmManager::thresholdOrigin = 0;

void AlarmManager::setStatus(AlarmStatus newStatus)
{
  HAL::Piezo::setEnabled(newStatus == AlarmStatus::TRIPPED);
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

void AlarmManager::setThresholdOrigin(uint16_t newOrigin)
{
  thresholdOrigin = newOrigin;
}

uint16_t AlarmManager::getThresholdOrigin()
{
  return thresholdOrigin;
}

void AlarmManager::checkThresholdExceeded(uint16_t newValue)
{
  if (getStatus() != AlarmStatus::ARMED)
  {
    return;
  }

  if (abs(newValue - thresholdOrigin) > thresholdWidth)
  {
    setStatus(AlarmStatus::TRIPPED);
  }
}