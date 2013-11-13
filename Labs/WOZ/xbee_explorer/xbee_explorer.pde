import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port
char instruction;

void setup() 
{
  size(200, 200);
  
  println(Serial.list());

  String portName = Serial.list()[4];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(255);    
}

void keyPressed() {
  if (keyCode == UP) {
    instruction = 'F';
  }
  
  if (keyCode == RIGHT) {
    instruction = 'L';
  }
  
  if (keyCode == LEFT) {
    instruction = 'R';
  }
  
  if (keyCode == DOWN) {
    instruction = 'B';
  }
  
  myPort.write(instruction);  
}

void keyReleased() {
  myPort.write('O');
}



