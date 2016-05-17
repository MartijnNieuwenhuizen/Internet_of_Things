// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WiFi Settings
char ssid[] = "Router Name";
char password[] = "Router Password";

// Init
int oneGreen = D1;
int oneRed = D2;
int twoGreen = D3;
int twoRed = D4;
int threeGreen = D5;
int threeRed = D6;
int buttonPin = D7; 

String data;
String ledStatus;
int buttonState = 0;

// Setup Wifi Client + Ip
WiFiClient server;
IPAddress ip(xxx,xxx,xxx,xxx); // Your IP adress

void setup() {  
  
  pinMode(oneGreen, OUTPUT);
  pinMode(oneRed, OUTPUT);
  pinMode(twoGreen, OUTPUT);
  pinMode(twoRed, OUTPUT);
  pinMode(threeGreen, OUTPUT);
  pinMode(threeRed, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  // Confirm Wifi Connection
  Serial.println("WiFi connected");  
}

void loop() {

  postRequest();
  getRequest();
 
  delay(2000);
}

void getRequest() {

  if (server.connect(ip, 3000)) { // Run if you're connected to your server
    server.print(String("GET ") + "/path/to/your.json" + " HTTP/1.1\r\n" +
   "Host: " + "xxx.xxx.xxx.xxx:3000" + "\r\n" + // ip adress
   "Connection: keep-alive\r\n\r\n"); 

   delay(500);

    // read response
  String section="header";
  while(server.available()){
    
    String line = server.readStringUntil('\r');
    // we’ll parse the HTML body here
    if (section=="header") { // headers..
      Serial.print(".");
      if (line=="\n") {
        section="json";
      }
    }
    // the body part
    else if (section=="json") {
      section="ignore";
      String result = line.substring(1);
      
      // Parse the JSON
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
      
      if ( strcmp(json_parsed["ledState"], "one") == 0 ) {
        Serial.println("json = One");
        setOne(255, 0);
        setTwo(0, 255);
        setThree(0, 255);
      } else if ( strcmp(json_parsed["ledState"], "two") == 0 ) {
        Serial.println("json = Two");
        setOne(255, 0);
        setTwo(255, 0);
        setThree(0, 255);
      } else if ( strcmp(json_parsed["ledState"], "three") == 0 ) {
        Serial.println("json = Three");
        setOne(255, 0);
        setTwo(255, 0);
        setThree(255, 0);
      } else  if ( strcmp(json_parsed["ledState"], "false") == 0 ) {
        Serial.println("json = false");
        setOne(0, 255);
        setTwo(0, 255);
        setThree(0, 255);
      } else  if ( strcmp(json_parsed["ledState"], "off") == 0 ) {
        Serial.println("json = off");
        
        setOne(120, 120);
        setTwo(120, 120);
        setThree(120, 120);

      } else  if ( strcmp(json_parsed["ledState"], "blink") == 0 ) {
        Serial.println("json = blink");
        
        setOne(0, 255);
        setTwo(0, 255);
        setThree(0, 255);
        
        delay(500);

        setOne(255, 0);
        setTwo(255, 0);
        setThree(255, 0);

        delay(200);
        
        setOne(0, 255);
        setTwo(0, 255);
        setThree(0, 255);
        
      } else {
        Serial.println("json = ERROR??");
      }
    }
    
  }
   
  } else {
    Serial.println("Not Connected");
  }
  
}

void postRequest() {

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    data = "sitting";
  } else {
    data = "standing";
  }

  // Thx Casper for this bit of code,
  // and the helping hand to setup the server!
  if (server.connect(ip, 3000)) { // Run if you're connected to your server
    server.println("POST / HTTP/1.1");
    server.println("Host: xxx.xxx.xxx.xxx:3000"); // your ip adress
    server.println("Content-Type: application/x-www-form-urlencoded");
    server.println("Connection: close");
    server.print("Content-Length: ");
    server.println(data.length());
    server.println();
    server.print(data);
    server.println();
    Serial.println("Data send: ");
    Serial.println(data);
  } else {
    Serial.println("Not Connected");
  }
  
}

void setOne(int green, int red) {
    red = 255 - red;
    green = 255 - green;
    analogWrite(oneGreen, green);
    analogWrite(oneRed, red);
}
void setTwo(int green, int red) {
    red = 255 - red;
    green = 255 - green;
    analogWrite(twoGreen, green);
    analogWrite(twoRed, red);
}
void setThree(int green, int red) {
    red = 255 - red;
    green = 255 - green;
    analogWrite(threeGreen, green);
    analogWrite(threeRed, red);
}
