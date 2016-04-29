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

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  
  Serial.begin(9600);
  
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }

}

void loop() {

  // Motion
  readmotion();

  // Light
  readLight();

  // Sound
  readSound();

  // Put values in the POST
  postRequest(pirValue, ldrValue, soundValue);
  
  delay(10000);
  
}


// The three reading values
void readLight() {

  ldrValue = analogRead(ldrSensor);
//  Serial.println(ldrValue);
  
}

void readmotion() {

  pirState = digitalRead(pirSensor);

  if ( pirState == HIGH ) {

//    Serial.println("Motion!");
    pirValue = 1;

  } else {

//    Serial.println("No Motion!");
    pirValue = 0;
    
  }
  
}

void readSound() {
  if ( Serial.read() == -1) {
    soundValue = 0;
  } else {
    soundValue = Serial.read();  
  }
  
  
  Serial.println("Sound");
  Serial.println(soundValue);
  
}

void postRequest(int pirPost, int ldrPost, int soundPost) {

  String sendData = "esp2/" + String(pirPost) + "/" + String(ldrPost) + "/" + String(soundPost);
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
