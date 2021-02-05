//button set up

const int light_button = 2; //set button pin
const int medium_button = 3;
const int dark_button = 4;
const int wire = 5; //heating
int light_state = 0;
int medium_state = 0;
int dark_state = 0;

//temp set up
int TC_Pin = A0; //analog to digital converter
int raw_adc = 0;
#define AREF 3.3 // voltage used by amplifier

float reading, voltage, temp;

float get_voltage(int raw_adc) { //turns ADC reading to voltage
  //Serial.print(raw_adc);
  return raw_adc * (AREF / 1023);
}
float get_temp(float voltage){ //turned voltage to temp
  return (voltage - .5) / .01;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(light_button, INPUT);
  pinMode(medium_button, INPUT);
  pinMode(dark_button, INPUT);
  pinMode(wire, OUTPUT);

  //temp
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //read state
  light_button_state = digitalRead(light_button);
  medium_button_state = digitalRead(medium_button);
  dark_button_state = digitalRead(dark_button);
  
  //if pushed
  if (light_button_state == HIGH)
  {
    while (light_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 200){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
      }
    }
  }
  if (medium_button_state == HIGH)
  {
    while (medium_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 215){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
      }
    }
  }
  if (dark_button_state == HIGH)
  {
    while (dark_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 235){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
      }
    }
  }
}
