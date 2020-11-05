#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
///////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> // bool, true, false
#include<math.h>    // round
#include<time.h>    // time
#include<conio.h>   //
#include<windows.h> // Sleep, cls(). On Unix include unistd.h
#include<WinCon.h> // get and SetConsoleCursorInfo (for making it visible or not)
///////////////////////////////////////////////////////////////////////////////
// function declarations
void setup(void);
void draw(void);
void input(void);
void logic(void);
void cls(void);
void update(void);
void setCursorPosition(int, int);
void show_cursor(bool);
///////////////////////////////////////////////////////////////////////////////
// global variable declarations
bool gameover;
const int width = 80;
const int height = 40;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirection dir;
int fruitx, fruity, score, x, x_old, y, y_old = 0;
int minx, miny = 2;
int maxx = width - 1;
int maxy = height - 1;
CONSOLE_CURSOR_INFO cursor;
///////////////////////////////////////////////////////////////////////////////
// MAIN
int main(){
  show_cursor(false); // stop showing the cursor
  // Display splash screen
  cls();
  setCursorPosition(round(width/2), round(height/2));
  printf("Snake Game");
  Sleep(2000);

  // Get the board ready
  cls();
  setup();
  draw();

  while (!gameover) {
    input();
    logic();
    update();
    Sleep(100); // on windows sleep(1000) to sleep 1 sec
    // on unix enter sleep(1) to sleep 1 second
  }

  // Display game over
  cls();
  setCursorPosition(round(width/2), round(height/2));
  printf("Game Over");
  Sleep(2000);
  cls();
  show_cursor(true);
  return 0;
}// end of main
///////////////////////////////////////////////////////////////////////////////
// SETUP
void setup(){
  // allows us to enter the while loop and play the game
  gameover = false;
  dir = STOP;

  // start in the middle
  x = round(width/2);
  y = round(height/2);

  // set fruit position randomly
  srand((unsigned) time(0)); // use current time as seed
  fruitx = rand() % (maxx - minx + 1) + minx;
  fruity = rand() % (maxy - miny + 1) + miny;

} // end setup
///////////////////////////////////////////////////////////////////////////////
// DRAW
void draw(){
  //system("cls"); // clear the terminal window

  // top border
  for (int i = 0; i < width + 2; i++){
    printf("#");
  }
  printf("\n");

  // drawing the map
  for (int j = 0; j < height; j++){
    for (int i = 0; i < width; i++){
      // left border
      if (i == 0){
        printf("#");
      }
      // center area
      if (i == (fruitx - 1) && j == (fruity - 1)){ // minus 1s account for difference between draw and update
        printf("F");
      }
      else {
        printf(" ");
      }
      // right border
      if (i == width - 1)
      printf("#");
    } // end width loop

    printf("\n");
  } // end height loop

  // bottom border
  for (int i = 0; i < width + 2; i++){
    printf("#");
  }
  printf("\n");

  // Instructions
  printf("W = move up  A = move left  S = move down  D = move right\n"); // (height + 1) + 1
  printf("(Press X to end the game.)\n"); // (height + 1) + 2
  // score board
  printf("Score: %d\n", score); // (height + 1) + 3


} // end draw
///////////////////////////////////////////////////////////////////////////////
// INPUT
void input(){
  if (_kbhit()){
    switch (_getch()) {
      case 'a':
        dir = LEFT;
        break;
      case 'd':
        dir = RIGHT;
        break;
      case 'w':
        dir  = UP;
        break;
      case 's':
        dir = DOWN;
        break;
      case 'x':
        gameover = true;
        break;
    } // end switch
  } // end if kbhit
}// end input function
///////////////////////////////////////////////////////////////////////////////
// LOGIC
void logic(){
  x_old = x;
  y_old = y;
  switch (dir) {
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
    case UP:
      y--;
      break;
    case DOWN:
      y++;
      break;
    default:
      break;
  }
}// end logic
///////////////////////////////////////////////////////////////////////////////
// Update
void update() {
  // x is the column, y is the row. The origin (0,0) is top-left.
  // Remove the old snake
  setCursorPosition(x_old, y_old);
  printf(" ");
  // Check to see if the snake is still on the map
  if ((x < 1 | (x > width - 1) ) | (y < 1 | (y > height - 1) )) {
    gameover = true;
  } else {
    // Place the snake's head
    setCursorPosition(x, y);
    printf("S");
    // Place the snake's tail
    // TODO: write tail code

    // If snake's head is at fruit location, increase score and move fruit
    if (x == fruitx & y == fruity) {
      fruitx = rand() % (maxx - minx + 1) + minx;
      fruity = rand() % (maxy - miny + 1) + miny;
      setCursorPosition(fruitx, fruity);
      printf("F");
      score++;
      setCursorPosition(0, (height + 1) + 3);
      printf("Score: %d\n", score);
    }// end of if
  }// end of else

} // end of update
///////////////////////////////////////////////////////////////////////////////
void setCursorPosition(int x, int y){
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coord = { (SHORT)x, (SHORT)y };
  SetConsoleCursorPosition(hOut, coord);
} // end of setCursorPosition
///////////////////////////////////////////////////////////////////////////////
// Clear Screen
void cls() {
  // Get the Win32 handle representing standard output.
  // This generally only has to be done once, so we make it static.
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD topLeft = { 0, 0 };
  // Figure out the current width and height of the console window
  if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
    // TODO: Handle failure!
    abort();
  }
  DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
  DWORD written;

  // Flood-fill the console with spaces to clear it
  FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

  // Reset the attributes of every character to the default.
  // This clears all background colour formatting, if any.
  FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

  // Move the cursor back to the top left for the next sequence of writes
  SetConsoleCursorPosition(hOut, topLeft);
} // end of cls
///////////////////////////////////////////////////////////////////////////////
// Hide cursor
void show_cursor(bool input){
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // should be handle to console screen buffer
  if (!GetConsoleCursorInfo(handle, &cursor)){ // pCursor is structure
    printf("Failure to get console cursor info.\n");
  } else {
    if (input) {
      cursor.bVisible = true;
      SetConsoleCursorInfo(handle, &cursor);
    } else {
      cursor.bVisible = false;
      SetConsoleCursorInfo(handle, &cursor);
    }
  }
}
///////////////////////////////////////////////////////////////////////////////
// end of file
