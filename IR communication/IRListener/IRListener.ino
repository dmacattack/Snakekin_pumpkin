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
  IR_RX = 2, // 
}PINS;

int led = 0; // debug


// create the IR objects
IRrecv irRecv(IR_RX);

decode_results results;

void translateIrCmd(unsigned int cmd)
{
  switch(cmd)
  {
    case IR_CMD_UP:
      //Serial.println(" MOVE UP ");
      digitalWrite(led, HIGH);
      break;
    case IR_CMD_DN:
      //Serial.println(" MOVE DOWN ");
      break;
    case IR_CMD_LEFT:
      //Serial.println(" MOVE LEFT");
      digitalWrite(led, LOW);
      break;
    case IR_CMD_RIGHT:
      //Serial.println(" MOVE RIGHT ");
      break;
    //default:
      //Serial.print("unknown cmd: ");
      //Serial.println(cmd, HEX);
  }
}


void setup()
{
  //Serial.begin(9600); // debugging
  irRecv.enableIRIn(); // Start the receiver
  pinMode(led, OUTPUT);
}

void loop()
{
  //Serial.println("Starting IR decoding ");
  
  while(1)
  {
  // receive stuff if its there
  if (irRecv.decode(&results))
  {
//    Serial.print("IR READ: ");
//    Serial.println(results.value,HEX);
    translateIrCmd(results.value);
    irRecv.resume(); // receive next value
  }
  }

}
