#include <SimpleTimer.h>
#include "LedMatrixTypes.h"
#include "LedTestAnimation.h"
#include "LedMatrixMethods.h"

SimpleTimer gameTimer;   // create the game timer 
SimpleTimer matrixTimer; // create the LED matrix updater
SimpleTimer appleTimer;  // create the apple matrix updater

int stateMachineInterval = 1000; // how often to update the fake state machine
int matrixInterval = 3; // how often to update the LED matrix. Tweak this to change how the LEDs are displayed
int appleInterval = 50; // how often to update the apples to show the blinking effect

/*
 * statemachine
 * Fake state machine to test the LED matrix with animations
 */
void statemachine()
{
  byte i;
  static STATES states = STATE0;

  switch(states)
  {
    case STATE0: // draw nothing to the matrix
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = 0; // clears the matrix
      }
      states = STATE1;  
      break;
    case STATE1:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = barAnimation[0][i]; 
      }
      states = STATE2;
      break;
    case STATE2:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = barAnimation[1][i]; 
      }
      states = STATE3;
      break;
    case STATE3:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = barAnimation[2][i]; 
      }
      states = STATE4;
      break;
    case STATE4:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = barAnimation[3][i]; 
      }
      states = STATE5;
      break;  
    case STATE5:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = barAnimation[4][i]; 
      }
      states = STATE6;
      break;  
    case STATE6:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = barAnimation[5][i]; 
      }
      states = STATE7;
      break;  
    case STATE7:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = barAnimation[6][i]; 
      }
      states = STATE0;
      break;        
    default:
      break;
  }
}


void setup()
{ 
  byte i;
  for(i=0; i<MATRIX_SIZE; i++)
  {
    pinMode(arrColPins[i], OUTPUT);
    pinMode(arrRowPins[i], OUTPUT);
  }
  
  clearRows();
  
  gameTimer.setInterval(stateMachineInterval, statemachine); // set the timer interval
  matrixTimer.setInterval(matrixInterval, printMatrix);   
  appleTimer.setInterval(appleInterval, toggleApples);
} 


void loop() 
{ 
gameTimer.run();
matrixTimer.run();
//appleTimer.run();
}

