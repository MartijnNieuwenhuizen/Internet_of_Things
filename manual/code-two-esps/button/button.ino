// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WiFi Settings
char ssid[] = "Router Name";
char password[] = "Router Password";

// Init
int buttonPin = D7; 

String data;
String ledStatus;
int buttonState = 0;

// Setup Wifi Client + Ip
WiFiClient server;
IPAddress ip(xxx,xxx,xxx,xxx); // Your IP adress

void setup() {  
  
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  // Confirm Wifi Connection
  Serial.println("WiFi connected");  
}

void loop() {

  postRequest();
 
  delay(2000);
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
