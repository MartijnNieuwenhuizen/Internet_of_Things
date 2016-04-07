// Include Library
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

// Setup the WiFi
char ssid[] = "iPhone van Martijn"; //  your network SSID (name) 
char pass[] = "wortels18"; // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;

// Channel Id
long myChannelNumber = 106591; // Set channel number
const char * myWriteAPIKey = "7Q1IHZ4O5W6MHN6T";

void setup() {
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  int light = analogRead(A0);
  int window = digitalRead(D3);

  ThingSpeak.setField(1, light);
  ThingSpeak.setField(2, window);
  
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  
}
