// Include Library
#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>

// What is this?
EIoTCloudRestApi eiotcloud;

int windowInput = D3;
int window;
int light;

// Setup
void setup() {
  Serial.begin(9600);
  pinMode(windowInput, INPUT);
  eiotcloud.begin();
}

// Program loop
void loop() {
  light = analogRead(A0);
  window = digitalRead(windowInput);
  
  // Sent to sever
  eiotcloud.sendParameter("5703acb8c943a0661cf314a1/vAMd23X54wh4HITt", light);
  eiotcloud.sendParameter("5703acb8c943a0661cf314a1/gJUQnNmd56IDgEvZ", window);
}
