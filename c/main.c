#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> // bool, true, false
#include<math.h>    // round
#include<time.h>    // time
#include<conio.h>   //
#include<windows.h> // Sleep, cls(). On Unix include unistd.h
///////////////////////////////////////////////////////////////////////////////
// function declarations
void setup(void);
void draw(void);
void input(void);
void logic(void);
void cls(void);
void update_map(void);
void setCursorPosition(int, int);
///////////////////////////////////////////////////////////////////////////////
// global variable declarations
bool gameover;
const int width = 80;
const int height = 40;
int x, y, fruitx, fruity = 0;
int score = 0;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirection dir;
int count = 0;

///////////////////////////////////////////////////////////////////////////////
// MAIN
int main(){
  setup();
  while (!gameover) {
    update_map();
    input();
    logic();
    //Sleep(2000); // on windows sleep(1000) to sleep 1 sec
                // on unix enter sleep(1) to sleep 1 second
  }// end main

  return 0;
}// end of main
///////////////////////////////////////////////////////////////////////////////
// SETUP
void setup(){
  // local variable declarations
  int minx = 1;
  int maxx = width - 1;
  int miny = 1;
  int maxy = height - 1;

  // allows us to enter the while loop and play the game
  gameover = false;

  dir = STOP;

  // start in the middle
  x = round(width/2);
  y = round(height/2);

  // place the fruit randomly
  srand((unsigned) time(0)); // use current time as seed
  fruitx = rand() % (maxx - minx + 1) + minx;
  fruity = rand() % (maxy - miny + 1) + miny;

  // Draw the map
  draw();
} // end setup
///////////////////////////////////////////////////////////////////////////////
// DRAW
void draw(){
  //system("cls"); // clear the terminal window
  cls(); // local function (below)

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
      if (i == x && j == y){
        printf("S");
      }
      else if (i == fruitx && j == fruity){
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

  // score board
  printf("Score: %d\n", score);

} // end draw
///////////////////////////////////////////////////////////////////////////////
// Update Map
void update_map() {
// x is the column, y is the row. The origin (0,0) is top-left.


// Step through with a debugger, or insert sleeps, to see the effect.
setCursorPosition(1, 1);
printf("CHEESE");         //std::cout << "CHEESE";
/*
Sleep(1000);
setCursorPosition(10, 5);
printf("W");              // std::cout 'W';
Sleep(1000);
setCursorPosition(10, 9);
printf("Z");              // std::cout << 'Z';
Sleep(1000);
setCursorPosition(10, 5);
printf("     ");          // std::cout << "     ";  // Overwrite characters with spaces to "erase" them
Sleep(1000);
*/
while (getchar() != '\n'); //std::cout.flush();
// Voilà, 'CHEESE' converted to 'WHEEZE', then all but the last 'E' erased
} // end of update_map

///////////////////////////////////////////////////////////////////////////////
// INPUT
void input(){
  if (kbhit()){
    switch (getch()) {
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
// Clear Screen
void cls() {
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    //_fpurge(); // C
    // std::cout.flush(); // C++

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
void setCursorPosition(int x, int y){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //std::cout.flush();
    while (getchar() != '\n');
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
} // end of setCursorPosition
///////////////////////////////////////////////////////////////////////////////
// end of file
