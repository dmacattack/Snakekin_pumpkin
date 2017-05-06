#define MATRIX_SIZE 7

typedef enum
{
  ROW0 = 0x0,
  ROW1 = 0x3,
  ROW2,
  ROW3,
  ROW4,
  ROW5,
  ROW6,
  COL0 = 13,
  COL1,
  COL2,
  COL3,
  COL4,
  COL5,
  COL6
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
  STATE6
}STATES;

