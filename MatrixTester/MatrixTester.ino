typedef enum
{
  PIN_D2 = 0x2,
  PIN_D3,
  PIN_D4,
  PIN_D5,
  PIN_D6,
  PIN_D7,
  PIN_D8,
  PIN_A0 = 14,
  PIN_A1,
  PIN_A2,
  PIN_A3,
  PIN_A4,
  PIN_A5,
  PIN_A6
}PINS;

typedef enum
{
  ROW0 = 0x2,
  ROW1,
  ROW2,
  ROW3,
  ROW4,
  ROW5,
  ROW6,
  COL0 = 14,
  COL1,
  COL2,
  COL3,
  COL4,
  COL5,
  COL6 = 13
}ROWSANDCOLS;


void clearRows()
{
  byte i;
  for(i=0;i<7;i++)
  {
    digitalWrite(ROW0+i, LOW);
  }
}

void enableRow(byte row)
{
  byte i;
  
  for(i=0;i<7;i++)
  {
    if (i == row)
    {
      digitalWrite(ROW0+row, HIGH);
    }
    else
    {
      digitalWrite(ROW0+row, LOW);
    }
  }
}

void enableCol(byte col)
{
  byte i;
  
  for(i=0;i<7;i++)
  {
    if(i==col)
    {
      digitalWrite(COL0+col, HIGH);
    }
    else
    {
      digitalWrite(COL0+col, LOW);
    }
  }
}

void setup()
{ 
  byte i;
    Serial.begin(9600);
  
  for(i=0;i<7;i++)
  {
    pinMode(COL0+i, OUTPUT);
    pinMode(ROW0+i, OUTPUT);
  }    
 pinMode(COL6, OUTPUT);
} 

void clearMatrix()
{  
  digitalWrite(ROW0, LOW);
  digitalWrite(ROW1, LOW);
  digitalWrite(ROW2, LOW);
  digitalWrite(ROW3, LOW);
  digitalWrite(ROW4, LOW);
  digitalWrite(ROW5, LOW);
  digitalWrite(ROW6, LOW);
  
  // clear all the cols
  digitalWrite(COL0, LOW);
  digitalWrite(COL1, LOW);
  digitalWrite(COL2, LOW);
  digitalWrite(COL3, LOW);
  digitalWrite(COL4, LOW);
  digitalWrite(COL5, LOW);
  digitalWrite(COL6, LOW);
}

void loop() 
{ 
 byte row, col;
 const int delayTime = 50;


clearMatrix();

  delay(delayTime);
  
  // enable row 0
  digitalWrite(ROW0, HIGH);
  // enable cols one by one
  digitalWrite(COL0, HIGH);
  delay(delayTime/2);
  digitalWrite(COL1, HIGH);
  delay(delayTime/2);
  digitalWrite(COL2, HIGH);
  delay(delayTime/2);
  digitalWrite(COL3, HIGH);
  delay(delayTime/2);
  digitalWrite(COL4, HIGH);
  delay(delayTime/2);
  digitalWrite(COL5, HIGH);
  delay(delayTime/2);
  digitalWrite(COL6, HIGH);

  delay(delayTime);

  clearMatrix();

  // enable row 1
  digitalWrite(ROW1, HIGH);
  // enable cols one by one
  digitalWrite(COL0, HIGH);
  delay(delayTime/2);
  digitalWrite(COL1, HIGH);
  delay(delayTime/2);
  digitalWrite(COL2, HIGH);
  delay(delayTime/2);
  digitalWrite(COL3, HIGH);
  delay(delayTime/2);
  digitalWrite(COL4, HIGH);
  delay(delayTime/2);
  digitalWrite(COL5, HIGH);
  delay(delayTime/2);
  digitalWrite(COL6, HIGH);

  delay(delayTime);

  clearMatrix();

  // enable row 2
  digitalWrite(ROW2, HIGH);
  // enable cols one by one
  digitalWrite(COL0, HIGH);
  delay(delayTime/2);
  digitalWrite(COL1, HIGH);
  delay(delayTime/2);
  digitalWrite(COL2, HIGH);
  delay(delayTime/2);
  digitalWrite(COL3, HIGH);
  delay(delayTime/2);
  digitalWrite(COL4, HIGH);
  delay(delayTime/2);
  digitalWrite(COL5, HIGH);
  delay(delayTime/2);
  digitalWrite(COL6, HIGH);

  delay(delayTime);

  clearMatrix();

  // enable row 3
  digitalWrite(ROW3, HIGH);
  // enable cols one by one
  digitalWrite(COL0, HIGH);
  delay(delayTime/2);
  digitalWrite(COL1, HIGH);
  delay(delayTime/2);
  digitalWrite(COL2, HIGH);
  delay(delayTime/2);
  digitalWrite(COL3, HIGH);
  delay(delayTime/2);
  digitalWrite(COL4, HIGH);
  delay(delayTime/2);
  digitalWrite(COL5, HIGH);
  delay(delayTime/2);
  digitalWrite(COL6, HIGH);

  delay(delayTime);

  clearMatrix();

  // enable row 4
  digitalWrite(ROW4, HIGH);
  // enable cols one by one
  digitalWrite(COL0, HIGH);
  delay(delayTime/2);
  digitalWrite(COL1, HIGH);
  delay(delayTime/2);
  digitalWrite(COL2, HIGH);
  delay(delayTime/2);
  digitalWrite(COL3, HIGH);
  delay(delayTime/2);
  digitalWrite(COL4, HIGH);
  delay(delayTime/2);
  digitalWrite(COL5, HIGH);
  delay(delayTime/2);
  digitalWrite(COL6, HIGH);

  delay(delayTime);

  clearMatrix();
  
    // enable row 5
  digitalWrite(ROW5, HIGH);
  // enable cols one by one
  digitalWrite(COL0, HIGH);
  delay(delayTime/2);
  digitalWrite(COL1, HIGH);
  delay(delayTime/2);
  digitalWrite(COL2, HIGH);
  delay(delayTime/2);
  digitalWrite(COL3, HIGH);
  delay(delayTime/2);
  digitalWrite(COL4, HIGH);
  delay(delayTime/2);
  digitalWrite(COL5, HIGH);
  delay(delayTime/2);
  digitalWrite(COL6, HIGH);

  delay(delayTime);

  clearMatrix();
  
    // enable row 6
  digitalWrite(ROW6, HIGH);
  // enable cols one by one
  digitalWrite(COL0, HIGH);
  delay(delayTime/2);
  digitalWrite(COL1, HIGH);
  delay(delayTime/2);
  digitalWrite(COL2, HIGH);
  delay(delayTime/2);
  digitalWrite(COL3, HIGH);
  delay(delayTime/2);
  digitalWrite(COL4, HIGH);
  delay(delayTime/2);
  digitalWrite(COL5, HIGH);
  delay(delayTime/2);
  digitalWrite(COL6, HIGH);

  delay(delayTime);

  clearMatrix();
  delay(delayTime);

 
 
 
 
 
 
 
 
 
 
 /*
 clearRows();
 Serial.println("Clearing the Rows");
 delay(delayTime);
 
 for(row=0;row<7;row++)
 {
   enableRow(row);
   for(col=0;col<7;col++)
   {
     Serial.print("row");
     Serial.print(row);
     Serial.print(" col");
     Serial.println(col);
     enableCol(col);
     delay(delayTime);
   }   
 }
*/

}

