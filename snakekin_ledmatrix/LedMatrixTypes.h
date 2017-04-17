#define MATRIX_SIZE 7

typedef enum
{
  ROW0 = 0x2, //D2
  ROW1, //D3
  ROW2, //D4
  ROW3, //D5
  ROW4, //D6
  ROW5, //D7
  ROW6, //D8
  COL0 = 13, //A0
  COL1, //A1
  COL2, //A2
  COL3, //A3
  COL4, //A4
  COL5, //A5
  COL6 //D13
}ROWSANDCOLS;

typedef enum
{
  MASKCOL0 = 0x01,
  MASKCOL1 = 0x02, 
  MASKCOL2 = 0x04, 
  MASKCOL3 = 0x08, 
  MASKCOL4 = 0x10,
  MASKCOL5 = 0x20, 
  MASKCOL6 = 0x40
} COLMASKS;

typedef enum
{
  STATE0,
  STATE1,
  STATE2,
  STATE3,
  STATE4,
  STATE5, 
  STATE6,
  STATE7
}STATES;

