void route(int i) {

  int led = i;

  //forward
  if (vals[i] > (forwardVal - gap) && vals[i] < (forwardVal + gap)) {
    Serial.println('F');
    transmitLED(led, 0);
    //delay(2000);
  }

  //left
  if (vals[i] > (leftVal - gap) && vals[i] < (leftVal + gap)) {
    Serial.println('L');
    transmitLED(led, 0);
    //delay(1500);
  }


  //right
  if (vals[i] > (rightVal - gap) && vals[i] < (rightVal + gap)) {
    Serial.println('R');
    transmitLED(led, 0);
    //delay(1500);
  }

  //function
  if (vals[i] > (functionVal - gap) && vals[i] < (functionVal + gap)) {
    
    transmitLED(led, 0);
    
    //route function line
    for ( int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        //INFINITE LOOP FOR THE WIN!!
        route(i);
      } else {
        break;
      }
    }
    
    //turn function leds back on
    for (int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        transmitLED(i, 1);
      }
    }
    
    delay(500);
    
  }

}







