// include the library code:
#include <LiquidCrystal.h>
#include <math.h>

// lcd init
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int contrastPin = 6;

// pressure init
int maxPounds = 25;
int pressurePin = A0;
int currentDepth = 0;

// temp init
int thermPin = A1;
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
  // read the sensor and calculate the footage
  int reading = analogRead(pressurePin);
  int pounds = maxPounds * reading / 1024;
  int feet = pounds * 33 / 14.7;
  
  // normalize to be more concise
  if(feet < 6) { feet = 0; }
  // if feet < 5 then feet = 0
  currentDepth = feet;
  
  // caclulate alarm
  depthAlarm = (currentDepth > 30) ? true : false;
}

void updateTemp() {
  int Vo = analogRead(thermPin);; 
  float R = 9870.0; //9870.0; // Fixed resistance in the voltage divider
  float logRt, Rt, T;
  float c1 = 1.009249522e-03, 
        c2 = 2.378405444e-04, 
        c3 = 2.019202697e-07;
  Rt = R * (1024.0 / (float)Vo - 1.0);
  logRt = log(Rt);
  T = (1.0 / (c1 + c2 * logRt + c3 * logRt * logRt * logRt)) - 273.15;
  T = (T * 9.0) / 5.0 + 32.0;
  currentTemp = (int)T;
}

void updateAlarm() {
  if(depthAlarm) {
    analogWrite(beepPin, 20);
  } else {
    analogWrite(beepPin, 0); 
  }
}


