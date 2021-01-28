#include <Wire.h>
#include "TCS34725.h"
//#include "colorcode"

/* Pushbutton */
const int buttonlight = 2;   // pushbutton for light roast
const int buttonmedium = 3;  // pushbutton for medium roast
const int buttondark = 4;    // pushbutton for dark roast
const int buttoncool = 5;    // pushbutton for cool down
/* Pushbutton End */


/* Color Sensor */
// Initialise with specific int time and gain values
TCS34725 tcs = TCS34725(INTEGRATIONTIME_700MS, GAIN_1X);

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


/* Sound Sensor */
int CrackSensor = A1; // assigns crack sensor circuit to analog pin 1.
int FirstCrack = 3; // assigns output signal for first crack to digital pin 3.
int SecondCrack = 4; //assigns output signal for second crack to digital pin 4.
bool firstcrackregistered = false; // boolean that is set to true once the coffee roasting process is in the "First crack stage".
bool secondcrackregistered = false; // boolean that is set to true once the coffee roasting process is in the "Second crack stage".
int crackcount = 0; //integer value to count for number of crack sounds.
int secondcrackcount = 0; //integer value to count for number of crack sounds at second crack.
/* Sound Sensor End */


void setup() {
  /*  Pushbutton Set Up */
  // Set up the pushbutton pins to be an input
  pinMode(buttonlight, INPUT);
  pinMode(buttonmedium, INPUT);
  pinMode(buttondark, INPUT);
  pinMode(buttoncool, INPUT);
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
  pinMode (CrackSensor, INPUT); // sets crack sensor as input.
  Serial.begin(9600); // this is test code that allows input for crack sensor to be printed for testing.
  pinMode (FirstCrack, OUTPUT);// sets firstcrack signal as output.
  pinMode (SecondCrack, OUTPUT); // sets secondcrack signal as output.
  /* Sound Sensor Set Up End */
}

void loop(void) {
  int buttonLstate, buttonMstate, buttonDstate, buttonCstate;  // pushbutton states variables
  int colorcorrect, soundcorrect;
  
  buttonLstate = digitalRead(buttonlight);
  buttonMstate = digitalRead(buttonmedium);
  buttonDstate = digitalRead(buttondark);
  buttonCstate = digitalRead(buttoncool);

  coffeebeansdetected();

  if (buttonLstate == LOW)
  { 
    colorlight();
    soundlight();
    if (colorcorrect == 1 || soundcorrect = 1)
    {
      ______
    }
    else
    {
      delay(5000);
      colorlight();
    }
  }
  else if (buttonMstate == LOW)
  {
    colormedium();
    soundmedium();
    if (colorcorrect == 1)
    {
      ______
    }
    else
    {
      delay(5000);
      colormedium();
    }
  }
  else if (buttonDstate == LOW)
  {
    colordark();
    sounddark();
    if (colorcorrect == 1 )
    {
      ______
    }
    else
    {
      delay(5000);
      colordark();
    }
  }
  else if (buttonCstate == LOW)
  {

  }
  else
  {
    delay(5000);
  }
}


/* Color Sensor Functions */
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

/* Sound Sensor Functions */
/* Sound Sensor Functions End */
