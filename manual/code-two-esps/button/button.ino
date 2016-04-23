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
int buttonPin = D7; 
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

String data;
String buttonValue;

void setup() {

  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);

}

void loop() {

  postRequest();
     
  delay(500);
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
