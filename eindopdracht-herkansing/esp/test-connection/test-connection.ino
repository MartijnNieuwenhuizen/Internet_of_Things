// Libraries
#include <ESP8266WiFi.h>

// WiFi Settings
char ssid[] = "FRITZ!Box Fon WLAN 7340";
char password[] = "3608432098104837";

// Init
int buttonPin = D7; 
int buttonState = 0;         // current state of the button

String data;

// Setup Wifi Client + Ip
WiFiClient server;
IPAddress ip(192,168,178,114);

void setup() {  
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  // Confirm Wifi Connection
  Serial.println("WiFi connected");  
  Serial.println("IP address: " + WiFi.localIP());
}

void loop() {

  pinMode(buttonPin, INPUT);
  
  // wait .5s to reloop this loop
  delay(4000);
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
    server.println("Host: 192.168.178.114:3000");
    server.println("Content-Type: application/x-www-form-urlencoded");
    server.println("Connection: close");
    server.print("Content-Length: ");
    server.println(data.length());
    server.println();
    server.print(data);
    server.println();
    Serial.println("Data send");
  } else {
    Serial.println("Not Connected");
  }
  
}























