// -------------------Useful Variables ------------------------
byte LedMatrix[MATRIX_SIZE]; // LED matrix
byte AppleMatrix[MATRIX_SIZE] ={0, 16, 0, 0, 0, 0, 0}; // dummy apple location
byte arrRowPins[7] = {ROW0, ROW1, ROW2, ROW3, ROW4, ROW5, ROW6 };
byte arrColPins[7] = {COL0, COL1, COL2, COL3, COL4, COL5, COL6 };


// --------------------function prototypes ---------------------

void enableRow(byte rowIdx);
void clearRows();
void printMatrix();
byte bitXOR(byte x, byte y);
void toggleApples();

// --------------------functions--------------------------------

// global
// byte LedMatrix[7] // 7x7 led matrix
// byte AppleMatrix[7] // matrix indicating where the apple is and toggle it respectively

/* 
 * bitXOR
 * XORs bytes x & y and returns them
 * 
 * x = first arg to XOR
 * y = second arg to XOR
 * returns the XORd bytes
 */
byte bitXOR(byte x, byte y)
{
    return (~x | ~y) & (x | y);
}


/* 
 * toggleApples
 * This function reads from the Apple Matrix and toggles the location of the apple in the LED matrix
 * to give it a "flashing" appearance. This function is called every X ms with a timer to control the blinking
 */
void toggleApples()
{
  byte i;
  static byte appleDutyCycle = 1; // when to toggle during the count. currently 50% duty cycle
  static byte appleCount = 0;     // counting variable
  byte appleDutyLimit = 1;        // counts from 0 to Limit

  if (appleCount == appleDutyLimit)
  {
    for(i=0;i<MATRIX_SIZE;i++)
    {
      LedMatrix[i] = bitXOR(LedMatrix[i],AppleMatrix[i]); // XOR the bit vectors together causes the bits to toggle :)
    }
    appleCount = 0;
  }
  else
  {
    appleCount++;
  }

}


// printMatrix prints the byte array matrix to the LEDs
/*
void printMatrix()
{
    static byte matrixRowIdx = 0; // static to remove from global
   //TODO: find out these functions and how to use
   // row write PORT(row << x)

   // col write PORT((ledMatrix[row] & B01111111 ))
   // row++
}
*/

/*
 * printMatrix
 * This function prints out the matrix to the LEDs
 */
void printMatrix()
{
  static byte row =0;

  enableRow(row);
    
  digitalWrite(COL0, (LedMatrix[row]) & 0x1 );
  digitalWrite(COL1, (LedMatrix[row] >> 1) & 0x1 );
  digitalWrite(COL2, (LedMatrix[row] >> 2) & 0x1 );
  digitalWrite(COL3, (LedMatrix[row] >> 3) & 0x1 );
  digitalWrite(COL4, (LedMatrix[row] >> 4) & 0x1 );
  digitalWrite(COL5, (LedMatrix[row] >> 5) & 0x1 );
  digitalWrite(COL6, (LedMatrix[row] >> 6) & 0x1 );
    
  if(row <MATRIX_SIZE)
  {
    row++;
  }
  else
  {
    row =0;
  }
}




/*
 * clearRows
 * This function writes 0 to all the rows of the matrix, clearing all the rows
 */
void clearRows()
{
  byte i;
  for(i=0; i<MATRIX_SIZE; i++)
  {
    digitalWrite(arrRowPins[i], LOW);
  }
}

/*
 * enableRow
 * This function disables all rows, except the index passed to it
 *
 * row = row index to enable
 */
void enableRow(byte row)
{
  byte i;
  
  for(i=0; i<MATRIX_SIZE; i++)
  {
    if (i==row)
    {
      digitalWrite(arrRowPins[i], HIGH);
    }
    else
    {
      digitalWrite(arrRowPins[i], LOW);
    }
  }
}
