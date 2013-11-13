void leftWheel(int direction, int speed, int steps) {

  int vl, pvl;
  int counter = 0;

  if(direction == FORWARD) {
    analogWrite(leftForward, speed);   
    digitalWrite(leftReverse, LOW);  
  } 
  else {
    digitalWrite(leftForward, LOW);   
    analogWrite(leftReverse, speed);   
  }  

  while(counter <= steps) {
    vl = digitalRead(leftEncoder);
    if(vl != pvl) counter++;
    pvl = vl;     
  }

  stopLeft();
}

void rightWheel(int direction, int speed, int steps) {

  int vl, pvl;
  int counter = 0;

  if(direction == FORWARD) {
    analogWrite(rightForward, speed);   
    digitalWrite(rightReverse, LOW);  
  } 
  else {
    digitalWrite(rightForward, LOW);   
    analogWrite(rightReverse, speed);   
  }  

  while(counter <= steps) {
    vl = digitalRead(rightEncoder);
    if(vl != pvl) counter++;
    pvl = vl;     
  }

  stopRight();
}

