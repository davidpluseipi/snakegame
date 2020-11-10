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
void show_gameover(void);
void show_winner(void);
///////////////////////////////////////////////////////////////////////////////
// global variable declarations
bool gameover;
const int width = 80;
const int height = 40;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirection dir;
int fruitx, fruity, score, x, x_head_old, y, y_head_old = 0;
int x_old[101], y_old[101], x_temp[102], y_temp[102];
int minx, miny = 2;
int maxx = width - 1;
int maxy = height - 1;
CONSOLE_CURSOR_INFO cursor;
///////////////////////////////////////////////////////////////////////////////
// MAIN
int main(){
  show_cursor(false); // stop showing the cursor
  cls(); // Display splash screen
  setCursorPosition(round(width/2), round(height/2));
  printf("Snake Game");
  Sleep(2000);

  // Get the board ready
  setup();
  while(!gameover) {
    input();
    logic();
    update();
    Sleep(100); // on windows sleep(1000) to sleep 1 sec. On unix enter sleep(1) to sleep 1 second
  }
  if (score < 100) {show_gameover();} else {show_winner();}
  show_cursor(true);
  fflush(stdin); // clear the input buffer (extra keyboard input would otherwise show after the return)
  return 0;
}// end of main
///////////////////////////////////////////////////////////////////////////////
// SETUP
void setup(){
  cls();
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

  draw();
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
      case 'A': // in case the caps lock is on
        dir = LEFT;
        break;
      case 'd':
        dir = RIGHT;
        break;
      case 'D':
        dir = RIGHT;
        break;
      case 'w':
        dir  = UP;
        break;
      case 'W':
        dir  = UP;
        break;
      case 's':
        dir = DOWN;
        break;
      case 'S':
        dir = DOWN;
        break;
      case 'x':
        gameover = true;
        break;
      case 'X':
        gameover = true;
        break;
    } // end switch
  } // end if kbhit
}// end input function
///////////////////////////////////////////////////////////////////////////////
// LOGIC
void logic(){
  // head
  x_head_old = x;
  y_head_old = y;
  // tail
  x_temp[0] = x;
  y_temp[0] = y;
  for (int i = 0; i < score; i++){
    x_temp[i+1] = x_old[i];
    y_temp[i+1] = y_old[i];
  }
  for (int i = 0; i < 100; i++){
    x_old[i] = x_temp[i];
    y_old[i] = y_temp[i];
  }
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
// UPDATE
void update() {
  // x is the column, y is the row. The origin (0,0) is top-left.
  // Remove the old head
  setCursorPosition(x_head_old, y_head_old);
  printf(" ");
  // Remove the old tail
  if (score > 0){
    for (int i = 0; i < score + 1; i++){
      setCursorPosition(x_old[i], y_old[i]);
      printf(" ");
    }
  }
  // Check to see if the snake is still on the map
  if ((x < 1 | (x > width - 1) ) | (y < 1 | (y > height - 1) )) {
    gameover = true;
  } else {
    // Place the snake's tail and check if the snake touches its tail
    if (score > 0){
      for (int i = 0; i < score; i++){
        setCursorPosition(x_old[i], y_old[i]);
        printf("o");
        if (x == x_old[i] & y == y_old[i]){
          gameover = true;
          break;
        }
      }
    }
    // If snake's head is at fruit location, increase score and move fruit
    if (x == fruitx & y == fruity) {
      fruitx = rand() % (maxx - minx + 1) + minx;
      fruity = rand() % (maxy - miny + 1) + miny;
      score++;
      if (score == 100){
        gameover = true;
      }
      setCursorPosition(7, (height + 1) + 3);
      printf("%d\n", score);
    }// end of if
    // Print the fruit (over the tail if necessary)
    setCursorPosition(fruitx, fruity);
    printf("F");
    // Place the snake's head (over the tail if necessary)
    setCursorPosition(x, y);
    printf("O");
  }// end of else

} // end of update
///////////////////////////////////////////////////////////////////////////////
// setCursorPosition
void setCursorPosition(int x, int y){
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coord = { (SHORT)x, (SHORT)y };
  SetConsoleCursorPosition(hOut, coord);
} // end of setCursorPosition
///////////////////////////////////////////////////////////////////////////////
// CLEAR SCREEN
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
// SHOW CURSOR
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
// SHOW GAMEOVER
void show_gameover(){
  cls();
  setCursorPosition(round(width/2), round(height/2));
  printf("Game Over");
  Sleep(2000);
  cls();
} // end show_gameover
///////////////////////////////////////////////////////////////////////////////
// SHOW WINNER
void show_winner(){
  cls();
  setCursorPosition(round(width/2), round(height/2));
  printf("> 100 Points Makes You A Winner!");
  setCursorPosition(0, height);
  printf("(Press any key to exit)");
  _getch(); // windows version of getch()
  cls();
}
// end of file
