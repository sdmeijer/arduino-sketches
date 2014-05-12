/*
http://primo.io

This sketch is part of the Primo Prototype Documentation.
http://docs.primo.io

Tested on the Arduino UNO.
Load this into Cubetto, the little cube robot.
*/

#define FORWARD 1
#define BACKWARD 0

//serial protocol
#define STOP 'O'
#define LEFT 'L'
#define RIGHT 'R'
#define FORWARD 'F'
#define BACKWARD 'B' 
#define INIT 'I'

//left motor
const int leftEnable = 8;
const int leftForward = 10;
const int leftReverse = 11;

//right motor
const int rightEnable = 12;
const int rightForward = 5;
const int rightReverse = 9;

//encoders
const int leftEncoder = 18;
const int rightEncoder = 15;

//CNY70
const int bwVal = 150;

char instruction = 'O';

void setup() {

  Serial.begin(9600);

  //initialize left
  pinMode(leftEnable, OUTPUT);
  pinMode(leftReverse, OUTPUT);
  pinMode(leftForward, OUTPUT);

  //initialize right
  pinMode(rightEnable, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightReverse, OUTPUT);

  //enable motors
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);

  //initialize aligns the wheels
  initialize(0);

  delay(2000);
}

void loop() {

  //read from the xbee
  if (Serial.available() > 0) {
    instruction = Serial.read();
  }

  if (instruction == 'F') {
    //initialize(1);
      forward(128, 16);
  } else
  if (instruction == 'B') {
    //initialize(1);
      backward(128, 16);
  } else
  if (instruction == 'R') {
    //initialize(1);
      right(130, 7);
  } else
  if (instruction == 'L') {
    //initialize(1);
      left(150, 5);
  } else
  if (instruction == 'I') {
      initialize(0);
  } //else {
      //stop();
  //}    

  instruction = 'O';
}






