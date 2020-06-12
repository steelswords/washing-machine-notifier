#pragma once

#include "Arduino.h"
#include "Texter.hpp"

class AccelerometerWatchdog
{
public:
  AccelerometerWatchdog(int zPin, int maxCalmTime, Texter* texter)
    : m_zPin(zPin),
      m_maxCalmTime(maxCalmTime),
      m_texter(texter)
  {
    pinMode(zPin, INPUT);
  }

  void watch();

  int m_zPin;
  int m_maxCalmTime;
  Texter* m_texter;

  int m_deltaThreshold = 5;
  int m_centerLevel = 403;
  int m_delayTime = 100;
};
