#include "AccelerometerWatchdog.hpp"

void AccelerometerWatchdog::watch()
{
  int sample = 0;
  int delta = 0;
  //int calmSamples = 0;
  //int calmSamplesToBeDone = m_maxCalmTime / m_delayTime;
  int secondChances = 0;
  unsigned long timeItHasBeenCalm_ms = 0;
  unsigned long prev_ms = 0;
  unsigned long now_ms = millis();


  while (timeItHasBeenCalm_ms < m_calmTime_ms)
  {
    prev_ms = now_ms;
    now_ms = millis();
    sample = analogRead(m_accelPin);

    //Serial.print("AnalogValue = ");
    //Serial.println(sample);

    //Get absolute delta from the norm.
    delta = m_centerLevel - sample;
    if (delta < 0) delta *= -1; //If need faster code, could add a fancy hex value instead of a mult.

    //If delta is less than threshold, add to time it has been calm
    if (delta < m_deltaThreshold)
    {
      //Associate addition first in case clock errors introduce an overflow in the subtraction.
      timeItHasBeenCalm_ms = (timeItHasBeenCalm_ms + now_ms) - prev_ms;
      Serial.print("Time it has been calm: ");
      Serial.println(timeItHasBeenCalm_ms);
    }
    else
    {
      timeItHasBeenCalm_ms = 0;
#if 0
      //Second chances allow a few bumps/blips in the "calm time"
      //without having to start the calm period over again.
      if (++secondChances > 5)
      {
        secondChances = 0;
        calmSamples = 0;
      }
#endif
    }

    delay(100);
  }
  digitalWrite(13, LOW);
}
