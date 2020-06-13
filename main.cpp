#include <iostream>
#include <conio.h> // for input
#include <windows.h> // for sleep 
#include <stdio.h>  // printf, NULL
#include <stdlib.h> // rand, srand, cls
#include <time.h> // time

using namespace std;

// global variables
bool gameOver;
const int width = 20;
const int height = 20;
int x,y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int sleepvar = 100;

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw() {
    system("cls"); //clears the screen, linux system("clear")

    // top border of map
    for (int i = 0; i < width + 2; i++) 
        cout << "#";
    
    cout << endl;

    // drawing the map
    for (int i = 0; i < height; i++) // y, vertical
    {
        for (int j = 0; j < width; j++) // x, horizontal
        {
            if (j == 0)
                cout << "#";                    // left border of the map
                
            if (i == y && j == x)
                cout << "0";                    // this is the snake's head
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++){
                    
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                    
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    // bottom border of map
    for (int i = 0; i < width + 2; i++) 
        cout << "#";

    cout << endl;
    cout << "Score: " << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void logic() {

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

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

    // end the game if you touch the border
    if (x > width || x < 0 || y > height || y < 0) {    
        gameOver = true;
    }

    /* 
    // end the game if you eat your tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    */
    
    // if the snake eats the fruit
    if (x == fruitX && y == fruitY) {           
        score += 10;     
        srand(time(0));                       // reward with points
        fruitX = rand() % width;                // randomly place the next fruit
        fruitY = rand() % height;
        nTail++;                                // increase length of the tail
    }

}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(sleepvar); // slows the game
    }

    return 0;
}