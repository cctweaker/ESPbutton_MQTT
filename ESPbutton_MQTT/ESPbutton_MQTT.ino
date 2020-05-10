#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <time.h>
#include <Wire.h>
#include <ArduinoJson.h>
// #include <FS.h>
// #include <ESP8266httpUpdate.h>

#include "private.h"
#include "mqtt.h"
#include "variables.h"

BearSSL::WiFiClientSecure net;
MQTTClient client();
time_t now;

void setup()
{
  // initialize wifi
  init_wifi();
  // get ntp time
  ntp_time();
  // take care of certs
  certification();
  // setup & connect mqtt
  mqtt_setup();
}

void loop()
{
  if (!client.connected())
    mqtt_connect();

  client.loop();

  read_PCA(); // read buttons

  delay(50);
}
