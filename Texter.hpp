#pragma once

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

class Texter
{
public:
  void text(String msg);
  static String urlEncode(String message);
  Texter(String APIKey, String phoneNumber);
  
  String m_APIKey;
  String m_phoneNumber;
  String m_host;
private:
  WiFiClient m_client;  
};
