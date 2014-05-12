/*
http://primo.io

This sketch is part of the Primo Prototype Documentation.
http://docs.primo.io

Tested on the Arduino Mega 2560.
Load this into the Interface Board.

ANALOG VALUES FOR DIFFERENT RESISTORS:
10KΩ = 500
100KΩ = 920
4.7KΩ = 319
220Ω = 20
*/

#include <Wire.h>

//#define DEBUG

//4.7kΩ
int forwardVal = 326;
//10kΩ
int leftVal = 931; //511;
//220Ω
int rightVal = 22;
//100kΩ
int functionVal = 511; //931;
//range 
int gap = 50;

int buttonPin = 5;
int butVal, pButVal;

boolean isExecuting = false;

//int vals[16];

const int selectPin1 = 10;
const int selectPin2 = 11;

const int analogPinX1 = A2;
const int analogPinY1 = A0;
const int analogPinX2 = A3;
const int analogPinY2 = A1;

char instruction = 'O';

byte primo[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int vals[16] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
int primoP[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int funcBlock = 0;

int setBytes(int byte1, int byte2)
{
  digitalWrite(selectPin1, byte1);
  digitalWrite(selectPin2, byte2);
}

void transmitLED(int pin, int val) { //transmit LED-states with I2C
#ifdef DEBUG
  Serial.print(pin);
  Serial.print(": ");
  Serial.println(val);    
#endif

  Wire.beginTransmission(2);
  Wire.write(pin);
  Wire.write(val);  
  Wire.endTransmission();
}

void readBlock() {
  for (int i=0; i<4; i++) {
   if (i == 0) {
    setBytes(0,0);
  }
  if (i == 1) {
    setBytes(0,2);
  }
  if (i == 2) {
    setBytes(1,0);
  }
  if (i == 3) {
    setBytes(1,1);
  }
  
  int k = i * 4;
  
  vals[k] = analogRead(analogPinX1);
  vals[k+1] = analogRead(analogPinY1);
  vals[k+2] = analogRead(analogPinX2);
  vals[k+3] = analogRead(analogPinY2);
  }
}

void checkFuncBlock() {
  funcBlock = 0;
  for (int i = 0; i < 12; i++) {
    if (vals[i] > (functionVal - gap) && vals[i] < (functionVal + gap)) {
      funcBlock = 1;
    }
  }
#ifdef DEBUG
  Serial.print("funcBlock: ");
  Serial.println(funcBlock);
#endif
}

void blinkLEDs() {
    for (int i = 0; i < 16; i++) {
    transmitLED(i, 0);
  }
  for (int i = 0; i < 16; i++) {
    transmitLED(i, 1);
    delay(100);
  }
  for (int i = 0; i < 16; i++) {
    transmitLED(i, 0);
    delay(100);
  }
  for (int i = 0; i < 3; i++) {
    for (int i = 0; i < 16; i++) {
      transmitLED(i, 1);
    }
    delay(100);
    for (int i = 0; i < 16; i++) {
      transmitLED(i, 0);
    }
    delay(100);
  } 
}

void setup() {  
  pinMode(buttonPin, INPUT);

  Wire.begin();
  Serial.begin(9600);
  pinMode(selectPin1, OUTPUT);
  pinMode(selectPin2, OUTPUT);
  
  blinkLEDs();
}

void waitCubetto() {
  unsigned long time = millis();
  
  while (instruction != 'S') {
    if (Serial.available() > 0) {
      instruction = Serial.read();
    }
    if ((millis() - time) > 2500) { // assume Cubetto is finished
      instruction = 'S';
    }
  }
}

void loop() {
  
  readBlock();        //read the values of all blocks
  checkFuncBlock();   //check if a function block is inserted
  
  for (int m = 0; m < 16; m++) {
    if (vals[m] < 1010 && m < 12) {
      primo[m] = 1;
    } else if (vals[m] < 1010 && m >= 12 && funcBlock == 1) {  //only turn on led in function area if a function block is inserted
      primo[m] = 1;
    } else {
      primo[m] = 0;
      if (m < 12) {
        for (int q = m+1; q < 12; q++) {  //check if all blocks are inserted in sequence, otherwise blink leds for missing blocks
          if (vals[q] < 1010 && vals[m] > 1010) {
            primo[m] = 2;
          }
        }
      }
      if (m >= 12 && funcBlock == 1) { //only blink led in function area if a function block is inserted
        for (int q = m+1; q < 16; q++) {
          if (vals[q] < 1010 && vals[m] > 1010) {
            primo[m] = 2;
          }
        }
      }
    }
#ifdef DEBUG
      Serial.print("test ");
      Serial.print(m);
      Serial.print(": ");
      Serial.print(primo[m]);
      Serial.print(" ");
      Serial.println(primoP[m]);
#endif

    if (primo[m] != primoP[m]) { //only transmit ledstate if it has to be changed
      primoP[m] = primo[m];
      transmitLED(m, primo[m]); 
    }
  }

  butVal = digitalRead(buttonPin); //check if button is pressed

#ifdef DEBUG
  Serial.println(butVal);
#endif

  //if button press & not executing
  if(butVal == 1 && isExecuting == false) {
    isExecuting = true;
  }

  if(isExecuting) {
    readBlock();

    for (int i = 0; i < 12; i++) {
      if (vals[i] < 1010) {
#ifdef DEBUG
        Serial.print("stap ");
        Serial.print(": ");
        Serial.println(vals[i]);
#endif
        instruction = 'O';
        route(i);
      }
      else {
        break;
      }
      waitCubetto();
    }
    blinkLEDs();
    
    //reset all values
    for (int i = 0; i < 16; i++) {
      primo[i] = 0;
      primoP[i] = 0;
      vals[i] = 0;
    }
    funcBlock = 0;
  }  

  isExecuting = false;
  delay(30);
}






