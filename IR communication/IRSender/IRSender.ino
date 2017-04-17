// IR test
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

// create the IR objects
IRsend irSend;


void setup()
{
  Serial.begin(9600); // debugging

  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DN, INPUT);
}


void loop()
{
  
  // send something
  delay(2000);
  irSend.sendSony(IR_CMD_UP, 12); 
  Serial.println(">> BUTTON UP ");
  
  delay(2000);
  irSend.sendSony(IR_CMD_DN, 12); 
  Serial.println(">> BUTTON DOWN ");
  
  delay(2000);
  irSend.sendSony(IR_CMD_LEFT, 12); 
  Serial.println(">> BUTTON LEFT ");
  
  delay(2000);
  irSend.sendSony(IR_CMD_RIGHT, 12); 
  Serial.println(">> BUTTON RIGHT ");

}
