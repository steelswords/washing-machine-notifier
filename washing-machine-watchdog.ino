/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include "PersonalData.hpp"

ESP8266WiFiMulti WiFiMulti;

String urlencode(String msg);

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("The Promised LAN", "Tristanisgreat");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    String phoneNumber = String(TARGET_PHONE);
    String textbeltAPIKey = String(TEXTBELT_API_KEY);
    textbeltAPIKey = "textbelt_test";
    String message = String("Your washing is done.");
#if 0
    String url = String("http://textbelt.com/text");
    String postPayload = String("phone=") + phoneNumber
                + "&message=" + urlencode(message)
                + "&key=" + textbeltAPIKey;
    Serial.println(url);
    Serial.println(postPayload);
#endif
#if 0
    String url = String("http://textbelt.com/text?");
    url += String("phone=") + phoneNumber
                + "&message=" + urlencode(message)
                + "&key=" + textbeltAPIKey;
    Serial.println(url);
    String postPayload = "";
    Serial.println(postPayload);

#endif
#if 1
    String url = String("http://textbelt.com/text");
    String postPayload = "{\"phone\":\"" + phoneNumber + "\","
                        + "\"message\": \"" + message +"\","
                        + "\"key\": \"" + textbeltAPIKey + "\"}"; 
    Serial.println(postPayload);
#endif
    if (http.begin(client, url)) {  // HTTP
      int httpCode = http.POST(postPayload);
      
      //if the code is negative, there was an error.
      if (httpCode > 0)
      {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
        
    }
    
#if 0
    if (http.begin(client, "http://jigsaw.w3.org/HTTP/connection.html")) {  // HTTP


      Serial.print("[HTTP] POST...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect\n");
    }
#endif
  }

  delay(10000);
  while (true)
  {
    delay(10000);
    Serial.println("That's all, folks!");
  }
}

String urlencode(String msg)
{
  String output;
  int len = msg.length();
  for (int i = 0; i < len; ++i)
  {
    //TODO: This only handles spaces right now. There is a whole lot more that could go wrong.
    if (msg[i] == ' ')
    {
      output += "%20";
    }
    else
    {
      output += msg[i];
    }
  }
  return output;
}
