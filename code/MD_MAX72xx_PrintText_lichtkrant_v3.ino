// Use the MD_MAX72XX library to Print some text on the display
// This code puts the time in dutch text on a max7219 display and shows news, weather forecasts and rain messages in between
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <ezTime.h>
#include <MD_Parola.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "Parola_Fonts_data.h"

// Define the number of devices we have in the chain and the hardware interface
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 16

#define CLK_PIN   D5 //13  // or SCK
#define DATA_PIN  D7 //11  // or MOSI
#define CS_PIN    D6 //10  // or SS Normaal D8, maar die is kapot
#define  DELAYTIME  100  // wait a bit between updates of the display in milliseconds 

// SPI hardware interface
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Text parameters
#define CHAR_SPACING  1 // number of pixels between characters. 1 is very tight

#define BUF_SIZE  500 // Global message buffers shared by Serial and Scrolling functions
char message[BUF_SIZE];
char messageTemp[BUF_SIZE];
char tijd_tekst[50];
char tijd_tekst_oud[50];
char* HostName = "Lichtkrant";
boolean WifiConnected = false;

// MQTT Broker IP address
const char* mqtt_server = "FILL IN THE IP OF YOUR MQTT SERVER";
Timezone myTZ;

WiFiClient espLichtkrant;
PubSubClient client(espLichtkrant);

uint8_t SmallSpace[] = { 1, 0 }; // Reduced the space to one column, to make the text fit on the display

void setup() {
  unsigned long startmillis;
  P.begin();
  P.setIntensity(1);
  P.addChar(' ', SmallSpace);
  P.print("   wait for wifi connect");
  startmillis = millis();
  setup_wifi();
  Serial.printf("Setup Wifi took: %u ms\n", millis() - startmillis);
  startmillis = millis();
  P.print("   wait for MQTT connect");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.printf("Setup MQTT took: %u ms\n", millis() - startmillis);
  Serial.println("[MD_MAX72XX Message Display]");
  Serial.println("wait for time sync");
  P.print(" wait for time sync");
  startmillis = millis();
  waitForSync();
  Serial.printf("Time sync took: %u ms\n", millis() - startmillis);
  P.print("  time synced");
  if (!myTZ.setCache(0)) myTZ.setLocation(F("nl"));
}

void loop() {
  events();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if (myTZ.hour() == 7 && myTZ.minute() == 00 && myTZ.second() == 0)ESP.restart();
  ArduinoOTA.handle();
  NL_tijd_tekst(myTZ.minute(), myTZ.hour(), tijd_tekst);
  if (P.displayAnimate() and strcmp(tijd_tekst, tijd_tekst_oud) != 0) { // animates and returns true when an animation is completed
    P.displayText(tijd_tekst, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    strcpy(tijd_tekst_oud, tijd_tekst);
  }
}
