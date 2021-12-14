#include "alarm-status-manager.hpp"

AlarmStatus AlarmStatusManager::status = AlarmStatus::NONE;

void AlarmStatusManager::setStatus(AlarmStatus newStatus)
{
  status = newStatus;
}

AlarmStatus AlarmStatusManager::getStatus()
{
  return status;
}

AlarmStatus AlarmStatusManager::getStatusString()
{
  return status;
}
