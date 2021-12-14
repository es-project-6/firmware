#pragma once

enum AlarmStatus { NONE, SETUP, DISARMED, ARMED, TRIPPED };

class AlarmStatusManager
{
private:
  static AlarmStatus status;

public:
  static void setStatus(AlarmStatus newStatus);
  static AlarmStatus getStatus();
};
