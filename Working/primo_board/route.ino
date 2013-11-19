void route(int i) {  

  int led = i+22;  

  //forward = 326 = 4.7K
  if (vals[i] < 500 && vals[i] > 325) {

    Serial1.print('F');
    Serial.println('F');
    digitalWrite(led,LOW);
    delay(1500);

  }

  //leftval = 511 = 10 K
  if (vals[i] < 700 && vals[i] > 550) {
    Serial1.print('L');
    Serial.println('L');
    digitalWrite(led,LOW);
    delay(1000);
  }


  //rightVal = 183 = 2.2
  if (vals[i] < 319 && vals[i] > 180) {
    Serial1.print('R');
    Serial.println('R');
    digitalWrite(led,LOW);
    delay(1000);
  }

  //function = 931 = 100K
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







