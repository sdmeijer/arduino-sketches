//fixed resistor: 10K
//10K = 500
//100K = 920
//4.7K = 319
//2.2 = 178
//220 = 20

int forwardVal = 326;
int leftVal = 511;
int rightVal = 183;
int funcVal = 931;

int gap = 100;

int buttonPin = 46;
int butVal, pButVal;

boolean execute = false;

int vals[16];

void setup() {  
  //led init
  for (int i = 22; i < 38; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {

  for(int i = 0; i < 16; i++) {
    int led = i+22;

    //fix this
    if (analogRead(i) < 1010) {
      digitalWrite(led, HIGH);
    } 
    else {
      digitalWrite(led, LOW);
    }    
  }

  butVal = digitalRead(buttonPin);

  if(butVal == HIGH && pButVal == LOW && execute == false) {
    execute = true;
  }

  if(execute) {
    readPins();

    for ( int i = 0; i < 12; i++) {
      if (vals[i] < 1010) {
        route(i);
      }
      else {
        break;
      }
    }    
  }  
  
  execute = false;
  pButVal = butVal;

  //Serial.println(analogRead(0));
  delay(30);
}






