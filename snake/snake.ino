#include <IRremote.h>
#include <SimpleTimer.h>
#include "LedMatrixTypes.h"
#include "LedTestAnimation.h"
#include "LedMatrixMethods.h"

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

typedef enum direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 3,
	RIGHT = 4,
	NEW_PIECE = 5,
	UNDEFINED = -1
};

#define MAX_SIZE 49
#define ROW_SIZE MATRIX_SIZE
#define MOVE_TIMER 1000

IRrecv irRecv(IR_RX);

SimpleTimer moveTimer;
SimpleTimer matrixTimer; // create the LED matrix updater
SimpleTimer appleTimer;  // create the apple matrix updater

int matrixInterval = 3; // how often to update the LED matrix. Tweak this to change how the LEDs are displayed
int appleInterval = 50; // how often to update the apples to show the blinking effect

static byte matrix[ROW_SIZE][ROW_SIZE]; //holds the entire matrix

static byte xList[MAX_SIZE]; //list of x and y coordinates for the snake
static byte yList[MAX_SIZE];

static int currX=0; //the head of the snake
static int currY=0;

static int currSize = 1;

static direction currDir = UNDEFINED;

static boolean moved = false; //if the move was valid
static boolean gameOver = true;

static int states = 0;

decode_results results;
char joykinput[2] = "";

void setup()
{                 
        setupPins(); //set the LED pins
        
//        Serial.begin(9600); //debug, need to disable for production
        //setup the IR receiver
        irRecv.enableIRIn();
        pinMode(IR_RX, INPUT);
        
        clearRows(); //clear the screen
        
        resetGame(); //reset all of the game variables
        
        //start the timers that govern the display and movement
        moveTimer.setInterval(MOVE_TIMER, receiveWireless);
        matrixTimer.setInterval(matrixInterval, printMatrix);   
        appleTimer.setInterval(appleInterval, toggleApples);
}

void setupPins()
{
  byte i;
  //loop through and set all the rows and columns as output
  for(i=0; i<MATRIX_SIZE; i++)
  {
    pinMode(arrColPins[i], OUTPUT);
    pinMode(arrRowPins[i], OUTPUT);
  }
  
}

void loop()
{
  //just run the timers, they take care of everything
    moveTimer.run();
    matrixTimer.run();
    appleTimer.run();
}

void receiveWireless()
{
  if(gameOver == true)
  {
    //this displays the SNAKE animation 
    snakeMachine();
  }
  else if(currSize == MAX_SIZE)
  {
    //its a gameover, the user wins
     gameOver = true;
     return;
  }
  else if(irRecv.decode(&results))
  {
    //this receives the IR transmission and translates it to a movement
//    Serial.println("IR READ");
    switch(results.value)
    {
    case IR_CMD_UP:
//      Serial.println(" MOVE UP ");
      if(currDir != DOWN)
      {
        currDir = UP;
      }
      break;
    case IR_CMD_DN:
//      Serial.println(" MOVE DOWN ");
      if(currDir != UP)
      {
        currDir = DOWN;
      }
      break;
    case IR_CMD_LEFT:
//      Serial.println(" MOVE LEFT");
      if(currDir != RIGHT)
      {
        currDir = LEFT;
      }
      break;
    case IR_CMD_RIGHT:
//      Serial.println(" MOVE RIGHT ");
      if(currDir != LEFT)
      {
        currDir = RIGHT;
      }
      break;
    default:
//      Serial.print("unknown cmd: ");
    break;
    }
    irRecv.resume();
  }
  moveSnake();
}

//void serialEvent()
//{
//   while(Serial.available() > 0)
//   {
//    String input = "";
//    char readVal = Serial.read();
//    input += readVal;
//    if(input == "w" ||
//      input == "a" ||
//      input == "s" ||
//      input == "d")
//      {
//        input.toCharArray(joykinput, 2);
//        Serial.println(joykinput);
//      }
//   }
//}
//void input()
//{
//        if(gameOver == true)
//        {
//          snakeMachine();
//        }
//	else if(currSize == MAX_SIZE)
//	{
//		gameOver = true;
//                return;
//	}
//	else if(strcmp(joykinput, "w") == 0)
//	{
//	  currDir = UP;
//	}
//	else if(strcmp(joykinput, "a") == 0)
//	{
//	  currDir = LEFT;
//	}
//	else if(strcmp(joykinput, "s") == 0)
//	{
//	  currDir = DOWN;
//	}
//	else if(strcmp(joykinput, "d") == 0)
//	{
//	  currDir = RIGHT;
//	}
//
//	moveSnake();
//}

void moveSnake()
{
	direction dir = currDir;
	moved = false;
	switch(dir)
	{
	case UP:
		if(currX-1 != -1)
		{
			//this is a valid move
			currX-=1;
			moved = true;
		}
		else
		{
			//this means that we hit a wall
		}
		break;
        case LEFT:
		if(currY-1 != -1)
		{
			currY-=1;
			moved = true;
		}
		break;
        case DOWN:
		if(currX+1 < ROW_SIZE)
		{
			currX+=1;
			moved = true;
		}
		break;
	case RIGHT:
		if(currY+1 < ROW_SIZE)
		{
			currY+=1;
			moved = true;
		}
		break;
	}
	if(moved)
	{
		if(matrix[currX][currY] == 2)
		{
			//special handeling if we find a new piece;
			currSize += 1;
			xList[currSize-1] = currX;
			yList[currSize-1] = currY;
			matrix[xList[currSize-1]][yList[currSize-1]] = 1;
			generateNewPiece();
		}
		else
		{
			int oldX = 0;
			int oldY = 0;
			for(int i = 0; i < currSize; i++)
			{
				oldX = xList[i];
				oldY = yList[i];
				int newDir = sorroundings(i, dir);
				if(newDir != UNDEFINED)
				{
					if(i == 0)
					{
						//reset the old one
						matrix[xList[i]][yList[i]] = 0;
					}
					switch(newDir)
					{
					case RIGHT:
						matrix[xList[i]][yList[i]+1] = 1;
						yList[i] = yList[i]+1;
						xList[i] = oldX;
						break;
					case LEFT:
						matrix[xList[i]][yList[i]-1] = 1;
						yList[i] = yList[i]-1;
						xList[i] = oldX;
						break;
					case UP: 
						matrix[xList[i]-1][yList[i]] = 1;
						xList[i] = xList[i]-1;
						yList[i] = oldY;
						break;
					case DOWN:
						matrix[xList[i]+1][yList[i]] = 1;
						xList[i] = xList[i]+1;
						yList[i] = oldY;
						break;
					}
				}
				else
				{
					//they fucked up and lost, undefined means
					//that there was contact with a wall or the snakes body
					gameOver = true;
				}
			}
		}
		updateDisplay();
                convertToByteArray();
	}
	else
	{
		gameOver = true;
	}
}

int sorroundings(int idx, int dir)
{
	int returnVal = UNDEFINED;
	if(idx == currSize-1)
	{
		//we need special handling for the head.
		//if its next movement is the body, its game over
		switch(dir)
		{
		case UP:
			if(matrix[xList[idx]-1][yList[idx]] == 1)
			{
				//we hit the body of the snake
				//game over
				return UNDEFINED;
			}
			else
				return dir;
			break;
		case DOWN:
			if(matrix[xList[idx]+1][yList[idx]] == 1)
			{
				return UNDEFINED;
			}
			else
				return dir;
			break;
		case LEFT:
			if(matrix[xList[idx]][yList[idx]-1] == 1)
			{
				return UNDEFINED;
			}
			else
				return dir;
			break;
		case RIGHT:
			if(matrix[xList[idx]][yList[idx]+1] == 1)
			{
				return UNDEFINED;
			}
			else
				return dir;
			break;
		default:
			return UNDEFINED;
			break;
		}
	}
	int newX = xList[idx+1];
	int newY = yList[idx+1];
	if(newX > xList[idx])
		return DOWN;
	else if(newX < xList[idx])
		return UP;
	else if(newY < yList[idx])
		return LEFT;
	else
		return RIGHT;
		
}

void generateNewPiece()
{
	boolean goodPOS = false;
	while (!goodPOS)
	{
		int newPiecePOS = random(1, MAX_SIZE);
		//int newPiecePOS = std::rand() % 36;
		int row = 0;
		//now we need to associate the number with an x and y
		if(newPiecePOS <=ROW_SIZE)
		{
			row = 0;
		}
		//figure out which row its in to avoid looping over 
		//the entire array
		else if(newPiecePOS >= 8 && newPiecePOS <= 14)
		{
			row = 1;
		}
		else if(newPiecePOS >= 15 && newPiecePOS <= 21)
		{
			row = 2;
		}
		else if(newPiecePOS >= 22 && newPiecePOS <= 28)
		{
			row = 3;
		}
		else if(newPiecePOS >= 29 && newPiecePOS <= 35)
		{
			row = 4;
		}
		else if(newPiecePOS >= 36 && newPiecePOS <= 42)
		{
			row = 5;
		}
                else if(newPiecePOS >= 43 && newPiecePOS <= 49)
                {
                        row = 6;
                }
		//now that we got the row, get the offset
		//ROW_SIZE*ROW - newPiece gives us the distance from the right
		//subtract that from the row size to get the offset from the left
		//int offset = ROW_SIZE - ((ROW_SIZE*row) - newPiecePOS);
		int offset = newPiecePOS % ROW_SIZE;
		if(matrix[row][offset] == 1)
		{
			continue;
		}
		else
		{
			//newPieceX = row;
			//newPieceY = offset;
			matrix[row][offset] = 2;
			goodPOS = true;
                        //memset(AppleMatrix, 0, MATRIX_SIZE);
                        //AppleMatrix[row] = offset << (ROW_SIZE - offset);
      		}
	}
}

void updateDisplay()
{
	for(int i = 0; i<ROW_SIZE; i++)
	{
                char printVal[10];
                sprintf(printVal, "%d %d %d %d %d %d %d", matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3], matrix[i][4], matrix[i][5], matrix[i][6]);
//		Serial.println(printVal);
	}
//	Serial.println("***************************************"); 
}

void resetGame()
{
	currDir = RIGHT;
	currSize = 1;
	currX = 0;
	currY = 0;
	memset(yList, 0, MAX_SIZE);
	memset(xList, 0, MAX_SIZE);
        memset(matrix, 0, MAX_SIZE);
        
        matrix[currX][currY]=1;
	generateNewPiece();
	updateDisplay();
        convertToByteArray();
        states = STATE0;
        gameOver = false;        
}

void convertToByteArray()
{
  byte converted[ROW_SIZE];
  memset(converted, 0, ROW_SIZE);
   for(int i = 0; i<ROW_SIZE; i++)
   {
     int rowVal = 0;
     for(int j = 0; j<ROW_SIZE; j++)
     {
       if(matrix[i][j] == 2)
       {
         memset(AppleMatrix, 0, MATRIX_SIZE);
         AppleMatrix[i] = 1 << ((ROW_SIZE-1) - j);
         continue;
       }
       rowVal += (matrix[i][j] << ((ROW_SIZE-1) - j));
     }
     converted[i] = rowVal;
   }
   char printVal[20];
   memset(printVal, 0, ROW_SIZE);
   sprintf(printVal, "%d %d %d %d %d %d %d", converted[0], converted[1], converted[2], converted[3], converted[4], converted[5], converted[6]);
//   Serial.println(printVal);
   
   for(int i = 0; i<ROW_SIZE; i++)
   {
     LedMatrix[i] = converted[i];
   }
}

void snakeMachine()
{
  byte i;
   switch(states)
  {
    case STATE0: // draw nothing to the matrix
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = 0; // clears the matrix
        
      }
      memset(AppleMatrix, 0, MATRIX_SIZE);
      states = STATE1;  
      break;
    case STATE1:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = SnakeAnimation[0][i]; 
      }
      states = STATE2;
      break;
    case STATE2:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = SnakeAnimation[1][i]; 
      }
      states = STATE3;
      break;
    case STATE3:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = SnakeAnimation[2][i]; 
      }
      states = STATE4;
      break;
    case STATE4:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = SnakeAnimation[3][i]; 
      }
      states = STATE5;
      break;  
    case STATE5:
      for(i=0;i<MATRIX_SIZE;i++)
      {
        LedMatrix[i] = SnakeAnimation[4][i]; 
      }
      states = STATE6;
      break;
      case STATE6:
        resetGame();
      break;  
    default:
      break; 
  }
}

