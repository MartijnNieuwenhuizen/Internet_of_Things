// ToDo:
  // Post all data insead of singles.
  // Get data from function by a return.
  // Do function With Millis and not a Delay.

// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

// WiFi
char ssid[] = "SWEEX1337";
char password[] = "billgatesrules";

// URL
String host = "http://localhost:3000/"; // need to change this!
const int httpPort = 80;
WiFiClient client;
HTTPClient http;

// init
int ldrSensor = A0;
int pirSensor = D2;
int pirValue;
int pirState;
int ldrValue;
int soundValue;

void setup() {

  pinMode(pirSensor, INPUT);
  pinMode(ldrSensor, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  
  Serial.begin(9600);

}

void loop() {

  String sendData = "Test connection";
  http.begin(host + sendData);

  Serial.println("In The POST");
  Serial.println(sendData);
  
  
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  

  int httpCode = http.POST(sendData);

  if (httpCode > 0) {
    Serial.println("POST request gelukt");
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.println(http.errorToString(httpCode).c_str());
  }

  http.end();
  
}
