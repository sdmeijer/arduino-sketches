void route(int i) {  

  int led = i+22;  

  //forward = 326
  if (vals[i] < 400 && vals[i] > 280) {

    Serial1.print('F');
    Serial.println('F');
    digitalWrite(led,LOW);
    delay(1500);

  }

  //leftval = 511
  if (vals[i] < 600 && vals[i] > 450) {
    Serial1.print('L');
    Serial.println('L');
    digitalWrite(led,LOW);
    delay(1000);
  }


  //rightVal = 183;
  if (vals[i] < 250 && vals[i] > 100) {
    Serial1.print('R');
    Serial.println('R');
    digitalWrite(led,LOW);
    delay(1000);
  }

  //function = 931
  if (vals[i] > 850 && vals[i] < 990) {
    for ( int i = 12; i < 16; i++) {      
      if (vals[i] < 1023) {
        route(i);
      }
      else {        
        break;
      }
    }
    
    for (int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        digitalWrite(i+22,HIGH);
      }
    }
    
    delay(500);
    
   
    
  }

} 







