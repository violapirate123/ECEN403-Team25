/*Color Sensor*/
#include <Wire.h>
#include "TCS34725.h"

// Initialise with specific int time and gain values
TCS34725 tcs = TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

// Calibration values
unsigned int redlow = 504;
unsigned int redhigh = 1236;
unsigned int greenlow = 380;
unsigned int greenhigh = 1244;
unsigned int bluelow = 354;
unsigned int bluehigh = 1293;

// Declare RGB Values
int red = 0;
int green = 0;
int blue = 0;

int redOut = 0;
int greenOut = 0;
int blueOut = 0;
/* Color Sensor End */

bool colorcorrect, sound1correct, sound2correct;

/* Color Sensor Functions */
// Color Light Roast
bool colorlight(void) {
  uint16_t r, g, b;
  tcs.getRawData(&r, &g, &b); // Getting RGB Values

  // Convert to RGB values
  int redV = map(r, redlow, redhigh, 0, 255);
  int greenV = map(g, greenlow, greenhigh, 0, 255);
  int blueV = map(b, bluelow, bluehigh, 0, 255);

  // Constrain to values of 0-65535
  red = constrain(redV, 0, 255);
  green = constrain(greenV, 0, 255);
  blue = constrain(blueV, 0, 255);
  
  while(colorcorrect == false){

  // IF ELSE STATEMENT RED
  if (83 <= red && red <= 130)          // Not Roasted
    { redOut = 0; }
  else if (131 <= red && red <= 200)    // Light Roast
    { redOut = 1; }
  else if (61 <= red && red <= 82)      // Medium Roast
    { redOut = 2; }
  else if (0 <= red && red <= 60)       // Dark Roast
    { redOut = 3; }
  else
    { redOut = 4; }
  // IF ELSE STATEMENT GREEN
  if (83 <= green  && green <= 119)        // Not Roasted
    { greenOut = 0; }
  else if (120 <= green && green <= 200)    // Light Roast
    { greenOut = 1; }
  else if (62 <= green && green <= 82)      // Medium Roast
    { greenOut = 2; }
  else if (0 <= green && green <= 61)       // Dark Roast
    { greenOut = 3; }
  else 
    { greenOut = 4; }
  // IF ELSE STATEMENT BLUE
  if (96 <= blue && blue <= 120)          // Not Roasted
    { blueOut = 0; }
  else if (121 <= blue && blue <= 200)    // Light Roast
    { blueOut = 1; }
  else if (62 <= blue && blue <= 95)      // Medium Roast
    { blueOut = 2; }
  else if (0 <= blue && blue <= 61)       // Dark Roast
    { blueOut = 3; }
  else
    { blueOut = 4; }
    
  // IF ELSE STATEMENT ROAST
  if (redOut == 1 && greenOut == 1 && blueOut == 1) // Light Roast
    { colorcorrect = true; }
  else if (redOut == 0 && greenOut == 1 && blueOut == 1)  // Light Roast (Overlapping Red with Not)
    { colorcorrect = true; }
  else if (redOut == 1 && greenOut == 0 && blueOut == 1)  // Light Roast (Overlapping Green with Not)
    { colorcorrect = true; }
  else if (redOut == 1 && greenOut == 1 && blueOut == 0)  // Light Roast (Overlapping Blue with Not)
    { colorcorrect = true; }
  else
    { colorcorrect = false; }
 }
  return colorcorrect;
}
/*
// Color Medium Roast
bool colormedium(void) {
  uint16_t r, g, b;
  tcs.getRawData(&r, &g, &b); // Getting RGB Values
  // Convert to RGB values
  int redV = map(r, redlow, redhigh, 0, 255);
  int greenV = map(g, greenlow, greenhigh, 0, 255);
  int blueV = map(b, bluelow, bluehigh, 0, 255);
  // Constrain to values of 0-65535
  red = constrain(redV, 0, 255);
  green = constrain(greenV, 0, 255);
  blue = constrain(blueV, 0, 255);
  while(colorcorrect == false){
  // IF ELSE STATEMENT RED
  if (83 <= red && red <= 130)          // Not Roasted
    { redOut = 0; }
  else if (131 <= red && red <= 200)    // Light Roast
    { redOut = 1; }
  else if (61 <= red && red <= 82)      // Medium Roast
    { redOut = 2; }
  else if (0 <= red && red <= 60)       // Dark Roast
    { redOut = 3; }
  else
    { redOut = 4; }
  // IF ELSE STATEMENT GREEN
  if (83 <= green  && green <= 119)        // Not Roasted
    { greenOut = 0; }
  else if (120 <= green && green <= 200)    // Light Roast
    { greenOut = 1; }
  else if (62 <= green && green <= 82)      // Medium Roast
    { greenOut = 2; }
  else if (0 <= green && green <= 61)       // Dark Roast
    { greenOut = 3; }
  else 
    { greenOut = 4; }
  // IF ELSE STATEMENT BLUE
  if (96 <= blue && blue <= 120)          // Not Roasted
    { blueOut = 0; }
  else if (121 <= blue && blue <= 200)    // Light Roast
    { blueOut = 1; }
  else if (62 <= blue && blue <= 95)      // Medium Roast
    { blueOut = 2; }
  else if (0 <= blue && blue <= 61)       // Dark Roast
    { blueOut = 3; }
  else
    { blueOut = 4; }
  // IF ELSE STATEMENT ROAST
  if (redOut == 2 && greenOut == 2 && blueOut == 2) // Medium Roast
    { colorcorrect = true; }
  else if (redOut == 0 && greenOut == 2 && blueOut == 2)  // Medium Roast (Overlapping Red with Not)
    { colorcorrect = true; }
  else if (redOut == 2 && greenOut == 0 && blueOut == 2)  // Medium Roast (Overlapping Green with Not)
    { colorcorrect = true; }
  else if (redOut == 2 && greenOut == 2 && blueOut == 0)  // Medium Roast (Overlapping Blue with Not)
    { colorcorrect = 1; }
  else if (redOut == 3 && greenOut == 2 && blueOut == 2)  // Medium Roast (Overlapping Red with Dark)
    { colorcorrect = true; }
  else if (redOut == 2 && greenOut == 3 && blueOut == 2)  // Medium Roast (Overlapping Green with Dark)
    { colorcorrect = true; }
  else if (redOut == 2 && greenOut == 2 && blueOut == 3)  // Medium Roast (Overlapping Blue with Dark)
    { colorcorrect = true; }
  else
    { colorcorrect = false; }
 }
  return colorcorrect;
}
    
// Color Dark Roast
bool colordark(void) {
  uint16_t r, g, b;
  tcs.getRawData(&r, &g, &b); // Getting RGB Values
  // Convert to RGB values
  int redV = map(r, redlow, redhigh, 0, 255);
  int greenV = map(g, greenlow, greenhigh, 0, 255);
  int blueV = map(b, bluelow, bluehigh, 0, 255);
  // Constrain to values of 0-65535
  red = constrain(redV, 0, 255);
  green = constrain(greenV, 0, 255);
  blue = constrain(blueV, 0, 255);
  while(colorcorrect == false){
  // IF ELSE STATEMENT RED
  if (83 <= red && red <= 130)          // Not Roasted
    { redOut = 0; }
  else if (131 <= red && red <= 200)    // Light Roast
    { redOut = 1; }
  else if (61 <= red && red <= 82)      // Medium Roast
    { redOut = 2; }
  else if (0 <= red && red <= 60)       // Dark Roast
    { redOut = 3; }
  else
    { redOut = 4; }
  // IF ELSE STATEMENT GREEN
  if (83 <= green  && green <= 119)        // Not Roasted
    { greenOut = 0; }
  else if (120 <= green && green <= 200)    // Light Roast
    { greenOut = 1; }
  else if (62 <= green && green <= 82)      // Medium Roast
    { greenOut = 2; }
  else if (0 <= green && green <= 61)       // Dark Roast
    { greenOut = 3; }
  else 
    { greenOut = 4; }
  // IF ELSE STATEMENT BLUE
  if (96 <= blue && blue <= 120)          // Not Roasted
    { blueOut = 0; }
  else if (121 <= blue && blue <= 200)    // Light Roast
    { blueOut = 1; }
  else if (62 <= blue && blue <= 95)      // Medium Roast
    { blueOut = 2; }
  else if (0 <= blue && blue <= 61)       // Dark Roast
    { blueOut = 3; }
  else
    { blueOut = 4; }
  
  // IF ELSE STATEMENT ROAST
  if (redOut == 3 && greenOut == 3 && blueOut == 3) // Dark Roast
    { colorcorrect = true; }
  else if (redOut == 2 && greenOut == 3 && blueOut == 3)  // Dark Roast (Overlapping Red with Medium)
    { colorcorrect = true; }
  else if (redOut == 3 && greenOut == 2 && blueOut == 3)  // Dark Roast (Overlapping Green with Medium)
    { colorcorrect = true; }
  else if (redOut == 3 && greenOut == 3 && blueOut == 2)  // Dark Roast (Overlapping Blue with Medium)
    { colorcorrect = true; }
  else
    { colorcorrect = false; }
 }
  return colorcorrect;
}
*/
void coffeebeansdetected(void) {
  uint16_t r, g, b;
  tcs.getRawData(&r, &g, &b); // Getting RGB Values

  // Convert to RGB values
  int redV = map(r, redlow, redhigh, 0, 255);
  int greenV = map(g, greenlow, greenhigh, 0, 255);
  int blueV = map(b, bluelow, bluehigh, 0, 255);

  // Constrain to values of 0-65535
  red = constrain(redV, 0, 255);
  green = constrain(greenV, 0, 255);
  blue = constrain(blueV, 0, 255);

  // IF ELSE STATEMENT RED
  if (83 <= red && red <= 130)          // Not Roasted
    { redOut = 0; }
  else if (131 <= red && red <= 200)    // Light Roast
    { redOut = 1; }
  else if (61 <= red && red <= 82)      // Medium Roast
    { redOut = 2; }
  else if (0 <= red && red <= 60)       // Dark Roast
    { redOut = 3; }
  else
    { redOut = 4; }
  // IF ELSE STATEMENT GREEN
  if (83 <= green  && green <= 119)        // Not Roasted
    { greenOut = 0; }
  else if (120 <= green && green <= 200)    // Light Roast
    { greenOut = 1; }
  else if (62 <= green && green <= 82)      // Medium Roast
    { greenOut = 2; }
  else if (0 <= green && green <= 61)       // Dark Roast
    { greenOut = 3; }
  else 
    { greenOut = 4; }
  // IF ELSE STATEMENT BLUE
  if (96 <= blue && blue <= 120)          // Not Roasted
    { blueOut = 0; }
  else if (121 <= blue && blue <= 200)    // Light Roast
    { blueOut = 1; }
  else if (62 <= blue && blue <= 95)      // Medium Roast
    { blueOut = 2; }
  else if (0 <= blue && blue <= 61)       // Dark Roast
    { blueOut = 3; }
  else
    { blueOut = 4; }

  // IF ELSE STATEMENT ROAST
  if (redOut == 0 && greenOut == 0 && blueOut == 0) // Not Roasted
    { return; }
  else if (redOut == 1 && greenOut == 0 && blueOut == 0)  // Not Roasted (Overlapping Red with Light)
    { return; }
  else if (redOut == 0 && greenOut == 1 && blueOut == 0)  // Not Roasted (Overlapping Green with Light)
    { return; }
  else if (redOut == 0 && greenOut == 0 && blueOut == 1)  // Not Roasted (Overlapping Blue with Light)
    { return; }
  else if (redOut == 2 && greenOut == 0 && blueOut == 0)  // Not Roasted (Overlapping Red with Medium)
    { return; }
  else if (redOut == 0 && greenOut == 0 && blueOut == 2)  // Not Roasted (Overlapping Blue with Medium)
    { return; }
  else
    { delay(5000);
      coffeebeansdetected(); }
}
/* Color Sensor Functions End */



//BUTTON SET UP
const int light_button = 2; //set button pin
const int medium_button = 3;
const int dark_button = 4;
const int wire = 5; //heating
int light_button_state = 0;
int medium_button_state = 0;
int dark_button_state = 0;

//TEMP SET UP
int TC_Pin = A1; //analog to digital converter
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


  /*Color Sensor Set Up*/
  /*// Check if Color Sensor Connected
  if (tcs.begin()) 
  {  // Checking if sensor is connected
    Serial.println("Sensor Connected");
  } 
  else 
  {
    Serial.println("Sensor NOT Connected");
    while (1);
  }
  // Check if Color Sensor Connected End
  /* Color Sensor Set Up End*/


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
     coffeebeansdetected();
    while (light_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 200){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
      }
      /*
      if (temp >= ____) {
        while (soundfirst == false && colorcorrect == false)
        {
          soundfirst();
          //colorlight();
          //temperature has to be in the range of 300 degrees farenheit, we need the function for this.
        }
      }
      //if ( (temp && sound == true) || ((temp && color == true))
      */
     
    }
  }
  if (medium_button_state == HIGH)
  { 
    coffeebeansdetected();
    while (medium_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 215){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
      }
      soundfirst();
      //colormedium();
      //temperature has to be in the range of 410 degrees to 428 degrees farenheit, we need a function for this.
    }
  }
  if (dark_button_state == HIGH)
  {
    coffeebeansdetected();
    while (dark_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 235){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
      }
      soundfirst();
      //soundsecond();
      //colordark();
      //temperature has to be in between 465 and 480 degrees farenheit, we need a function for this.
    }
  }
}
