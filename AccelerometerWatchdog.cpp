#include "AccelerometerWatchdog.hpp"

void AccelerometerWatchdog::watch()
{
  int sample = 0;
  int delta = 0;
  int calmSamples = 0;
  int calmSamplesToBeDone = m_maxCalmTime / m_delayTime;
  int secondChances = 0;
  while (calmSamples < calmSamplesToBeDone)
  {
    sample = analogRead(m_zPin);

    Serial.print("AnalogValue = ");
    Serial.println(analogRead(A0));
    //Get absolute delta from the norm.
    delta = m_centerLevel - sample;
    if (delta < 0) delta *= -1; //If need faster code, could add a fancy hex value instead of a mult.

    //If delta is less than threshold, add to number of calm samples.
    if (delta < m_deltaThreshold)
    {
      ++calmSamples;
    }
    else
    {
      //Second chances allow a few bumps/blips in the "calm time"
      //without having to start the calm period over again.
      if (++secondChances > 5)
      {
        secondChances = 0;
        calmSamples = 0;
      }
    }

    delay(m_delayTime);
  }
  digitalWrite(13, LOW);
}
