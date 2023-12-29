#include <LiquidCrystal.h>
#define PI 3.1415926535897932384626433832795
// 4 components (Motor, IR sensor, LCD, encoder sensor)
// Motor A connections
int enA = 11;
int in1 = A1;
int in2 = A2;
// Motor B connections
int enB = 3;
int in3 = A3;
int in4 = A4;

// Sensors
const int LS = 13; //Left Sensor
const int RS = 12; //Right Sensor

// LCD
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Rotary encoder
int encoderLeft = 2;
int encoderRight = 1;
int initialLeft=0;
int initialRight=0;
int currentLeft;
int currentRight;
int degreeLeft=0;
int degreeRight=0;
float distanceL=0.0;
float distanceR=0.0;
float distanceS=0.0;
float distance=0.0;
//float initialTime=0;

void setup() {
  Serial.begin(9600);
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
    
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // Initialize Sensors
  pinMode (LS, INPUT);
  pinMode (RS, INPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  
  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Prepare to begin");
  delay(1000);
  lcd.clear();
  lcd.print("Moving in");
  lcd.setCursor(0,1);
  lcd.print("3");
  delay(1000);
  lcd.setCursor(1,1);
  lcd.print("2");
  delay(1000);
  lcd.setCursor(2,1);
  lcd.print("1");
  delay(1000);
  lcd.clear();
  lcd.print("Start!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Motion");
  lcd.setCursor(0,1);
  lcd.print("Measure distance");
  delay(500);

}

void loop() {
  // Clear previous message in lcd
  lcd.clear();

  // Move in straight line
  if (digitalRead(LS)==HIGH && digitalRead(RS)==HIGH){
    analogWrite(enA,65);
    analogWrite(enB,60);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    lcd.print("Moving Straight");

    // Encoder Left
    currentLeft = digitalRead(encoderLeft);

    if (initialLeft == 0 && currentLeft==1){
      degreeLeft+=18;
    }
    initialLeft = currentLeft;

    // Encoder Right
    currentRight = digitalRead(encoderRight);

    if (initialRight == 0 && currentRight==1){
      degreeRight+=18;
    }
    initialRight = currentRight;

    distanceS = float(((float(degreeLeft)/360.0*PI*3.2*2 )+(float(degreeRight)/360.0*PI*3.2*2)/2));
    distance += distanceS;
    lcd.setCursor(0,1);
    lcd.print("Distance:");
    lcd.setCursor(9,1);
    lcd.print(distance);
    distanceS = 0.0;
    degreeLeft = 0;
    degreeRight = 0;
  }
  // Turn Right
  if((digitalRead(LS)==HIGH) && (digitalRead(RS)==LOW)){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    lcd.print("Turning Right");
    
    // Turn Left
  if((digitalRead(LS)==LOW) && (digitalRead(RS)==HIGH)){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    lcd.print("Turning Left");

    // Encoder Left
    currentLeft = digitalRead(encoderLeft);

    if (initialLeft == 0 && currentLeft ==1){
      degreeLeft+=18;
    }
    initialLeft = currentLeft;

    //if (millis()-initialTime==1000){
    distanceR = float((float(degreeLeft)/360.0*PI*3.2*2));
    distance += distanceR;
    lcd.setCursor(0,1);
    lcd.print("Distance:");
    lcd.setCursor(9,1);
    lcd.print(distance);
    distanceR = 0.0;
    degreeLeft = 0;
    //initialTime=millis();
    //}
  }

  // Turn Left
  if((digitalRead(LS)==LOW) && (digitalRead(RS)==HIGH)){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    lcd.print("Turning Left");

    // Encoder Right
    currentRight = digitalRead(encoderRight);

    if (initialRight == 0 && currentRight==1){
      degreeRight+=18;
    }
    initialRight = currentRight;

    distanceL = float((float(degreeRight)/360.0*PI*3.2*2));
    distance += distanceL;
    lcd.setCursor(0,1);
    lcd.print("Distance:");
    lcd.setCursor(9,1);
    lcd.print(distance);
    distanceL = 0.0;
    degreeRight = 0;
  }

  //Stop 
  if((digitalRead(LS)==LOW) && (digitalRead(RS)==LOW)){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    lcd.print("Stop");

    // Print distance
    lcd.setCursor(0,1);
    lcd.print("Distance:");
    lcd.setCursor(9,1);
    lcd.print(distance);
    Serial.print("Encoder Left: ");
    Serial.println(distance);
  }

}
