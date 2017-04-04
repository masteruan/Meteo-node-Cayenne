//#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space

#include "CayenneDefines.h"
#include "BlynkSimpleEsp8266.h"
#include "CayenneWiFiClient.h"
#include "SimpleTimer.h"
#include "DHT.h"

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "#########";

SimpleTimer timer;

// Your network name and password.
char ssid[] = "#########";
char password[] = "#########";

int led = 0;

DHT dht(12, DHT11);

void sendUptime()
{
  Cayenne.virtualWrite(V5, millis() /1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Cayenne.virtualWrite(V6, h);
  Cayenne.virtualWrite(V7, t);
}

void setup()
{
  // initialize digital pin 2 as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Cayenne.begin(token, ssid, password);
  timer.setInterval(5000L, sendUptime); // every 5 seconds
}

void loop()
{
  Cayenne.run();
  timer.run();
}

// This function will be called every time a Dashboard widget writes a value to Virtual Pin 2.
CAYENNE_IN(V2)
{
  CAYENNE_LOG("Got a value: %s", getValue.asStr());
  int i = getValue.asInt();
  
  if (i == 0)
  {
    digitalWrite(led, LOW);
  }
  else
  {
    digitalWrite(led, HIGH);
  }  
}
