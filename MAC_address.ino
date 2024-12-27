#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(9600);
  delay(1000);  // Wait for the serial monitor to initialize
  Serial.println("Starting program...");

  WiFi.mode(WIFI_STA);
  delay(500);
  String macAddr = WiFi.macAddress();
  Serial.print("MAC Address: ");
  Serial.println(macAddr);
}

void loop() {
  // Nothing to do in loop
}
