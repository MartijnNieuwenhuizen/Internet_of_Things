// Include Library
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>

// Setup the WiFi
//char ssid[] = "FRITZ!Box Fon WLAN 7340"; //  Network Name
//char pass[] = "3608432098104837"; // Network Password
char ssid[] = "iPhone van Martijn";
char pass[] = "wortels18";

int status = WL_IDLE_STATUS;
WiFiClient  client;

EIoTCloudRestApi eiotcloud;

// init
int windowInput = D3;
int window;
int light;

// Channel Id
long myChannelNumber = 106591; // Set channel number
const char * myWriteAPIKey = "7Q1IHZ4O5W6MHN6T";

void setup() {
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
  Serial.begin(9600);  
  pinMode(windowInput, INPUT);
  eiotcloud.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  light = analogRead(A0);
  window = digitalRead(windowInput);

  ThingSpeak.setField(1, light);
  ThingSpeak.setField(2, window);
  
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 
  eiotcloud.sendParameter("5703acb8c943a0661cf314a1/vAMd23X54wh4HITt", light);
  eiotcloud.sendParameter("5703acb8c943a0661cf314a1/gJUQnNmd56IDgEvZ", window); 
}
