// Include Library
#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>

// What is this?
EIoTCloudRestApi eiotcloud;

// Setup
void setup() {
  Serial.begin(9600);
  eiotcloud.begin();
}

// Program loop
void loop() {
  int sound = analogRead(A0);
  int switcher = digitalRead(A1);
  Serial.println(sound);
  Serial.println(switcher);
  // Sent to sever
//  eiotcloud.sendParameter("5703acb8c943a0661cf314a1/udqPvogb1j0zanrA", sound);
//  eiotcloud.sendParameter("5703acb8c943a0661cf314a1/vAMd23X54wh4HITt", switcher);
}
