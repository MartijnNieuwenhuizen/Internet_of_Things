#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

char ssid[] = "iPhone van Martijn";
char password[] = "wortels18";

char* host = "http://martijnnieuwenhuizen.nl/";    
String path = "esp/light.json";  
int lightPin = D1;

int delayAmount = 500;

void setup() {
  pinMode(lightPin, OUTPUT);

  WiFi.begin(ssid, password);
  int wifi_ctr = 0;

}

void loop() {
  WiFiClient client;
  
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");

  delay(500); // wait for server to respond
  
  int dir = 0; 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);

    int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }

     if (strcmp(json_parsed["light"], "on") == 0) {
        digitalWrite(lightPin, HIGH); 
        Serial.println("LED ON");
      }
      else {
        digitalWrite(lightPin, LOW);
        Serial.println("led off");
      }
    
  }
}
