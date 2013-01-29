
// include the library code:
#include <LiquidCrystal.h>
#include <math.h>
#include <Pressure.h>

// lcd init
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int contrastPin = 6;

// pressure init
Pressure pressure(A0, 25);
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


