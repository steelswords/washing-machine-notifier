/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

//The following defines my API key, phone number, and Wifi creds.
#include "PersonalData.hpp"

ESP8266WiFiMulti WiFiMulti;

String urlencode(String msg);

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


  while (WiFiMulti.run() != WL_CONNECTED)
  {
    delay(200);
  }
  Serial.println("Connected to network.");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    String phoneNumber = String(TARGET_PHONE);
    String textbeltAPIKey = String(TEXTBELT_API_KEY);
    String message = String("Your washing is done.");

    //Connect the client
    int clientConnectStatus = client.connect("textbelt.com", 80);
    if (!clientConnectStatus)
    {
      Serial.println("Connection Failed");
    }
    String data = String("phone=") + phoneNumber
                  + "&message=" + urlencode(message)
                  + "&key=" + textbeltAPIKey;
    String payload = String("POST /text/ HTTP/1.1\r\n");
    payload += String("Host: textbelt.com\r\n")
          + "User-Agent: ESP8266/1.0\r\n"
          + "Accept: */*\r\n"
          + "Content-Length: " + String(data.length()) + "\r\n"
          + "Content-Type: application/x-www-form-urlencoded\r\n"
          + "\r\n"
          + data + "\r\n";

    Serial.println("Payload:\n" + payload);
    Serial.println("\n---------\nSending payload");
    client.print(payload);
    Serial.print("Waiting for client to send...");
    int loopBreaker = 0;
    while (!client.available())
    {
      delay(10);
      Serial.print(".");
      if (++loopBreaker > 130) break;
    }

    while(client.available() || client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }

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
