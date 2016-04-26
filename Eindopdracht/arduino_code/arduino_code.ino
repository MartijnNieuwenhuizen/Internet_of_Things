int soundInput = A2;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }
    
}

void loop() {

  int soundValue = analogRead(soundInput);
  Serial1.write(soundValue);
  Serial.write(soundValue);
  
  Serial.println(soundValue);

  delay(500);
      
}





//void loop() {
////    while (Serial1.available()) {
////        Serial.write(Serial1.read());
////        Serial.println("1 avalible");
////    }
////    while (Serial.available()) {
////        Serial1.write(Serial.read());
////        Serial.println("0 avalible");
////    }
//
//  ldrValue = analogRead(ldrSensor);
//  Serial.println(ldrValue);
//
//  Serial.write(ldrValue);
////  int bytesSent = Serial.write("HELLOOOO");
////  Serial.println(bytesSent);
//  
//delay(500);
//      
//}
