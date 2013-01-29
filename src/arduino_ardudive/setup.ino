
void setup() {
  // lcd columns and rows
  lcd.begin(16, 2);
  
  // initialize serial port
  Serial.begin(9600);
  
  // set the contrast information
  pinMode(contrastPin, OUTPUT);
  pinMode(beepPin, OUTPUT);
}
