#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

char ssid[] = "iPhone van Martijn";
char password[] = "wortels18";

char* host = "145.28.124.107";
//String path = "/esp/light.json";
int pin = D1;
String data;
int light;

void setup() {  
  pinMode(pin, OUTPUT); 
  pinMode(pin, HIGH);
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: " + WiFi.localIP());
}

  WiFiClient client;

void loop() {  
//  Serial.print("connecting to ");
//  Serial.println(host);
//  if (!client.connect(host, 8000)) {
//    Serial.println("connection failed");
//    return;
//  }

  light = analogRead(A0);
  
//  String thisString = String(light);
  data = "light=" + light;

  Serial.println(data);
//
  if (client.connect("145.28.124.107" , 8000)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST / HTTP/1.1");
    client.println("Host: 145.28.124.107:8000");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
    client.println();
    Serial.println("Data send");
//
//        while(client.available()) {
//          char c = client.read();
//          Serial.print(c);  
//        }
    }
//
//    if (client.connected()) { 
//        client.stop();    // DISCONNECT FROM THE SERVER
//    }

//  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" + 
//               "Connection: keep-alive\r\n\r\n");

  //delay(500); // wait for server to respond

  // read response
//  String section="header";
//  while(client.available()){
//    String line = client.readStringUntil('\r');
//    // Serial.print(line);
//    // we’ll parse the HTML body here
//    if (section=="header") { // headers..
//      Serial.print(".");
//      if (line=="\n") { // skips the empty space at the beginning 
//        section="json";
//      }
//    }
//    else if (section=="json") {  // print the good stuff
//      section="ignore";
//      String result = line.substring(1);
//
//      // Parse JSON
//      int size = result.length() + 1;
//      char json[size];
//      result.toCharArray(json, size);
//      StaticJsonBuffer<200> jsonBuffer;
//      JsonObject& json_parsed = jsonBuffer.parseObject(json);
//      if (!json_parsed.success())
//      {
//        Serial.println("parseObject() failed");
//        return;
//      }
//
//      // Make the decision to turn off or on the LED
//      if (strcmp(json_parsed["light"], "on") == 0) {
//        digitalWrite(pin, HIGH); 
//        Serial.println("LED ON");
//      }
//      else {
//        digitalWrite(pin, LOW);
//        Serial.println("led off");
//      }
//    }
//  }

    delay(15);
//  Serial.print("closing connection. ");
}
