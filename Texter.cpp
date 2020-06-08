#include "Texter.hpp"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

Texter::Texter(String APIKey, String phoneNumber)
  : m_APIKey(APIKey),
    m_phoneNumber(phoneNumber),
    m_host(String("textbelt.com"))
{
}

void Texter::text(String message)
{
  //TODO: Try with key "textbelt" first to allow us to claim on 
  // the one free text per day.

  // TODO Eventually: Make all this over HTTPS. It doesn't really matter,
  // My $5 API key isn't really worth the effort to protect at this 
  // level of deployment.
  Serial.print("[HTTP] begin...\n");

  //Connect the client
  int clientConnectStatus = m_client.connect("textbelt.com", 80);
  if (!clientConnectStatus)
  {
    Serial.println("Connection Failed");
  }

  //Assemble the HTTP Header and data
  String data = String("phone=") + m_phoneNumber
                + "&message=" + urlEncode(message)
                + "&key=" + m_APIKey;
  String payload = String("POST /text/ HTTP/1.1\r\n");
  payload += String("Host: textbelt.com\r\n")
        + "User-Agent: ESP8266/1.0\r\n"
        + "Accept: */*\r\n"
        + "Content-Length: " + String(data.length()) + "\r\n"
        + "Content-Type: application/x-www-form-urlencoded\r\n"
        + "\r\n"
        + data + "\r\n";

  Serial.println("Payload:\n" + payload);
  Serial.println("\n-------------------------");
  Serial.println("Sending payload");

  //Actually send the payload over the client
  m_client.print(payload);

  //Wait for the client to 
  Serial.print("Waiting for client to send...");
  int loopBreaker = 0;
  while (!m_client.available())
  {
    delay(10);
    Serial.print(".");
    if (++loopBreaker > 130) break;
  }

  while(m_client.available() || m_client.connected())
  {
    if (m_client.available())
    {
      String line = m_client.readStringUntil('\n');
      Serial.println(line);
    }
  }
}

String Texter::urlEncode(String msg)
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
