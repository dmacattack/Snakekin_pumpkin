#include <Bounce.h>
#include <IRremote.h>

typedef enum
{
  IR_CMD_UP = 0xa90,
  IR_CMD_DN = 0xb90,
  IR_CMD_LEFT = 0xc90,
  IR_CMD_RIGHT = 0xd90,
}IR_CMDS;

typedef enum
{
  BTN_UP = 6,
  BTN_DN = 7,
  IR_RX = 4,
  IR_TX = 3 // it must be a pwm pin 3
}PINS;

IRsend irSend;

int mBTN_UP = 2;
int mBTN_DN = 12;
int mBTN_LEFT = 4;
int mBTN_RIGHT = 5;

int NUM_BUTTONS = 4;
int debounceDelay = 100;

int buttons[] = {mBTN_UP, mBTN_DN, mBTN_LEFT, mBTN_RIGHT};

// create the Bounce objects for each button
Bounce upBounce = Bounce(mBTN_UP, debounceDelay);
Bounce dnBounce = Bounce(mBTN_DN, debounceDelay);
Bounce leftBounce = Bounce(mBTN_LEFT, debounceDelay);
Bounce rightBounce = Bounce(mBTN_RIGHT, debounceDelay);

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
    irSend.sendSony(IR_CMD_UP, 12);
  }
  
  btnReading = dnBounce.fallingEdge();
  if (btnReading == true)
  {
    Serial.println("Button DOWN");
    irSend.sendSony(IR_CMD_DN, 12);
  }
  
  btnReading = leftBounce.fallingEdge();
  if (btnReading == true)
  {
    Serial.println("Button LEFT");
    irSend.sendSony(IR_CMD_LEFT, 12);
  }
 
  btnReading = rightBounce.fallingEdge();
  if (btnReading == true)
  {
    Serial.println("Button RIGHT");
    irSend.sendSony(IR_CMD_RIGHT, 12);
  }

}




