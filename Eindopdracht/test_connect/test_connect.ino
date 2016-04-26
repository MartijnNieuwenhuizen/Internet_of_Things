// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

// WiFi
char ssid[] = "iPhone van Martijn";
char password[] = "wortels18";

// URL
String host = "http://api.leandervanbaekel.nl/esp/";
const int httpPort = 80;
WiFiClient client;
HTTPClient http;

// init
int ldrSensor = A0;
int pirSensor = D1;
int pirValue;
int pirState;
int ldrValue;

// what I think it must be like
char theJson[] = "{light:0,movement:true,sound:480}";
// what the tutorial is like
char theJson[] = "{\"light\":\"0\",\"movement\":true\",\"sound\":480}";

void setup() {

  pinMode(pirSensor, INPUT);
  pinMode(ldrSensor, INPUT);

  WiFi.begin(ssid, password);
  
  Serial.begin(9600);

}

void loop() {

  // Motion
  readmotion();

  // Light
  readLight();
  
  delay(500);
  
}


// The three reading values
void readLight() {

  ldrValue = analogRead(ldrSensor);
  Serial.println(ldrValue);

//  postRequest(ldrValue);
  
}

void readmotion() {

  pirState = digitalRead(pirSensor);

  if ( pirState == HIGH ) {

    Serial.println("Motion!");
    pirValue = 1;

  } else {

    Serial.println("No Motion!");
    pirValue = 0;
    
  }

  postRequest(pirValue);
  
}

void readSound() {
  
}

void postRequest(int value) {
 
 // By Sem
 
  Serial.println(value);
  http.begin(host);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String sendData = "value=" + String(value);

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
