# Washing Machine Notifier

This is a gadget that you can slap on your washing machine or drier with a magnet
and it will text you when it detects the machine has stopped shaking. The design 
utilizes an accelerometer, a wifi-enabled microcontroler, the ESP8266, and texting
by Textbelt API. All the code is built as an Arduino project, since it is an 
out-of-the-box way to program the ESP8266.

Note: This project is missing a file, PersonalData.hpp, which defines the following macros:
- `TARGET_PHONE`
- `TEXTBELT_API_KEY`
- `WIFI_SSID`
- `WIFI_PSK`

These are self-explanatory.
