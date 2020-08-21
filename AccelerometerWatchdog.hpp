#pragma once

#include "Arduino.h"
#include "Texter.hpp"

class AccelerometerWatchdog
{
public:
  AccelerometerWatchdog(int accelPin, unsigned long calmTime_ms, Texter* texter)
    : m_accelPin(accelPin),
      m_calmTime_ms(calmTime_ms),
      m_texter(texter)
  {
    pinMode(accelPin, INPUT);
  }

  // Returns when accelerometer is calm for m_calmTime_s
  void watch();

  unsigned long m_calmTime_ms;
  int m_accelPin = A0;

  Texter* m_texter;

  int m_deltaThreshold = 15;
  int m_centerLevel = 490;
  //int m_delayTime = 100;
};
