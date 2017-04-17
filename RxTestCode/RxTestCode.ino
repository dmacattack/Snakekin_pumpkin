//receiver - NANO
typedef enum
{
  BTN_UP = 'A',
  BTN_DN = 'C',
  BTN_LEFT = 'E',
  BTN_RIGHT = 'G'
}BUTTON_DIRECTIONS;
void setup()
{
  Serial.begin(2400);
}

void loop()
{
  int inByte;
  
  if (Serial.available()) 
  {
    inByte = Serial.read();
    

    if(inByte ==BTN_UP)
    {
      Serial.println("Button UP");
    }
    // Serial.println(inByte);
 
  }


}
