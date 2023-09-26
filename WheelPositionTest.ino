// Ben Pacheco, SEED Lab Assignemnt 2. 

// Setup encoder library
#include <Encoder.h>

// Setup encoders
Encoder lWheel(3, 6);
Encoder rWheel(2, 5);

// Create variables for doing the math
double xnew = 0; // Current x pos
double xold = 0; // Old x pos
double ynew = 0; // Current y pos
double yold = 0; // Old y pos
double phinew = 0; // Current angle
long double phiold = 0; // Old angle 
long double lposNew = 0; // Left Rotary Encoder position current
long double rposNew = 0; // Right Rotary Encoder position current
long double lposOld = 0; // Left Old Rotary Encoder position
long double rposOld = 0; // Right Old Rotary Encoder positoin


const float b = 0.365; // Width between wheels 36.5cm
const float r = 0.0725; // Wheel radius 72.5mm
const long deltaT = 1000; // Time change between measurements in ms
const long pi = 3.14; // define a constant for pi
long lastpoll = 0; // store the last polling time


void setup() {
  // Setup serial connection 
  Serial.begin(9600);
  Serial.println("Wheel Position Test");
  
}

void loop() {
  // Wait till designated polling time has passed
  while (millis()<(lastpoll+deltaT)); 

  // Save current postion to old variable before reading the encoders
  xold = xnew; 
  yold = ynew;
  phiold = phinew;
  lposOld = lposNew;
  rposOld = rposNew;

  // Read rotary encoders to get current position
  lposNew = lWheel.read();
  rposNew = rWheel.read();

  // Calculate new xpos
  xnew = xold + (1*cos(phiold)*(((lposNew-lposOld)/3200*2*3.14*0.0725)+((rposNew-rposOld)/3200*2*3.14*0.0725)))/2;

  // Calculate new ypos
  ynew = yold + (1*sin(phiold)*(((lposNew-lposOld)/3200*2*3.14*0.0725)+((rposNew-rposOld)/3200*2*3.14*0.0725)))/2;

  // Calculate new phi
  phinew = phiold + (((lposNew-lposOld)/3200*2*3.14*0.0725)-((rposNew-rposOld)/3200*2*3.14*0.0725))/0.365;

  // Correct additive angle by looping around as you reach 2 pi
  while(phinew>2*3.14){
    phinew = phinew-2*3.14;
  }

  // Correct subtractive angle by looping around as you go below 0 
  while(phinew<0){
    phinew = phinew+2*3.14;
  }
  // Report new positions
  Serial.print(xnew*100);
  Serial.print("  ");
  Serial.print(ynew*100);
  Serial.print("  ");
  Serial.println(phinew);

  // Record the time that the measurement was taken
  lastpoll = millis();

}
