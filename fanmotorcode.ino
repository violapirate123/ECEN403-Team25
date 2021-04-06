const int stepperpin = 6; //stepper pin of fan motor set to pin 6.
const int driverpin = 7; //driver pin of fan motor set to pin 7.

void setup() {
 pinMode(6,OUTPUT); // pin 6 set as output.
 pinMode(7,OUTPUT); // pin 7 set as output.

}

void loop() {
  digitalWrite(driverpin,HIGH); //initiates motor rotation.

  for(int i = 0; i < 200; i++){ //loop that will send 200 pulses to stepper motor(this depends on step angle of 1.8 degrees.
    digitalWrite(stepperpin,HIGH);//high part of pulse.
    delayMicroseconds(1); //very small delay for maximum speed,it can be adjusted if you find issues.
    digitalWrite(stepperpin,LOW); //low part of pulse.
    delayMicroseconds(1);// very small delay for maximum speed,it can be adjusted if you find issues.
  }

}
