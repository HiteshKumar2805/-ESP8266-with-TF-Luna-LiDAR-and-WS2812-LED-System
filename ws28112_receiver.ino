#include <Wire.h>
#include <espnow.h>
#include <ESP8266WiFi.h>
#include "ArduinoJson.h"
#include "FastLED.h"

#define NUM_LEDS1 14 
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define PIN1 D0
int brightness = 255;

CRGB leds[NUM_LEDS1];
bool glowGreen = false;       
unsigned long greenStartTime; 

typedef struct struct_message 
{
  String json;
} 
struct_message;
struct_message incomingData;

void setup() 
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds, NUM_LEDS1).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);

  if (esp_now_init() != 0) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onDataReceive);
  fillLEDs(CRGB(255, 0, 0)); 
}

void onDataReceive(uint8_t *mac, uint8_t *incomingDataRaw, uint8_t len) 
{
  String jsonString = String((char *)incomingDataRaw);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, jsonString);
  if (error) 
  {
    Serial.println("Failed to parse JSON!");
    return;
  }

  int distance = doc["distance"];
  Serial.print("Received data: ");
  Serial.println(distance);

  if (distance == 1) 
  {
    glowGreen = true;
    greenStartTime = millis();
    fillLEDs(CRGB(0, 255, 0)); 
  }
}

void fillLEDs(CRGB color) 
{
  for (int i = 0; i < NUM_LEDS1; i++) 
  {
    leds[i] = color; 
  }
  FastLED.show(); 
}

void loop() 
{
  if (glowGreen && millis() - greenStartTime > 10000) 
  {
    glowGreen = false; 
    fillLEDs(CRGB(255, 0, 0));
  }
}
