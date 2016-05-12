// Libraries
#include <ESP8266WiFi.h>

// WiFi Settings
//char ssid[] = "iPhone van Martijn";
//char password[] = "wortels18";
char ssid[] = "iPhone van Martijn"; //  Network Name
char password[] = "wortels18"; // Network Password

// Init
String data;

// Setup Wifi Client + Ip
WiFiClient server;
IPAddress ip(172,20,10,4);

void setup() {  
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  // Confirm Wifi Connection
  Serial.println("WiFi connected");  
  Serial.println("IP address: " + WiFi.localIP());
}

void loop() {

  data = "sitting";

  // Thx Casper for this bit of code,
  // and the helping hand to setup the server!
  if (server.connect(ip, 3000)) { // Run if you're connected to your server
    server.println("POST / HTTP/1.1");
    server.println("Host: 172.20.10.4:3000");
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
  
  // wait .5s to reloop this loop
  delay(4000);
}
