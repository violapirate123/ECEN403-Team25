int temperaturepwm = 11; //sends pwm signal to pin 11 of arduino.
int darkroast = 255; //255 is the full duty cycle going into the pwm pin.
void setup() {
  pinMode(temperaturepwm,OUTPUT); //sets variable for pwm to output.
  
}

void loop() {

  analogWrite(temperaturepwm,darkroast); //sends duty cycle to transistor network to activate heat for dark roast.

}
