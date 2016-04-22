// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WiFi Settings
//char ssid[] = "FRITZ!Box Fon WLAN 7340"; //  Network Name
//char password[] = "3608432098104837"; // Network Password

char ssid[] = "iPhone van Martijn"; //  Network Name
char password[] = "wortels18"; // Network Password

// Host + Path (needed for GET Connection)
char* host = "www.martijnnieuwenhuizen.nl";
String path = "/esp/light.json";

const int httpPort = 80;

// RGB Led Setup
int redLed = D1;
int greenLed = D2;
int blueLed = D3;

// Setup Wifi Client + Ip
WiFiClient client;
IPAddress ip(192,168,178,114);

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

  // Print if not connected
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
  }
  
  client.print(String("GET ") + path + " HTTP/1.1\r\n" + 
    "Host: " + host + "\r\n" + 
    "Connection: keep-alive\r\n\r\n");  

  delay(500);

  String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    // Serial.print(line);
    // we’ll parse the HTML body here
    if (section=="header") { // headers..
      Serial.print(".");
      if (line=="\n") { // skips the empty space at the beginning 
        section="json";
      }
    }
    else if (section=="json") {  // print the good stuff
      section="ignore";
      String result = line.substring(1);

      // Parse JSON
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

      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed["light"], "green") == 0) {
        setColor(255, 0, 0);
        Serial.println("LED green");
      }
      else if (strcmp(json_parsed["light"], "red") == 0) {
        setColor(0, 255, 0);
        Serial.println("led red");
      }
      else if (strcmp(json_parsed["light"], "blue") == 0) {
        setColor(0, 0, 255);
        Serial.println("led blue");
      }
      else {
        setColor(255, 255, 255);
        Serial.println("led all");
      }
    }
  }

  // POST
 // Define data
 String data;
 String light;
 light = String(analogRead(A0));
 data = "light="+light;

 //check if and connect the nodeMCU to the server
 if(client.connect(host, httpPort)) {
   //make the POST headers and add the data string to it
   client.println("POST /esp/index.php HTTP/1.1");
   client.println("Host: www.martijnnieuwenhuizen.nl:80");
   client.println("Content-Type: application/x-www-form-urlencoded");
   client.println("Connection: close");
   client.print("Content-Length: ");
   client.println(data.length());
   client.println();
   client.print(data);
   client.println();
   Serial.println(light);
   Serial.println("Data send");

   //print the response to the USB
//    while(client.available()){
//      String line = client.readStringUntil('\r');
//      Serial.print(line);
//    }
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
