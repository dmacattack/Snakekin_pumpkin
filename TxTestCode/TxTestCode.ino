// sender - UNO

int pushButton = 3; // D3?


void setup()
{
  Serial.begin(2400);
  pinMode(pushButton, INPUT);
}

void loop()
{
  int buttonState = digitalRead(pushButton);
  
  //Serial.print("ButtonState = ");
  //Serial.print(buttonState);

  if(buttonState == HIGH)
  {
    Serial.print('A');
  }
  else
  {
    Serial.print('a');
  }
    
  delay(2000);
  
  
  /*
  if (buttonState = HIGH)
  {
Serial.println("button = high");    
//  Serial.println(0xDEADBEEF);  

  }
  else
  Serial.println("button = low");
  
  delay(2000);  
  */
}
