//one wheel is composed of 32 slices
//16 black and 16 white.

int l = 2;
int r = 2;

int readLeft(int l) {
  int rl = analogRead(leftEncoder);
  if (rl < bwVal && l == 1) {
    l = 0;
  } else if (rl < bwVal && l == 2) {
    l = 0;
  }
  if (rl >= bwVal && l == 0){
    l = 1;
  } else if (rl >= bwVal && l == 2) {
    l = 1;
  }
  return l;
}

int readRight(int r) {
  int rr = analogRead(rightEncoder);
  if (rr < bwVal && r == 1) {
    r = 0;
  } else if (rr < bwVal && r == 2) {
    r = 0;
  }
  if (rr >= bwVal && r == 0) {
    r = 1;
  } else if (rr >= bwVal && r == 2) {
    r = 1;
  }
  return r;
}

//rotate wheels until the next sign
void initialize(int d) {
  
  //int vl = digitalRead(leftEncoder);
  int vl;
  vl = readLeft(l);

  //forward left  
  if (d == 0) {
    analogWrite(leftForward, 88);
    digitalWrite(leftReverse, LOW);
  } else if (d == 1) {
    analogWrite(leftReverse, 88);
    digitalWrite(leftForward, LOW);
  }

  while (readLeft(vl) == 0);

  stopLeft();

  delay(100);
  
  int vr;
  vr = readRight(r);

  //forward right
  if (d == 0) {
    analogWrite(rightForward, 88);
    digitalWrite(rightReverse, LOW);
  } else if (d == 1) {
    analogWrite(rightReverse, 88);
    digitalWrite(rightForward, LOW);
  }

  while (readRight(vr) == 0);
  stopRight();
}

/* MOTION FUNCTIONS */

//not used
void backward(int speed, int steps) {
  int vL = 0; 
  int pvL = 0;
  int vR = 0;
  int pvR = 0;

  int counterL = 0;
  int counterR = 0;
  
  pvL = readLeft(l);
  pvR = readRight(r);

  //right backward
  digitalWrite(rightForward, LOW);
  analogWrite(rightReverse, speed);

  //left backward
  digitalWrite(leftForward, LOW);
  analogWrite(leftReverse, speed);


  while (counterL <= steps || counterR <= steps) {
    if (counterL <= steps) {
      vL = readLeft(pvL);
      if (vL != pvL) counterL++;
      pvL = vL;
    }
    if (counterR <= steps) {
      vR = readRight(pvR);
      if (vR != pvR) counterR++;
      pvR = vR;
    }

    Serial.print("R L: ");
    Serial.println(counterL);
    Serial.println(vL);
    Serial.print("R R: ");
    Serial.println(counterR);
    Serial.println(vR);
    
  }

  stop();
}

void forward(int speed, int steps) {
  int vL = 0; 
  int pvL = 0;
  int vR = 0;
  int pvR = 0;

  int counterL = 0;
  int counterR = 0;
  
  pvL = readLeft(l);
  pvR = readRight(r);

  //right forward
  analogWrite(rightReverse, LOW);
  digitalWrite(rightForward, speed);
  
  //left forward
  analogWrite(leftReverse, LOW);
  digitalWrite(leftForward, speed);
  

  while (counterL <= steps || counterR <= steps) {
    if (counterL <= steps) {
      vL = readLeft(pvL);
      if (vL != pvL) {
        counterL++;
        pvL = vL;
      }
    }
    if (counterR <= steps) {
      vR = readRight(pvR);
      if (vR != pvR) {
        counterR++;
        pvR = vR;
      }
    }
    
    Serial.print("F L: ");
    Serial.println(counterL);
    Serial.println(vL);
    Serial.print("F R: ");
    Serial.println(counterR);
    Serial.println(vR);
   
  }

  stop();
}

void left(int speed, int steps) {
  int vL = 0; 
  int pvL = 0;
  int vR = 0;
  int pvR = 0;

  int counterL = 0;
  int counterR = 0;

  pvL = readLeft(l);
  pvR = readRight(r);

  //right forward
  analogWrite(rightReverse, LOW);
  digitalWrite(rightForward, speed);
  
  //left backward
  digitalWrite(leftForward, LOW);
  analogWrite(leftReverse, speed);

  //count rotation
  while (counterL <= steps && counterR <= steps) {
    if (counterL <= steps) {
      vL = readLeft(pvL);
      if (vL != pvL) {
        counterL++;
        pvL = vL;
      }
    }
    if (counterR <= steps) {
      vR = readRight(pvR);
      if (vR != pvR) {
        counterR++;
        pvR = vR;
      }
    }

    Serial.print("L L: ");
    Serial.println(counterL);
    Serial.println(vL);
    Serial.print("L R: ");
    Serial.println(counterR);
    Serial.println(vR);
    
  }

  stop();
}

void right(int speed, int steps) {
  int vL = 0; 
  int pvL = 0;
  int vR = 0;
  int pvR = 0;

  int counterL = 0;
  int counterR = 0;

  pvL = readLeft(l);
  pvR = readRight(r);

  //right reverse
  digitalWrite(rightForward, LOW);
  analogWrite(rightReverse, speed);

  //left forward
  digitalWrite(leftReverse, LOW);
  analogWrite(leftForward, speed);

  //count rotation
  while (counterL <= steps && counterR <= steps) {
    if (counterL <= steps) {
      vL = readLeft(pvL);
      if (vL != pvL) {
        counterL++;
        pvL = vL;
      }
    }
    if (counterR <= steps) {
      vR = readRight(pvR);
      if (vR != pvR) {
        counterR++;
        pvR = vR;
      }
    }

    Serial.print("R L: ");
    Serial.println(counterL);
    Serial.println(vL);
    Serial.print("R R: ");
    Serial.println(counterR);
    Serial.println(vR);
  }

  stop();
}

/* STOP FUNCTIONS */
void stopLeft() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, LOW);
}

void stopRight() {
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, LOW);
}

void stop() {
/*
  stopLeft();
  stopRight();
*/  
  digitalWrite(leftEnable, LOW);
  digitalWrite(rightEnable, LOW);
  
  digitalWrite(rightForward, LOW);
  digitalWrite(leftForward, LOW);
  digitalWrite(rightReverse, LOW);
  digitalWrite(leftReverse, LOW);
  
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
  
  Serial.println('S');
}

void hardStop() {
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftReverse, HIGH);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightReverse, HIGH);
}
