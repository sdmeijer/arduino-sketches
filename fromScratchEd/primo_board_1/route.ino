void route(int i) {

  int led = i;

  //forward
  if (vals[i] > (forwardVal - gap) && vals[i] < (forwardVal + gap)) {
    delay(250);
    transmitLED(led, 0);
    Serial.println('F');
  }

  //left
  if (vals[i] > (leftVal - gap) && vals[i] < (leftVal + gap)) {
    delay(250);
    transmitLED(led, 0);
    Serial.println('L');
  }

  //right
  if (vals[i] > (rightVal - gap) && vals[i] < (rightVal + gap)) {
    delay(250);
    transmitLED(led, 0);
    Serial.println('R');
  }

  //function
  if (vals[i] > (functionVal - gap) && vals[i] < (functionVal + gap)) {
    
    transmitLED(led, 0);
    
    //route function line
    for ( int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        instruction = 'O';
        route(i);
      } else {
        break;
      }
      waitCubetto();
    }
    
    //turn function leds back on
    for (int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        transmitLED(i, 1);
      }
    }
    instruction = 'S';
  }

}







