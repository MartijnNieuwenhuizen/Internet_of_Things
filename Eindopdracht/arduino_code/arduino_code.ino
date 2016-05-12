int soundInput = A2;

void setup() {

  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
    
}

void loop() {

  int soundValue = analogRead(soundInput);
  int sendValue;

  if ( soundValue < 50 ) {
    sendValue = 1;
  } else if ( soundValue > 50 && soundValue < 100 ) {
    sendValue = 2;
  } else if ( soundValue > 100 && soundValue < 150 ) {
    sendValue = 3;
  } else if ( soundValue > 150 && soundValue < 200 ) {
    sendValue = 4;
  } else if ( soundValue > 200 && soundValue < 250 ) {
    sendValue = 5;
  } else if ( soundValue > 250 && soundValue < 300) {
    sendValue = 6;
  } else if ( soundValue > 300 && soundValue < 350) {
    sendValue = 7;
  } else if ( soundValue > 350 && soundValue < 400 ) {
    sendValue = 8;
  } else if ( soundValue > 400 && soundValue < 450 ) {
    sendValue = 9;
  } else if ( soundValue > 450 ) {
    sendValue = 10;
  }

  while (!Serial) {
    Serial1.write(300);
  }
  Serial.println(soundValue);

  delay(500);
      
}

