#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

char ssid[] = "iPhone van Martijn";
char password[] = "wortels18";

char* host     = "http://martijnnieuwenhuizen.nl/";    
String path          = "esp/light.json";  
int pin        = D1;

void setup() {  
  
  pinMode(pin, OUTPUT); 
  pinMode(pin, HIGH);
  Serial.begin(115200);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: " + WiFi.localIP());
}

void loop() {  
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;

  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");

  delay(500); // wait for server to respond

  // read response
  int dir = 0; 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    // we’ll parse the HTML body here
  }
  Serial.print("closing connection. ");
}
