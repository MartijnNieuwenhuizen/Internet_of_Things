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
  Serial1.write(soundValue);
  Serial.write(soundValue);
  
  Serial.println(soundValue);

  delay(500);
      
}

