const int stepperpin = 8; //stepper pin of rod motor set to pin 8.
const int driverpin = 9; //driver pin of rod motor set to pin 9.

void setup() {
 pinMode(8,OUTPUT); // pin 8 set as output.
 pinMode(9,OUTPUT); // pin 9 set as output.

}

void loop() {
  digitalWrite(driverpin,HIGH); //initiates motor rotation.

  for(int i = 0; i < 200; i++){ //loop that will send 200 pulses to stepper motor(this depends on step angle of 1.8 degrees.
    digitalWrite(stepperpin,LOW); //high part of pulse.
    delayMicroseconds(1); //very small delay for maximum speed,it can be adjusted if you find issues.
    digitalWrite(stepperpin,LOW); //low part of pulse.
    delayMicroseconds(1); //very small delay for maximum speed,it can be adjusted if you find issues.
  }

}// to stop motor you need digitalWrite(driverpin,LOW), I dont think you need a function for this, can be placed in the main code after roast is completed.
