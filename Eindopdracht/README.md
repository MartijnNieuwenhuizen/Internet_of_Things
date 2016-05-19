# How to measure if a drug deal occurred?

## What is there to measure?
Well, a typical drug deal has a known rhythm. A dealer stands on a spot, a person drives/walks up, pauses and drive/walks off. So if we measure a person coming up, standing still and driving/walking off, we could say that a possible drug deal occurred.

So why do we want to know this? We had an assignment of a community to measure if a drug deal occurs. We think it's more useful to measure how popular some spots are and then react, instead of a direct reaction by the police. 

## Materials
* An ESP8266 (available at stores like the [Hackerstore](http://www.hackerstore.nl/))
* A custom Arduino with a sound sensor OR an extra Arduino with an external sound sensor (connect this sensor to the A2 port).
* A breadboard
* A few wires
* 1 resistors (brown | black | black | red | brown) 
* 2 USB cables

## Setup
To measure this rhythm, we'll need to measure upcoming lights, sound, and movement. For this, we used a sound-sensitivity sensor, an LRD, and a Pir sensor. This is how the setup collects and sends the data.

![Global Setup](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/final-assignment-global-setup.jpg "Global Setup")

The Setup for the board is done like this.

![connect the board](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/final-assignment-setup.jpg "connect the board")

## Parts
![Parts](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/final-assignment-parts.jpg "Parts")

### Sound Sensor
The sound sensor measures an upcoming vehicle. We used the sensor on a custom Arduino Leonardo board, made by [smartsensors.com???](www.smart.nl). This means the Arduino needs to send the data to the NodeMCU thru the [serial connection](#serial-connection).

### LDR Sensor
The LDR(light-dependent resistor) measures upcoming lights of a scooter or a car. This is Analog data, so we can see the light sensitivity increasing or decreasing.

### Pir Sensor
The Pir sensor (Passive infrared sensor), measures if there's movement or not. This means we can see if there's a person walking/riding by, and how much movement there is. 

### ESP (NodeMCU)
The ESP collects all the data and POST it to the server.


## Connect your Arduino Leonardo to a NodeMCU (Serial Communication)
The NodeMCU has only one analog port, and for this setup, we'll need two. This means we need to connect an extra Arduino to the NodeMCU. But how do you send data from an Arduino to a NodeMCU? Well, that's done thru the serial communication. 

First, connect your two devices via the tx and Rx port like this

![Serial Communication](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/final-assignment-serial-communication.jpg "Serial Communication")

Now you can send your data thru the serial connection. Here's the setup we are using.

**Arduino Code (send the data)**

```c
int soundInput = A2;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
    
}

void loop() {

  int soundValue = analogRead(soundInput);
  // use Serial1 for the Leonardo. 
  Serial1.write(soundValue); // send the data thrue the serial communication

  delay(500);
      
}
```

**NodeMCU Code (reciefe the data)**

```c
int soundValue;

void loop() {
    soundValue = Serial.read(); // read the data thrue the serial communication
}
```

## Send data to the Server
After receiving this data, and the data from the other sensors, this needs to be sent to the server. This is done by the *ESP8266HTTPClient* library.

This is the function used in the code in this project

```c
String host = "http:your_own_url.com";
const int httpPort = 80; // this is the standard value
HTTPClient http; // open your http client

void postRequest(int valueOne, int valueTwo, int valueThree) { // use how many you would like

  String sendData = String(valueOne) + "/" + String(valueTwo) + "/" + String(valueThree); // this is how we need to send it to our own server, use your own format!
  
  http.begin(host + sendData); // send your collected data to your host

  Serial.println("In The POST");
  Serial.println(sendData); // print the data that's send
  
  
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // add a header, nessesary for a POST or GET request

  // check if the POST worked
  int httpCode = http.POST(sendData); 
  if (httpCode > 0) {
    Serial.println("POST request gelukt");
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.println(http.errorToString(httpCode).c_str());
  }

  http.end();
    
}
```

For the Server code, look at the [project3server reposetory](https://github.com/LeanderVanBaekel/project3server).

## Tips/Questions
For tips or Questions, you can add create a GitHub issue. If you can improve this manual/code, please make a Pull Request. Thx and good luck.