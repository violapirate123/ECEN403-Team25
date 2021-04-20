/*Color Sensor*/
#include <Wire.h>
#include "TCS34725.h"
#include "arduinoFFT.h" //performs conversion on ADC values directly.
#include "ExtendedADCShield.h"

// Initialise with specific int time and gain values
TCS34725 tcs = TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

// Calibration values
unsigned int redlow = 1600;
unsigned int redhigh = 2019;
unsigned int greenlow = 1600;
unsigned int greenhigh = 2029;
unsigned int bluelow = 1600;
unsigned int bluehigh = 2363;

// Declare RGB Values
int red = 0;
int green = 0;
int blue = 0;

int redOut = 0;
int greenOut = 0;
int blueOut = 0;
/* Color Sensor End */

bool colorcorrect;

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

  Serial.print("R: "); Serial.print(red, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(green, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(blue, DEC); Serial.print(" ");
  Serial.println(" ");


  // IF ELSE STATEMENT RED
  if (141 <= red && red <= 255)         // Light Roast
    { redOut = 1; }
  else if (110 <= red && red <= 131)      // Medium Roast
    { redOut = 2; }
  else if (132 <= red && red <= 140)       // Dark Roast
    { redOut = 3; }
  else
    { redOut = 4; }
  // IF ELSE STATEMENT GREEN
  if (91 <= green && green <= 255)    // Light Roast
    { greenOut = 1; }
  else if (50 <= green && green <= 66)      // Medium Roast
    { greenOut = 2; }
  else if (67 <= green && green <= 90)       // Dark Roast
    { greenOut = 3; }
  else 
    { greenOut = 4; }
  // IF ELSE STATEMENT BLUE
  if (60 <= blue && blue <= 69)    // Light Roast
    { blueOut = 1; }
  else if (40 <= blue && blue <= 54)      // Medium Roast
    { blueOut = 2; }
  else if (55 <= blue && blue <= 64)       // Dark Roast
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
 //Serial.println(colorcorrect);
  return colorcorrect;
}

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
  
  Serial.print("R: "); Serial.print(red, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(green, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(blue, DEC); Serial.print(" ");
  Serial.println(" ");
  
  // IF ELSE STATEMENT RED
  if (141 <= red && red <= 255)         // Light Roast
    { redOut = 1; }
  else if (110 <= red && red <= 131)      // Medium Roast
    { redOut = 2; }
  else if (132 <= red && red <= 140)       // Dark Roast
    { redOut = 3; }
  else
    { redOut = 4; }
  // IF ELSE STATEMENT GREEN
  if (91 <= green && green <= 255)    // Light Roast
    { greenOut = 1; }
  else if (50 <= green && green <= 66)      // Medium Roast
    { greenOut = 2; }
  else if (67 <= green && green <= 90)       // Dark Roast
    { greenOut = 3; }
  else 
    { greenOut = 4; }
  // IF ELSE STATEMENT BLUE
  if (60 <= blue && blue <= 69)    // Light Roast
    { blueOut = 1; }
  else if (40 <= blue && blue <= 54)      // Medium Roast
    { blueOut = 2; }
  else if (55 <= blue && blue <= 64)       // Dark Roast
    { blueOut = 3; }
  else
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

  Serial.print("R: "); Serial.print(red, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(green, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(blue, DEC); Serial.print(" ");
  Serial.println(" ");
  
  // IF ELSE STATEMENT RED
  if (141 <= red && red <= 255)         // Light Roast
    { redOut = 1; }
  else if (110 <= red && red <= 131)      // Medium Roast
    { redOut = 2; }
  else if (132 <= red && red <= 140)       // Dark Roast
    { redOut = 3; }
  else
    { redOut = 4; }
  // IF ELSE STATEMENT GREEN
  if (91 <= green && green <= 255)    // Light Roast
    { greenOut = 1; }
  else if (50 <= green && green <= 66)      // Medium Roast
    { greenOut = 2; }
  else if (67 <= green && green <= 90)       // Dark Roast
    { greenOut = 3; }
  else 
    { greenOut = 4; }
  // IF ELSE STATEMENT BLUE
  if (60 <= blue && blue <= 69)    // Light Roast
    { blueOut = 1; }
  else if (40 <= blue && blue <= 54)      // Medium Roast
    { blueOut = 2; }
  else if (55 <= blue && blue <= 64)       // Dark Roast
    { blueOut = 3; }
  else
  
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


/* Color Sensor Functions End */

/*Heating Set up*/
int temp_pwm = 9; //declares pwm pin
int temp_on = 255; //max pwm 
int temp_off = 0;
/*Heating Set up end*/

/*BUTTON SET UP */
//set button pins 2-4
const int light_button = 2;
const int medium_button = 3;
const int dark_button = 4;
const int wire = 5; //turns on pin that will power color and sound sensor

//initialize button states
int light_button_state = 0;
int medium_button_state = 0;
int dark_button_state = 0;
/*BUTTON SET UP END*/

/*TEMP FUNCTION SET UP */
int TC_Pin = A1; //analog to digital converter
int raw_adc = 0;
#define AREF 3.3 // voltage used by amplifier
bool tempcorrect;

//temp light roast
bool templight(void){
  float reading, voltage, temp;
  reading = analogRead(TC_Pin);
  voltage = reading * (AREF / 1023); //ADC to voltage
  temp = (voltage - .5) / .01; //voltage to temp
  if (temp >= 180 || temp <= 205){
    tempcorrect = true; //light roast
  }
  else{
    tempcorrect = false;
  }
  return tempcorrect;
}

//temp medium roast
 bool tempmedium(void){
  float reading, voltage, temp;
  reading = analogRead(TC_Pin);
  voltage = reading * (AREF / 1023); //ADC to voltage
  temp = (voltage - .5) / .01; //voltage to temp
  if (temp >= 210 || temp <= 220){
    tempcorrect = true; //medium roast
  }
  else{
    tempcorrect = false;
  }
  return tempcorrect;
 }

//temp dark roast
 bool tempdark(void){
  float reading, voltage, temp;
  reading = analogRead(TC_Pin);
  voltage = reading * (AREF / 1023); //ADC to voltage
  temp = (voltage - .5) / .01; //voltage to temp
  if (temp >= 225 || temp <= 240){
    tempcorrect = true; // dark roast
  }
  else{
    tempcorrect = false; // not complete
  }
  return tempcorrect;
}
/*TEMP FUNCTION SET UP END*/

/*Sound Sensor Initialization*/
//#include "arduinoFFT.h" //performs conversion on ADC values directly.
//#include "ExtendedADCShield.h"
arduinoFFT FFT = arduinoFFT(); //performs FFT from ADC data collected from microphone.
ExtendedADCShield extendedADCShield(12);
#define Sampling_Frequency 2048 //needs to be twice the number of the maximum frequency expected to detect.
unsigned int samplingprd; //period of sampling for microprocessor.
#define Sampling_Frequency2 32000 //needs to be twice the number of the maximum frequency expected to detect.
unsigned int samplingprd2; //period of sampling for microprocessor.
int CrackSensor = A0; // assigns crack sensor circuit to analog pin 1.
int ema_S = 0;        //initialization of ema S, used for low pass filter.
int ema_T = 0;        //initialization of ema T, used for High pass filter.
/* Sound Sensor Initialization End*/

/* Sound Sensor Functions */
bool firstcrackregistered;
bool soundfirst(void) {
  
  unsigned long microsec; //unit used for sampling time.
  bool firstcrackregistered = false; // boolean that is set to true once the coffee roasting process is in the "First crack stage".
  int crackcount = 0; //integer value to count for number of crack sounds.
  int sensorval = 0;  //initialization of sensor variable, equivalent to ema Y, used for high pass filter.
  float ema_a = 0.7523086052;    //initialization of ema alpha, equivalent to a frequency value of around 990hz.
  int lowpassfilter = 0; //initialized to zero.

  int sensorval2 = 0;
  float ema_b = 0.6970588518;
  int filteredsignal = 0;

  double imaginary[128];//turns all imaginary inputs into useful data for forier transform.
  double data[128];//collects real data into an array of numbers.
  int i = 0;// variable used for illeteration in for loops.
  int value;// ADC value generated by microprosessor.
  
  
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
 return firstcrackregistered;
  }

bool secondcrackregistered = false;
bool soundsecond(void) {

  unsigned long microsec; //unit used for sampling time.
  // boolean that is set to true once the coffee roasting process is in the "First crack stage".
  int crackcount = 0; //integer value to count for number of crack sounds.
  int sensorval = 0;  //initialization of sensor variable, equivalent to ema Y, used for high pass filter.
  float ema_a = 0.758546993;    //initialization of ema alpha, equivalent to a frequency value of around 1000hz.
  int lowpassfilter = 0; //initialized to zero.
  int sensorval2 = 0;
  float ema_b = 0.7260813406;
  int filteredsignal = 0;

  double imaginary[128];//turns all imaginary inputs into useful data for forier transform.
  double data[128];//collects real data into an array of numbers.
  int i = 0;// variable used for illeteration in for loops.
  int value;// ADC value generated by microprosessor.
  Serial.begin(9600);
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
   while(micros() < (microsec + samplingprd2)){//allows for a fixed sampling time depending on speed of microprocessor.
    //dont take samples while this is happening to allow processing time to catch up to sampling data.
   }
  }
  
  FFT.Windowing(data, 128, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//first part of FFT 
  FFT.Compute(data, imaginary, 128, FFT_FORWARD);//computational part of FFT
  FFT.ComplexToMagnitude(data, imaginary, 128);//complex magnitude part of FFT

  

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
   
  
  return secondcrackregistered;
}
/* Sound Sensor Functions End */

/* Motor Function */
const int step_pin1 = 6;//motor 1 step
const int dir_pin1 = 7;//motor 1 direction
const int step_pin2 = 8;//motor 2 step
const int dir_pin2 = 10;//motor 2 direction


//funtion that starts the motors
void motorstart(){
  digitalWrite(dir_pin1, HIGH);
  digitalWrite(dir_pin2, HIGH);
  bool rando = false;
  while (rando == false){
    for(int i = 0; i < 200; i++){ //loop that will send 200 pulses to stepper motor(this depends on step angle of 1.8 degrees)
      digitalWrite(step_pin1,HIGH);//high part of pulse.
      delayMicroseconds(350); //very small delay for maximum speed
      digitalWrite(step_pin1,LOW); //low part of pulse.
      delayMicroseconds(350);// very small delay for maximum speed
      digitalWrite(step_pin2,HIGH);//high part of pulse.
      delayMicroseconds(350); //very small delay for maximum speed
      digitalWrite(step_pin2,LOW); //low part of pulse.
      delayMicroseconds(350);// very small delay for maximum speed
    }
  }
}
void setup() {
    // put your setup code here, to run once:

   /*Button setup */
    pinMode(light_button, INPUT);
    pinMode(medium_button, INPUT);
    pinMode(dark_button, INPUT);
    pinMode(wire, OUTPUT);
    /*Button set up end*/

    /*Motor set up */
    pinMode(step_pin1, OUTPUT);
    pinMode(dir_pin1, OUTPUT);
    pinMode(step_pin2, OUTPUT);
    pinMode(dir_pin2, OUTPUT);
    /*motor set up end*/

    /* Sound Sensor Function Set Up */
    samplingprd2 = round(1000000*(1/Sampling_Frequency2));
    samplingprd = round(1000000*(1/Sampling_Frequency));
    pinMode (CrackSensor, INPUT); // sets crack sensor as input.
    ema_S = analogRead(CrackSensor); //initialize one of the variables required for lowpass filtering
    ema_T = analogRead(CrackSensor); //initialize one of th variables required for highpass filtering
    /* Sound Sensor Function Set Up End */

    /*heating set up*/
    pinMode(temp_pwm, OUTPUT);
    /*heating set up end*/

  /*temp set up*/
  Serial.begin(9600);
  /*temp set up end*/
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //turn off heating of wires
  analogWrite(temp_pwm, temp_off);
  
  //read state
  light_button_state = digitalRead(light_button);
  medium_button_state = digitalRead(medium_button);
  dark_button_state = digitalRead(dark_button);
  
  //if pushed
  if (light_button_state == HIGH)
  {
    analogWrite(temp_pwm,temp_on); // turn on heating
    
    while (light_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire aka power to buttons
      motorstart(); //keeps motors runing for duration

      //keeps sensors running
      while ((firstcrackregistered == false && colorcorrect == false) ||(firstcrackregistered == false && tempcorrect == false) || (colorcorrect == false && tempcorrect == false))
        {
          soundfirst();
          colorlight();
          templight();
        }

      //turns off sensors, motors, and heating once conditions have been met
      if ((tempcorrect == true && firstcrackregistered == true) || (tempcorrect == true && colorcorrect == true) || (firstcrackregistered == true && colorcorrect == true)){
        digitalWrite(wire, LOW);
        digitalWrite(dir_pin1, LOW);
        digitalWrite(dir_pin2, LOW);
        analogWrite(temp_pwm, temp_off); 
       }     
    }
  }

  if (medium_button_state == HIGH)
  { 
    analogWrite(temp_pwm, temp_on);// turn on heating
    
    while (medium_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      motorstart();//keeps motors running
      
      //keeps sensors running
       while ((firstcrackregistered == false && colorcorrect == false) || (firstcrackregistered == false && tempcorrect == false) || (colorcorrect == false && tempcorrect == false))
        {
          soundfirst();
          colormedium();
          tempmedium();
        }  

       //turns off sensors, motors and heating once conditions have been met
       if ((tempcorrect == true && firstcrackregistered == true) || (tempcorrect == true && colorcorrect == true) || (colorcorrect == true && firstcrackregistered == true)){
        digitalWrite(wire, LOW);
        digitalWrite(dir_pin1, LOW);
        digitalWrite(dir_pin2, LOW);
        analogWrite(temp_pwm, temp_off);
       }     
    }
  }
  
  if (dark_button_state == HIGH)
  {
    analogWrite(temp_pwm, temp_on);//turns on heating 
    
    while (dark_button_state == HIGH){ //keep button on
      digitalWrite(wire, HIGH); //turns on wire
      motorstart();//keeps motors running

      //regusters first crack before moving on to other sensors
      while (firstcrackregistered == false) 
        {
          soundfirst();
        }

        //calls all other sensors to start
        if (firstcrackregistered == true){
          while ((secondcrackregistered == false && colorcorrect == false) || (secondcrackregistered == false && tempcorrect == false) || (colorcorrect == false && tempcorrect == false)){
          soundsecond();
          colordark();
          tempdark();
        }
      }

      //turn off sensors, heating, motors once conditions have been met
      if ((tempcorrect == true && secondcrackregistered == true) || (tempcorrect == true && colorcorrect == true) || (colorcorrect == true && secondcrackregistered == true)){
        digitalWrite(wire, LOW);
        digitalWrite(dir_pin1, LOW);
        digitalWrite(dir_pin2, LOW);
        analogWrite(temp_pwm, temp_off);
      }
    }
  }
}
