#include <Wire.h>
#include "TCS34725.h"
//#include "colorcode"

/* Pushbutton */
const int light_button = 2; //set button pin
const int medium_button = 3;
const int dark_button = 4;
int light_button_state = 0;
int medium_button_state = 0;
int dark_button_state = 0;
/* Pushbutton End */


/* Temperature */
const int wire = 5; //heating
int TC_Pin = A1; //analog to digital converter
int raw_adc = 0;
#define AREF 3.3 // voltage used by amplifier

float reading, voltage, temp;

float get_voltage(int raw_adc) 
{ //turns ADC reading to voltage
  //Serial.print(raw_adc);
  return raw_adc * (AREF / 1023);
}
float get_temp(float voltage)
{ //turned voltage to temp
  return (voltage - .5) / .01;
}
/* Temperature */

/* Color Sensor */ 
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

//someting
int colorcorrect, sound1correct, sound2correct;
/* Color Sensor End */


/* Sound Sensor */
#include "arduinoFFT.h" 
#define Sampling_Frequency 2048

arduinoFFT FFT = arduinoFFT();

unsigned int samplingprd;
unsigned long microsec;
int CrackSensor = A0; // assigns crack sensor circuit to analog pin 1.
int FirstCrack = 3; // assigns output signal for first crack to digital pin 3.
int SecondCrack = 4; //assigns output signal for second crack to digital pin 4.
bool firstcrackregistered = false; // boolean that is set to true once the coffee roasting process is in the "First crack stage".
bool secondcrackregistered = false; // boolean that is set to true once the coffee roasting process is in the "Second crack stage".
int crackcount = 0; //integer value to count for number of crack sounds.
int secondcrackcount = 0; //integer value to count for number of crack sounds at second crack.
double imaginary[128];
double data[128];
int i = 0;
int value;
/* Sound Sensor End */

/* Sound Sensor Functions */
void soundfirst(void) {
  for (i = 0;i < 128; i++){//loops 128 times to take 128 samples of ADC from electret microphone.
    microsec = micros();// sets microsec variable to the amount of time processor takes to process information.
   value = analogRead(CrackSensor);//takes sound sensor data and assigns it to premade variable "value".
   data[i] = value;// places the analog to digital values in the array "data"
   imaginary[i] = 0; //sets imaginary values to 0.
   while(micros() < (microsec + samplingprd)){//allows for a fixed sampling time depending on speed of microprocessor.
    //dont take samples while this is happening to allow processing time to catch up to sampling data.
   }
  }
  FFT.Windowing(data, 128, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//first part of FFT 
  FFT.Compute(data, imaginary, 128, FFT_FORWARD);//computational part of FFT
  FFT.ComplexToMagnitude(data, imaginary, 128);//complex magnitude part of FFT

  double peak = FFT.MajorPeak(data, 128, Sampling_Frequency);//the peak found by the transform is set equal to "peak" variable.
  Serial.println(peak);//this code is to test peaks
  delay(2000);//delay to observe output well.

  if((128.5 <= peak)&&(135.0 >= peak)){ // registers a specific frequency that is converted to a digital number and identifies the crack sound.
    crackcount = crackcount + 1; //increments value of crack sound number everytime desired frequency is detected by the microcontroller.
  }
  else{ //else statement to keep count for first crack the same.
    crackcount = crackcount; //keeps the count for firstcrack the same.
  }
  if(crackcount >= 7){ // if 7 CLEAR cracks are heard, the boolean "firstcrackregistered" is set to true.
    firstcrackregistered = true; //boolean is set to true with given condition.
  }
  if(firstcrackregistered){ //first crack is successfully registered.
  digitalWrite(FirstCrack, HIGH); // LED for first crack stays constantly on when the boolean for first crack is set to true.
  } 

  else{ // else statement when first crack boolean is set to false.
  digitalWrite(FirstCrack, LOW); //keeps the LED for first crack on while the boolean for first crack remains false.
 }
}
/* Sound Sensor Functions End */

/* Color Sensor Functions */
// Color Light Roast
void colorlight(void) {
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
  {
    redOut = 0;
  }
  else if (131 <= red && red <= 200)    // Light Roast
  {
    redOut = 1;
  }
  else if (61 <= red && red <= 82)      // Medium Roast
  {
    redOut = 2;
  }
  else if (0 <= red && red <= 60)       // Dark Roast
  {   
    redOut = 3;
  }
  else
  {
    redOut = 4;
  }
  // IF ELSE STATEMENT GREEN
  if (83 <= green  && green <= 119)        // Not Roasted
  {
    greenOut = 0;
  }
  else if (120 <= green && green <= 200)    // Light Roast
  {
    greenOut = 1;
  }
  else if (62 <= green && green <= 82)      // Medium Roast
  {
    greenOut = 2;
  }
  else if (0 <= green && green <= 61)       // Dark Roast
  {   
    greenOut = 3;
  }
  else 
  {
    greenOut = 4;
  }

  // IF ELSE STATEMENT BLUE
  if (96 <= blue && blue <= 120)          // Not Roasted
  {
    blueOut = 0;
  }
  else if (121 <= blue && blue <= 200)    // Light Roast
  {
    blueOut = 1;
  }
  else if (62 <= blue && blue <= 95)      // Medium Roast
  {
    blueOut = 2;
  }
  else if (0 <= blue && blue <= 61)       // Dark Roast
  {   
    blueOut = 3;
  }
  else
  {
    blueOut = 4;
  }

  if (redOut == 1 &&                    // Light Roast
      greenOut == 1 &&
      blueOut == 1)
  {
    colorcorrect = 1;
  }
  else if (redOut == 0 &&              // Light Roast (Overlapping Red with Not)
           greenOut == 1 &&
           blueOut == 1)
  {
    colorcorrect = 1;       
  }
  else if (redOut == 1 &&              // Light Roast (Overlapping Green with Not)
           greenOut == 0 &&
           blueOut == 1)
  {
    colorcorrect = 1;
  }
  else if (redOut == 1 &&              // Light Roast (Overlapping Blue with Not)
           greenOut == 1 &&
           blueOut == 0)
  {
    colorcorrect = 1;
  }
  else
  {
    colorcorrect = 0;
  }
  return colorcorrect;
}

// Color Medium Roast
void colormedium(void) {
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
  {
    redOut = 0;
  }
  else if (131 <= red && red <= 200)    // Light Roast
  {
    redOut = 1;
  }
  else if (61 <= red && red <= 82)      // Medium Roast
  {
    redOut = 2;
  }
  else if (0 <= red && red <= 60)       // Dark Roast
  {   
    redOut = 3;
  }
  else
  {
    redOut = 4;
  }
  // IF ELSE STATEMENT GREEN
  if (83 <= green  && green <= 119)        // Not Roasted
  {
    greenOut = 0;
  }
  else if (120 <= green && green <= 200)    // Light Roast
  {
    greenOut = 1;
  }
  else if (62 <= green && green <= 82)      // Medium Roast
  {
    greenOut = 2;
  }
  else if (0 <= green && green <= 61)       // Dark Roast
  {   
    greenOut = 3;
  }
  else 
  {
    greenOut = 4;
  }

  // IF ELSE STATEMENT BLUE
  if (96 <= blue && blue <= 120)          // Not Roasted
  {
    blueOut = 0;
  }
  else if (121 <= blue && blue <= 200)    // Light Roast
  {
    blueOut = 1;
  }
  else if (62 <= blue && blue <= 95)      // Medium Roast
  {
    blueOut = 2;
  }
  else if (0 <= blue && blue <= 61)       // Dark Roast
  {   
    blueOut = 3;
  }
  else
  {
    blueOut = 4;
  }

  if (redOut == 2 &&                    // Medium Roast
      greenOut == 2 &&
      blueOut == 2)
  {
    colorcorrect = 1;
  }
  else if (redOut == 0 &&              // Medium Roast (Overlapping Red with Not)
           greenOut == 2 &&
           blueOut == 2)
  {
    colorcorrect = 1;
  }
  else if (redOut == 2 &&             // Medium Roast (Overlapping Green with Not)
           greenOut == 0 &&
           blueOut == 2)
  {
    colorcorrect = 1;
  }
  else if (redOut == 2 &&             // Medium Roast (Overlapping Blue with Not)
           greenOut == 2 &&
           blueOut == 0)
  {
    colorcorrect = 1;
  }
  else if (redOut == 3 &&             // Medium Roast (Overlapping Red with Dark)
           greenOut == 2 &&
           blueOut == 2)
  {
    colorcorrect = 1;
  }
  else if (redOut == 2 &&             // Medium Roast (Overlapping Green with Dark)
           greenOut == 3 &&
           blueOut == 2)
  {
    colorcorrect = 1;
  }
  else if (redOut == 2 &&             // Medium Roast (Overlapping Blue with Dark)
          greenOut == 2 &&
          blueOut == 3)
  {
    colorcorrect = 1;
  }
  else
  {
    colorcorrect = 0;
  }
  return colorcorrect;
}
    
// Color Dark Roast
void colordark(void) {
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
  {
    redOut = 0;
  }
  else if (131 <= red && red <= 200)    // Light Roast
  {
    redOut = 1;
  }
  else if (61 <= red && red <= 82)      // Medium Roast
  {
    redOut = 2;
  }
  else if (0 <= red && red <= 60)       // Dark Roast
  {   
    redOut = 3;
  }
  else
  {
    redOut = 4;
  }
  // IF ELSE STATEMENT GREEN
  if (83 <= green  && green <= 119)        // Not Roasted
  {
    greenOut = 0;
  }
  else if (120 <= green && green <= 200)    // Light Roast
  {
    greenOut = 1;
  }
  else if (62 <= green && green <= 82)      // Medium Roast
  {
    greenOut = 2;
  }
  else if (0 <= green && green <= 61)       // Dark Roast
  {   
    greenOut = 3;
  }
  else 
  {
    greenOut = 4;
  }

  // IF ELSE STATEMENT BLUE
  if (96 <= blue && blue <= 120)          // Not Roasted
  {
    blueOut = 0;
  }
  else if (121 <= blue && blue <= 200)    // Light Roast
  {
    blueOut = 1;
  }
  else if (62 <= blue && blue <= 95)      // Medium Roast
  {
    blueOut = 2;
  }
  else if (0 <= blue && blue <= 61)       // Dark Roast
  {   
    blueOut = 3;
  }
  else
  {
    blueOut = 4;
  }

  if (redOut == 3 &&                  // Dark Roast
      greenOut == 3 &&
      blueOut == 3)
  {
    colorcorrect = 1;
  }

  else if (redOut == 2 &&             // Dark Roast (Overlapping Red with Medium)
           greenOut == 3 &&
           blueOut == 3)
  {
    colorcorrect = 1;
  }
  else if (redOut == 3 &&             // Dark Roast (Overlapping Green with Medium)
           greenOut == 2 &&
           blueOut == 3)
  {
    colorcorrect = 1;
  }
  else if (redOut == 3 &&            // Dark Roast (Overlapping Blue with Medium)
           greenOut == 3 &&
           blueOut == 2)
  {
    colorcorrect = 1;
  }
  else
  {
    colorcorrect = 0;
  }
  return colorcorrect;
}

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
  {
    redOut = 0;
  }
  else if (131 <= red && red <= 200)    // Light Roast
  {
    redOut = 1;
  }
  else if (61 <= red && red <= 82)      // Medium Roast
  {
    redOut = 2;
  }
  else if (0 <= red && red <= 60)       // Dark Roast
  {   
    redOut = 3;
  }
  else
  {
    redOut = 4;
  }
  // IF ELSE STATEMENT GREEN
  if (83 <= green  && green <= 119)        // Not Roasted
  {
    greenOut = 0;
  }
  else if (120 <= green && green <= 200)    // Light Roast
  {
    greenOut = 1;
  }
  else if (62 <= green && green <= 82)      // Medium Roast
  {
    greenOut = 2;
  }
  else if (0 <= green && green <= 61)       // Dark Roast
  {   
    greenOut = 3;
  }
  else 
  {
    greenOut = 4;
  }

  // IF ELSE STATEMENT BLUE
  if (96 <= blue && blue <= 120)          // Not Roasted
  {
    blueOut = 0;
  }
  else if (121 <= blue && blue <= 200)    // Light Roast
  {
    blueOut = 1;
  }
  else if (62 <= blue && blue <= 95)      // Medium Roast
  {
    blueOut = 2;
  }
  else if (0 <= blue && blue <= 61)       // Dark Roast
  {   
    blueOut = 3;
  }
  else
  {
    blueOut = 4;
  }

  // IF ELSE STATEMENT ROAST
  if (redOut == 0 &&                   // Not Roasted
      greenOut == 0 &&
      blueOut == 0)
  {
    return;    
  }
  else if (redOut == 1 &&              // Not Roasted (Overlapping Red with Light)
           greenOut == 0 &&
           blueOut == 0)
  {
    return; 
  }
  else if (redOut == 0 &&              // Not Roasted (Overlapping Green with Light)
           greenOut == 1 &&
           blueOut == 0)
  {
    Serial.print("Not Roasted\n");
  }
  else if (redOut == 0 &&              // Not Roasted (Overlapping Blue with Light)
           greenOut == 0 &&
           blueOut == 1)
  {
    return; 
  }
  else if (redOut == 2 &&              // Not Roasted (Overlapping Red with Medium)
           greenOut == 0 &&
           blueOut == 0)
  {
    return; 
  }
  else if (redOut == 0 &&              // Not Roasted (Overlapping Blue with Medium)
           greenOut == 0 &&
           blueOut == 2)
  {
    return; 
  }
  else
  {
    delay(5000);
    coffeebeansdetected();
  }
}

/* Color Sensor Functions End */

void setup() {
  /*  Pushbutton Set Up */
  // Set up the pushbutton pins to be an input
  pinMode(light_button, INPUT);
  pinMode(medium_button, INPUT);
  pinMode(dark_button, INPUT);
  pinMode(wire, OUTPUT);
  /* Pushbutton Set Up End*/

  /* Color Sensor Set Up */
  // Check if Color Sensor Connected
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

  /* Sound Sensor Set Up */
  samplingprd = round(1000000*(1/Sampling_Frequency));
  pinMode (CrackSensor, INPUT); // sets crack sensor as input.
  pinMode (FirstCrack, OUTPUT);// sets firstcrack signal as output.
  pinMode (SecondCrack, OUTPUT); // sets secondcrack signal as output.
  /* Sound Sensor Set Up End */

  Serial.begin(9600);
}

void loop() {
  //int colorcorrect, sound1correct, sound2correct;
  
  //read state
  light_button_state = digitalRead(light_button);
  medium_button_state = digitalRead(medium_button);
  dark_button_state = digitalRead(dark_button);

  coffeebeansdetected();

  // Light Roast
  if (light_button_state == HIGH)
  { 
    while (light_button_state == HIGH)
    { //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 200){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
    }
    colorlight();
    if (colorcorrect == 1)
    {
//      ______
    }
    else
    {
      delay(5000);
      colorlight();
    }
  }
  }
  // Medium Roast
  else if (medium_button_state == HIGH)
  {
    while (medium_button_state == HIGH)
    { //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 215){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
    }
    colormedium();
    if (colorcorrect == 1 )
    {
//      ______
    }
    else
    {
      delay(5000);
      colormedium();
    }
  }
  }
  // Dark Roast
  else if (dark_button_state == HIGH)
  {
    while (dark_button_state == HIGH)
    { //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      //temp
      reading = analogRead(TC_Pin);
      voltage = get_voltage(reading);
      temp = get_temp(voltage);
      if (temp == 235){ //we can mess with this i needed a place holder to turn off the wire
        digitalWrite(wire, LOW);
    }
    colordark();
    //else if (colorcorrect == 1)
    {
//      ______
    }
//    else
    {
      delay(5000);
      colordark();
    }
  }
}
}



    
/* Cool Down Function */
/* Cool Down Function End */
    
/* Motor Function */
/* Motor Function End */
    
/* Thermal Function */
/* Thermal Function End */
