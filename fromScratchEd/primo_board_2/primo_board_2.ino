#include <Wire.h>

byte primo[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte primoTemp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ledState = 0;
int q = 0;

void blink() {
  for (int p = 0; p < 16; p++) {
    if (primo[p] == 2) {
      if (ledState == 1) {
        digitalWrite(p+2, LOW);
      } else if (ledState == 0) {
        digitalWrite(p+2, HIGH);
      }
    }
  }
  if (ledState == 0) {
    ledState = 1;
  } else {
    ledState = 0;
  }
}
  

void setup() {
  Wire.begin(2);
  Wire.onReceive(receiveEvent);
  
  for (int i=2; i<18; i++) {
    pinMode(i, OUTPUT);
  }
}

void receiveEvent(int howMany) {
  int p=0;
  while(1 < Wire.available()) {
    p = Wire.read();
    primoTemp[p]=Wire.read();
    
    //START correction for wrong wiring
    switch (p) {
      case 0:
        q = 3;
        break;
      case 1:
        q = 2;
        break;
      case 2:
        q = 1;
        break;
      case 3:
        q = 0;
        break;
      case 4:
        q = 7;
        break;
      case 5:
        q = 6;
        break;
      case 6:
        q = 5;
        break;
      case 7:
        q = 4;
        break;
      case 8:
        q = 11;
        break;
      case 9:
        q = 10;
        break;
      case 10:
        q = 9;
        break;
      case 11:
        q = 8;
        break;
      case 12:
        q = 15;
        break;
      case 13:
        q = 14;
        break;
      case 14:
        q = 13;
        break;
      case 15:
        q = 12;
        break;
    }
    primo[q] = primoTemp[p];
    //END correction for wrong wiring
      
    if (primo[q] < 2) {
      digitalWrite(q+2, primo[q]);
    }
  }
}

void loop() {
  blink(); 
  delay(100);
}
