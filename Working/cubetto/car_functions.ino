//one wheel is composed of 32 slices
//16 black and 16 white.
//360° = 16

void initialize() {  
  int vl = digitalRead(leftEncoder);

  //forward left  
  analogWrite(leftForward, 88);   
  digitalWrite(leftReverse, LOW);  

  while(digitalRead(leftEncoder) == vl);

  stopLeft();

  delay(100);

  int vr = digitalRead(rightEncoder);  

  //forward right
  analogWrite(rightForward, 88);   
  digitalWrite(rightReverse, LOW);  

  while(digitalRead(rightEncoder) == vr);

  stopRight();
}

void backward(int speed, int steps) {      
  int vL, pvL = 0;
  int vR, pvR = 0;

  int counterL, counterR = 0;

  //right backward
  digitalWrite(rightForward, LOW);   
  analogWrite(rightReverse, speed); 

  //left backward
  digitalWrite(leftForward, LOW);   
  analogWrite(leftReverse, speed);  


  while(counterL <= steps && counterR <= steps) {
    if(counterL <= steps) {
      vL = digitalRead(leftEncoder);
      if(vL != pvL) counterL++;
      pvL = vL;     
    } 
    if (counterR <= steps) {
      vR = digitalRead(rightEncoder);
      if(vR != pvR) counterR++;
      pvR = vR;     
    }
  }

  stop();
}

void forward(int speed, int steps) {
  int vL, pvL = 0;
  int vR, pvR = 0;

  int counterL, counterR = 0;

  //right forward
  digitalWrite(rightForward, speed);   
  analogWrite(rightReverse, LOW); 

  //left forward
  digitalWrite(leftForward, speed);   
  analogWrite(leftReverse, LOW);  


  while(counterL <= steps && counterR <= steps) {
    if(counterL <= steps) {
      vL = digitalRead(leftEncoder);
      if(vL != pvL) counterL++;
      pvL = vL;     
    } 
    if (counterR <= steps) {
      vR = digitalRead(rightEncoder);
      if(vR != pvR) counterR++;
      pvR = vR;     
    }
  }

  stop();
}

void right(int speed, int steps) {
  int vL, pvL = 0;
  int vR, pvR = 0;

  int counterL, counterR = 0;

  //right forward
  digitalWrite(rightForward, speed);   
  analogWrite(rightReverse, LOW); 

  //left backward
  digitalWrite(leftForward, LOW);   
  analogWrite(leftReverse, speed);  


  while(counterL <= steps && counterR <= steps) {
    if(counterL <= steps) {
      vL = digitalRead(leftEncoder);
      if(vL != pvL) counterL++;
      pvL = vL;     
    } 
    if (counterR <= steps) {
      vR = digitalRead(rightEncoder);
      if(vR != pvR) counterR++;
      pvR = vR;     
    }
  }

  stop();
}

void left(int speed, int steps) {
  int vL, pvL = 0;
  int vR, pvR = 0;

  int counterL = 0, counterR = 0;

  pvL = digitalRead(leftEncoder);
  pvR = digitalRead(rightEncoder);

  while(counterL <= steps || counterR <= steps) {

    if(counterL <= steps) {

      vL = digitalRead(leftEncoder);

      //left 
      if (counterL < (steps - 2)) {
        //fullspeed
        analogWrite(leftForward, speed);   
        digitalWrite(leftReverse, LOW);  
      } 
      else {
        //slowdown
        analogWrite(leftForward, 80);   
        digitalWrite(leftReverse, LOW);  
      }

      if(vL != pvL){ 
        counterL++;
        pvL = vL;   
      }
    } 

    if (counterR <= steps) {
      vR = digitalRead(rightEncoder);

      if (counterR < (steps - 2)) {
        //slowdown
        digitalWrite(rightForward, LOW);   
        analogWrite(rightReverse, speed); 
      } 
      else {
        //fullspeed
        digitalWrite(rightForward, LOW);   
        analogWrite(rightReverse, 80); 
      }     

      if(vR != pvR) {
        counterR++;
        pvR = vR;     
      }
    }
  }

  stop();
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





















