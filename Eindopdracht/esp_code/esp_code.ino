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
int pirSensor = D2;
int pirValue;
int pirState;
int ldrValue;
int soundValue;

// what I think it must be like
//char theJson[] = "{light:0,movement:true,sound:480}";
// what the tutorial is like
//char theJson[] = "{\"light\":\"0\",\"movement\":true\",\"sound\":480}";

void setup() {

  pinMode(pirSensor, INPUT);
  pinMode(ldrSensor, INPUT);

  WiFi.begin(ssid, password);
  
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

}

void loop() {

  // Motion
  readmotion();

  // Light
  readLight();

  // Sound
  int sound = readSound();
  Serial.println(sound);
  
  // ToDo:
  // Post all data insead of singles.
  // Get data from function by a return.
  // Do function With Millis and not a Delay.
  
  delay(2000);
  
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

//  postRequest(pirValue);
  
}

void readSound() {
  
  soundValue = Serial.read();
  Serial.println(soundValue);

  return soundValue;
  
}

void postRequest(int value) {
 
 // By Sem
  Serial.println("In The POST");
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
