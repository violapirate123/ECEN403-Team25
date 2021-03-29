int temperaturepwm = 11; //sets pwm signal to pin 11
int mediumroast = 230; //230 is a duty cycle below maximum efficiency but large enough for medium roast.
void setup() {
 pinMode(temperaturepwm,OUTPUT); //sets the variable for pwm to output. 
  

}

void loop() {
  analogWrite(temperaturepwm,mediumroast); //applies duty cycle for medium roast temperature.

}
