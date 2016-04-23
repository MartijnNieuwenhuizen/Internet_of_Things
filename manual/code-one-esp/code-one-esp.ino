// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WiFi
char ssid[] = "routers_name"; // set the routers name here
char password[] = "routers_password"; // set the routers password here

char* host = "www.your_url.nl"; // set your own url here
String path = "/get-up-stand-up/led.json";
const int httpPort = 80;

WiFiClient client;

// init
int oneGreen = D1;
int oneRed = D2;
int twoGreen = D3;
int twoRed = D4;
int threeGreen = D5;
int threeRed = D6;

int buttonPin = D7; 
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

String data;
String buttonValue;

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

}

void loop() {

  postRequest();
  getRequest();
     
  delay(500);
  
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

// Code From http://blog.nyl.io/esp8266-led-arduino/
void getRequest() {
  // Log the connection
  Serial.print("connecting to ");
  Serial.println(host);

  // set WiFi Client
  WiFiClient client;

  // check connection
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return; 
  }
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
   "Host: " + host + "\r\n" + 
   "Connection: keep-alive\r\n\r\n");             
               
  delay(500);
  
  // read response
  String section="header";
  while(client.available()){
    
    String line = client.readStringUntil('\r');
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
      } else {
        Serial.println("json = ERROR??");
      }
    }
    
  }
}

void postRequest() {

      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        buttonValue = "true";
      } else {
        buttonValue = "false";
      }
      data = "sitting="+buttonValue;

    if(client.connect(host, httpPort)) {
      
      // Code From Casper Boutens
      // make the POST headers and add the data string to it
      client.println("POST /get-up-stand-up/index.php HTTP/1.1");
      client.println("Host: www.your_url.nl:80"); // FILL IN YOU URL!!!!!!!!!!!
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.println("Connection: close");
      client.print("Content-Length: ");
      client.println(data.length());
      client.println();
      client.print(data);
      client.println();
      Serial.println(data);
      Serial.println("Data send");
 
//    Uncommend this code to dubug your POST Request
//    while(client.available()){
//      String line = client.readStringUntil('\r');
//      Serial.print(line);
//    }

   } else {
      Serial.println("Something went wrong");
   }
    
}
