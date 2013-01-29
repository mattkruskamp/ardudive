#include <Thermistor.h>
#include <LiquidCrystal.h>
#include <Pressure.h>

// lcd init
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int contrastPin = 6;

// pressure init
Pressure pressure(A0, 25);
int currentDepth = 0;

// temp init
Thermistor thermistor(A1, 9870.0, 1.009249522e-03, 
  2.378405444e-04, 2.019202697e-07);
int currentTemp = 0;

// sound init
int beepPin = 9;

// app init
boolean depthAlarm = false;
int displayMode = 0;

void loop() { 
  update(); 
  draw();
  // print the number of seconds since reset:
  //lcd.print("time: " + millis()/1000);
}

void update() {
  updateTemp();
  updateDepth();
  updateAlarm();
  delay(100);
}

void setup() {
  // lcd columns and rows
  lcd.begin(16, 2);
  
  // initialize serial port
  Serial.begin(9600);
  
  // set the contrast information
  pinMode(contrastPin, OUTPUT);
  pinMode(beepPin, OUTPUT);
}

void draw() {
  // set the lcd contrast
  analogWrite(contrastPin, 50);
  if(displayMode == 0) {
     lcd.setCursor(0, 0);
     lcd.print("Depth: ");
     lcd.print(currentDepth);
     lcd.print("  ");
     
     lcd.setCursor(0, 1);
     lcd.print("Temp: ");
     lcd.print(currentTemp);
     lcd.print("F  ");
  }
}

void updateDepth()
{
  currentDepth = pressure.getDepth();
  // caclulate alarm
  depthAlarm = (currentDepth > 30) ? true : false;
}

void updateTemp() {
  currentTemp = thermistor.getTemperature();
}

void updateAlarm() {
  if(depthAlarm) {
    analogWrite(beepPin, 20);
  } else {
    analogWrite(beepPin, 0); 
  }
}


