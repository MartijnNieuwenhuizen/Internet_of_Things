// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WiFi Settings
char ssid[] = "iPhone van Martijn"; //  Network Name
char password[] = "wortels18"; // Network Password

// Host + Path (needed for GET Connection)
char* host = "www.martijnnieuwenhuizen.nl";
String path = "/get-up-stand-up/data.json";

const int httpPort = 80;

// RGB Led Setup
int redLed = D1;
int greenLed = D2;
int blueLed = D3;

int  buttonPin = D7; 
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

// Setup Wifi Client + Ip
WiFiClient client;

void setup() {  
  // Set RGB Leds
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);  
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  // Confirm Wifi Connection
  Serial.println("WiFi connected");  
  Serial.println("IP address: " + WiFi.localIP());
}

void loop() {

  // Print Host
  Serial.print("connecting to ");
  Serial.println(host);
  
  String data;
  String sitting;
  sitting = String(digitalRead(D7));
  data = "sitting="+sitting;

 //check if and connect the nodeMCU to the server
 if(client.connect(host, httpPort)) {
   //make the POST headers and add the data string to it
   client.println("POST /get-up-stand-up/index.php HTTP/1.1");
   client.println("Host: www.martijnnieuwenhuizen.nl:80");
   client.println("Content-Type: application/x-www-form-urlencoded");
   client.println("Connection: close");
   client.print("Content-Length: ");
   client.println(data.length());
   client.println();
   client.print(data);
   client.println();
   Serial.println(data);
   Serial.println("Data send");

   //print the response to the USB
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
 } else {
   Serial.println("Something went wrong");
 }
     
  // wait .5s to reloop this loop
  delay(500);
  
}

// Set RGB Function
void setColor(int red, int green, int blue) {
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  analogWrite(redLed, red);
  analogWrite(greenLed, green);
  analogWrite(blueLed, blue);  
}
