#include <Bounce.h>

int BTN_UP = 2;
int BTN_DN = 3;
int BTN_LEFT = 4;
int BTN_RIGHT = 5;
int NUM_BUTTONS = 4;
int debounceDelay = 100;
int buttons[] = {BTN_UP, BTN_DN, BTN_LEFT, BTN_RIGHT};

// create the Bounce objects for each button
Bounce upBounce = Bounce(BTN_UP, debounceDelay);
Bounce dnBounce = Bounce(BTN_DN, debounceDelay);
Bounce leftBounce = Bounce(BTN_LEFT, debounceDelay);
Bounce rightBounce = Bounce(BTN_RIGHT, debounceDelay);

void setup()
{
  Serial.begin(9600);  
  int i;
  
  // set the pins to input, with a pullup resistor
  for(i=0;i<NUM_BUTTONS;i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);    
  }
  
}

void loop()
{
 upBounce.update();
 dnBounce.update();
 leftBounce.update();
 rightBounce.update();
 
  boolean btnReading = upBounce.fallingEdge();
  if (btnReading == true)
  {
    Serial.println("Button UP");
  }
  
  btnReading = dnBounce.fallingEdge();
  if (btnReading == true)
  {
    Serial.println("Button DOWN");
  }
  
  btnReading = leftBounce.fallingEdge();
  if (btnReading == true)
  {
    Serial.println("Button LEFT");
  }
 
  btnReading = rightBounce.fallingEdge();
  if (btnReading == true)
  {
    Serial.println("Button RIGHT");
  }

}




