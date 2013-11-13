#define FORWARD 1
#define BACKWARD 0

//left motor
const int leftEnable = 13;
const int leftForward = 10;
const int leftReverse = 11;

//right motor
const int rightEnable = 12;
const int rightForward = 6;
const int rightReverse = 9;

//encoders
const int leftEncoder = A1;
const int rightEncoder = A4;

char instruction = 'O';

void setup() {

  Serial.begin(9600); 

  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(12, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

  //enable motors
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);  

  //initialize aligns the wheels
  initialize();

  delay(2000);
}

void loop() {

  if (Serial.available() > 0) {
    instruction = Serial.read();
  }

  switch(instruction) {
  case 'F': 
    digitalWrite(11, HIGH);
    forward(255);
    delay(100);
    break;

  case'R':  
    right(255);
        delay(100);
    break;

  case'L':
    left(255);
        delay(100);
    break;

  case'I':
    initialize();
    break;
    
    case'B':
    backward(255);
        delay(100);
    break;

  case'O':
    stop();
    break;

  default:
    stop();
    break;

  }
}






