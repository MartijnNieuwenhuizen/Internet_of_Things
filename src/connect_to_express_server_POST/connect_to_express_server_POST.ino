// Libraries
#include <ESP8266WiFi.h>

// WiFi Settings
//char ssid[] = "iPhone van Martijn";
//char password[] = "wortels18";
char ssid[] = "FRITZ!Box Fon WLAN 7340"; //  Network Name
char password[] = "3608432098104837"; // Network Password

// Init
String data;
int light;

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
  // Read the analog meter
  light = analogRead(A0);

  // Set int value (number) to string
  String lightString = String(light);
  data = "light=" + lightString;


  // Thx Casper for this bit of code,
  // and the helping hand to setup the server!
  if (server.connect(ip, 8000)) { // Run if you're connected to your server
    server.println("POST / HTTP/1.1");
    server.println("Host: 192.168.178.114:8000");
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
  delay(500);
}
