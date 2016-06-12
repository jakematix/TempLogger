

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain and modified by JKa

#include "DHT.h"
#include <Bridge.h>
#include <Console.h>
#include <YunClient.h>
#include <YunServer.h>
#include <ArduinoJson.h>

#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V! Yun is operating at 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.

DHT dht(DHTPIN, DHTTYPE);
YunClient client;
// IPAddress server(192,168,10,49);


float temperature;
float humidity;
float heat_index;
String parameter = ""; // Show POST parameters


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  Console.begin();
  digitalWrite(13, LOW);
  Console.print("DHT TESTI");
  dht.begin();

}



void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Celsius (isFahreheit = false)
  heat_index = dht.computeHeatIndex(temperature, humidity, false);

  if (client.connect("192.168.10.49", 80)) {
    Serial.println("Connected to server!");
    delay(2500);
    parameter = "temp1="+String(temperature)+"&hum1="+String(humidity)+"&heat1="+String(heat_index);
    client.println("GET /add.php?"+parameter+" HTTP/1.1");
    client.println("Host:192.168.10.49");
    client.println("Connection-Type: application/x-www-form-urlencoded");
    client.println();
    client.println("Connection:Close");
  }
  else {
    Serial.println("Connection failed!");
    delay(1000);
  }
  if(client.connected()) {
    client.stop();
  }

  delay(2000);

}
