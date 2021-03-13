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

/* Sound Sensor First Crack */
#include "arduinoFFT.h" //performs conversion on ADC values directly.

#define Sampling_Frequency 2048 //needs to be twice the number of the maximum frequency expected to detect.
#include <ExtendedADCShield.h>
ExtendedADCShield extendedADCShield(12);
arduinoFFT FFT = arduinoFFT(); //performs FFT from ADC data collected from microphone.

unsigned int samplingprd; //period of sampling for microprocessor.
unsigned long microsec; //unit used for sampling time.

int CrackSensor = A0; // assigns crack sensor circuit to analog pin 1.
int FirstCrack = 3; // assigns output signal for first crack to digital pin 3.
bool firstcrackregistered = false; // boolean that is set to true once the coffee roasting process is in the "First crack stage".
int crackcount = 0; //integer value to count for number of crack sounds.
int sensorval = 0;  //initialization of sensor variable, equivalent to ema Y, used for high pass filter.
float ema_a = 0.7523086052;    //initialization of ema alpha, equivalent to a frequency value of around 990hz.
int ema_S = 0;        //initialization of ema S, used for high pass filter.
int lowpassfilter = 0; //initialized to zero.

int sensorval2 = 0;
float ema_b = 0.6970588518;
int ema_T = 0;
int filteredsignal = 0;

double imaginary[128];//turns all imaginary inputs into useful data for forier transform.
double data[128];//collects real data into an array of numbers.
int i = 0;// variable used for illeteration in for loops.
int value;// ADC value generated by microprosessor.
/* Sound Sensor First Crack End */

/* Sound Sensor Second Crack */
#include "arduinoFFT.h" //performs conversion on ADC values directly.

#define Sampling_Frequency 32000 //needs to be twice the number of the maximum frequency expected to detect.
#include <ExtendedADCShield.h>
arduinoFFT FFT = arduinoFFT(); //performs FFT from ADC data collected from microphone.
ExtendedADCShield extendedADCShield(12);

unsigned int samplingprd; //period of sampling for microprocessor.
unsigned long microsec; //unit used for sampling time.

int CrackSensor = A0; // assigns crack sensor circuit to analog pin 1.
int SecondCrack = 4; // assigns output signal for first crack to digital pin 3.
bool secondcrackregistered = false; // boolean that is set to true once the coffee roasting process is in the "First crack stage".
int crackcount = 0; //integer value to count for number of crack sounds.
int sensorval = 0;  //initialization of sensor variable, equivalent to ema Y, used for high pass filter.
float ema_a = 0.758546993;    //initialization of ema alpha, equivalent to a frequency value of around 1000hz.
int ema_S = 0;        //initialization of ema S, used for high pass filter.
int lowpassfilter = 0; //initialized to zero.

int sensorval2 = 0;
float ema_b = 0.7260813406;
int ema_T = 0;
int filteredsignal = 0;

double imaginary[128];//turns all imaginary inputs into useful data for forier transform.
double data[128];//collects real data into an array of numbers.
int i = 0;// variable used for illeteration in for loops.
int value;// ADC value generated by microprosessor.
/* Sound Sensor Second Crack end */

/* Sound Sensor Functions */
bool soundfirst(void) {
  sensorval = analogRead(CrackSensor);              //read the sensor value using ADC
  ema_S = (ema_a*sensorval) + ((1-ema_a)*ema_S);  //run the EMA
  lowpassfilter = ema_S; //create lowpassfilter.
  
   ema_T = (ema_b*lowpassfilter) + ((1-ema_b)*ema_T);
   filteredsignal = lowpassfilter - ema_T;
  
  

  for (i = 0;i < 128; i++){//loops 128 times to take 128 samples of ADC from electret microphone.
    microsec = micros();// sets microsec variable to the amount of time processor takes to process information.
   value = analogRead(filteredsignal);//takes sound sensor data and assigns it to premade variable "value".
   data[i] = value;// places the analog to digital values in the array "data"
   imaginary[i] = 0; //sets imaginary values to 0.
   while(micros() < (microsec + samplingprd)){//allows for a fixed sampling time depending on speed of microprocessor.
    //dont take samples while this is happening to allow processing time to catch up to sampling data.
   }
  }
  
  FFT.Windowing(data, 128, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//first part of FFT 
  FFT.Compute(data, imaginary, 128, FFT_FORWARD);//computational part of FFT
  FFT.ComplexToMagnitude(data, imaginary, 128);//complex magnitude part of FFT

  
  
  //double peak = FFT.MajorPeak(data, 128, Sampling_Frequency);//the peak found by the transform is set equal to "peak" variable.
 // Serial.println(peak);//this code is to test peaks
  Serial.println(" ");
  for (i = 0;i < 128; i++){
   Serial.println(data[i]);
   
  }
   for (i = 0;i < 128; i++){
  if((750 <= data[i])&&(980 >= data[i])){ // registers a specific frequency that is converted to a digital number and identifies the crack sound.
    crackcount = crackcount + 1; //increments value of crack sound number everytime desired frequency is detected by the microcontroller.
  }
  else{ //else statement to keep count for first crack the same.
    crackcount = crackcount; //keeps the count for firstcrack the same.
  }
  if(crackcount >= 7){ // if 7 CLEAR cracks are heard, the boolean "firstcrackregistered" is set to true.
    firstcrackregistered = true; //boolean is set to true with given condition.
  }
  
}
  if(firstcrackregistered){ //first crack is successfully registered.
  digitalWrite(FirstCrack, HIGH); // LED for first crack stays constantly on when the boolean for first crack is set to true.
  } 

  else{ // else statement when first crack boolean is set to false.
  digitalWrite(FirstCrack, LOW); //keeps the LED for first crack on while the boolean for first crack remains false.
 }
}

bool soundsecond(void) {
  {
  sensorval = analogRead(CrackSensor);              //read the sensor value using ADC
  ema_S = (ema_a*sensorval) + ((1-ema_a)*ema_S);  //run the EMA
  lowpassfilter = ema_S; //create lowpassfilter.
  
   ema_T = (ema_b*lowpassfilter) + ((1-ema_b)*ema_T);
   filteredsignal = lowpassfilter - ema_T;
  
  

  for (i = 0;i < 128; i++){//loops 128 times to take 128 samples of ADC from electret microphone.
    microsec = micros();// sets microsec variable to the amount of time processor takes to process information.
   value = analogRead(filteredsignal);//takes sound sensor data and assigns it to premade variable "value".
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
 // Serial.println(peak);//this code is to test peaks
  Serial.println(" ");
  for (i = 0;i < 128; i++){
   Serial.println(data[i]);
   
  }
   for (i = 0;i < 128; i++){
  if((14300 <= data[i])&&(15600 >= data[i])){ // registers a specific frequency that is converted to a digital number and identifies the crack sound.
    crackcount = crackcount + 1; //increments value of crack sound number everytime desired frequency is detected by the microcontroller.
  }
  else{ //else statement to keep count for first crack the same.
    crackcount = crackcount; //keeps the count for firstcrack the same.
  }
  if(crackcount >= 7){ // if 7 CLEAR cracks are heard, the boolean "firstcrackregistered" is set to true.
    secondcrackregistered = true; //boolean is set to true with given condition.
  }
  
}
  if(secondcrackregistered){ //first crack is successfully registered.
  digitalWrite(SecondCrack, HIGH); // LED for first crack stays constantly on when the boolean for first crack is set to true.
  } 

  else{ // else statement when first crack boolean is set to false.
  digitalWrite(SecondCrack, LOW); //keeps the LED for first crack on while the boolean for first crack remains false.
 }
}
/* Sound Sensor Functions End */



void setup() {
  // put your setup code here, to run once:
  pinMode(light_button, INPUT);
  pinMode(medium_button, INPUT);
  pinMode(dark_button, INPUT);
  pinMode(wire, OUTPUT);

    /* Sound Sensor First Crack Set Up */
  Serial.begin(9600);
  samplingprd = round(1000000*(1/Sampling_Frequency));
  pinMode (CrackSensor, INPUT); // sets crack sensor as input.
  pinMode (FirstCrack, OUTPUT);// sets firstcrack signal as output.
  ema_S = analogRead(CrackSensor); //initialize one of the variables required for lowpass filtering
  ema_T = analogRead(CrackSensor);
  /* Sound Sensor First Crack Set Up End */
  
  /* Sound Sensor Second Crack Set Up */
   Serial.begin(9600);
  samplingprd = round(1000000*(1/Sampling_Frequency));
  pinMode (CrackSensor, INPUT); // sets crack sensor as input.
  pinMode (SecondCrack, OUTPUT);// sets firstcrack signal as output.
  ema_S = analogRead(CrackSensor); //initialize one of the variables required for lowpass filtering
  ema_T = analogRead(CrackSensor);
  /* Sound Sensor Second Crack Set Up End */

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
      soundfirst();
      //colorlight();
      //temperature has to be in the range of 300 degrees farenheit, we need the function for this.
     
      
      /* sensor code idea
      while (soundfirst == false && colorcorrect == false && temp______) 
      {
            soundfirst();
            colorlight();
            temperature_____
      }
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
