const int BUTTON = 2; //set button pin
const int WIRE = 3; //set wire pin
int BUTTONstate = 0; //pushed or not

void setup()
{
  pinMode(BUTTON, INPUT); //nothing happens until pushed
  pinMode(WIRE, OUTPUT); //result of button pushed
}

void loop()
{
  BUTTONstate = digitalRead(BUTTON); //read state
  if (BUTTONstate == HIGH) //if pushed
  {
    while (BUTTONstate == HIGH){//keep pin on
    digitalWrite(WIRE, HIGH);
    
    }
  } 
  else{
    digitalWrite(WIRE, LOW); //nothing occurs
  }
}
