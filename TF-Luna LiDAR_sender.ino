#include <Wire.h>
#include <espnow.h>
#include <ESP8266WiFi.h>
#include "ArduinoJson.h"
#include <TFLI2C.h>

TFLI2C tfli2c;
uint8_t broadcastAddress[] = { 0XEC, 0X64, 0XC9, 0XD3, 0X80, 0X0A }; 
int16_t distance = 0;
uint8_t lidarAddress = 0x10;
String json;
StaticJsonDocument<200> doc;

typedef struct struct_message 
{
  String json;
}
struct_message;
struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) 
{
  Serial.print("\r\nLast Packet Send Status: ");
  if (sendStatus == 0) 
  {
    Serial.println("Delivery success");
  } 
  else 
  {
    Serial.println("Delivery fail");
  }
}

void sendData(int value) 
{
  json = GetJSONString(value); 
  myData.json = json;

  const char* jsonString = json.c_str();  
  size_t sizeBuff = strlen(jsonString);  
  esp_now_send(broadcastAddress, (uint8_t*)jsonString, sizeBuff);  
}

void setup() 
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != 0) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  Wire.begin();
  Serial.println("TF-Luna initialization complete!");
}

void loop() 
{
  bool success = tfli2c.getData(distance, lidarAddress);
  if (success) 
  {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= 10) 
    {
      Serial.println("Sending 1 (Green LED ON)");
      sendData(1); 
    } 
    else 
    {
      Serial.println("Sending 0 (Red LED ON)");
      sendData(0); 
    }
  } 
  else 
  {
    Serial.println("Failed to read data from TF-Luna!");
  }

  delay(100); 
}

String GetJSONString(int distance) 
{
  StaticJsonDocument<1024> staticJsonDocument;
  staticJsonDocument["distance"] = distance; 
  char docBuf[1024];
  serializeJson(staticJsonDocument, docBuf);
  return String(docBuf);
}

