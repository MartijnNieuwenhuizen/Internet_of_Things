#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>

EIoTCloudRestApi eiotcloud;

void setup() {
  Serial.begin(9600);
    eiotcloud.begin();
}

void loop() {
  int sound = analogRead(A0);
  Serial.println(sound);
  eiotcloud.sendParameter("5703acb8c943a0661cf314a1/udqPvogb1j0zanrA", sound);
}
