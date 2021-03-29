int temperaturepwm = 11; //sets pwm variable to pin 11.
int cooldown = 0; //no duty cycle, will completely turn off current into nichrome wire.

void setup() {
  pinMode(temperaturepwm,OUTPUT); //sets pwm variable as output.
}

void loop() {
  analogwrite(temperaturepwm,cooldown); //turns of any type of heating with zero duty cycle

}
