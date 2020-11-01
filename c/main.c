#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> // bool, true, false
#include<math.h>    // round
#include<time.h>    // time
#include<conio.h>   //
#include<windows.h> // Sleep. On Unix include unistd.h
///////////////////////////////////////////////////////////////////////////////
// function declarations
void setup(void);
void draw(void);
void input(void);
void logic(void);
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
    draw();
    input();
    logic();
    Sleep(100); // on windows sleep(1000) to sleep 1 sec
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
} // end setup
///////////////////////////////////////////////////////////////////////////////
// DRAW
void draw(){
  system("cls"); // clear the terminal window


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
// end of file
