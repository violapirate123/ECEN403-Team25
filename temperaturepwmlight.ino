int temperaturepwm = 11; // sets pwm signal to pin 11.
int lightroast = 209; //equal to duty cycle below maximum value but enough to produce light roast temperature.


void setup() {
  pinMode(temperaturepwm,OUTPUT); //sets pwm variable as output.

}

void loop() {
  analogWrite(temperaturepwm,lightroast); //writes duty cycle on the pwm variable, causes heating of nichrome wire to be for light roast.

}
