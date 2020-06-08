/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include "Texter.hpp"

//The following defines my API key, phone number, and Wifi creds.
#include "PersonalData.hpp"

ESP8266WiFiMulti WiFiMulti;
Texter texter(TEXTBELT_API_KEY, TARGET_PHONE);

void setup() {
  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PSK);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }


  // wait for WiFi connection
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    delay(50);
  }
  Serial.println("Connected to network.");

  texter.text("Your washing is done.");

}

void loop() {

  while (true)
  {
    delay(10000);
    Serial.println("That's all, folks!");
  }
}

