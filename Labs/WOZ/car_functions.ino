//one wheel is composed of 32 slices
//16 black and 16 white.

void initialize() {  
  int vl = digitalRead(leftEncoder);

  //forward left  
  analogWrite(leftForward, 128);   
  digitalWrite(leftReverse, LOW);  

  while(digitalRead(leftEncoder) == vl);

  stopLeft();

  delay(100);

  int vr = digitalRead(rightEncoder);  

  //forward right
  analogWrite(rightForward, 128);   
  digitalWrite(rightReverse, LOW);  

  while(digitalRead(rightEncoder) == vr);

  stopRight();
}

void backward(int speed) {      

  //right backward
  digitalWrite(rightForward, LOW);   
  analogWrite(rightReverse, speed); 

  //left backward
  digitalWrite(leftForward, LOW);   
  analogWrite(leftReverse, speed);  
}

void forward(int speed) {

  //right forward
  digitalWrite(rightForward, speed);   
  analogWrite(rightReverse, LOW); 

  //left forward
  digitalWrite(leftForward, speed);   
  analogWrite(leftReverse, LOW);  
}

void right(int speed) {

  //right forward
  digitalWrite(rightForward, speed);   
  analogWrite(rightReverse, LOW); 

  //left backward
  digitalWrite(leftForward, LOW);   
  analogWrite(leftReverse, speed);  
}

void left(int speed) {

    //right backward
  digitalWrite(rightForward, LOW);   
  analogWrite(rightReverse, speed); 
  
  //left forward
  analogWrite(leftForward, speed);   
  digitalWrite(leftReverse, LOW);  

}

void stopLeft() {   
  digitalWrite(leftForward, LOW);   
  digitalWrite(leftReverse, LOW);   
}

void stopRight() {
  digitalWrite(rightForward, LOW);   
  digitalWrite(rightReverse, LOW);
}

void stop() {
  stopLeft();
  stopRight();
}

void hardStop() {
  digitalWrite(leftForward, HIGH);   
  digitalWrite(leftReverse, HIGH); 

  digitalWrite(rightForward, HIGH);   
  digitalWrite(rightReverse, HIGH); 
}






















