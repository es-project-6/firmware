#include "alarm-manager.hpp"

AlarmStatus AlarmManager::status = AlarmStatus::NONE;

void AlarmManager::setStatus(AlarmStatus newStatus)
{
  status = newStatus;
}

AlarmStatus AlarmManager::getStatus()
{
  return status;
}
