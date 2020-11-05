#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<WinCon.h>

CONSOLE_CURSOR_INFO cursor;

int main(){
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // should be handle to console screen buffer
  if (!GetConsoleCursorInfo(handle, &cursor)){ // pCursor is structure
    printf("Failure to get console cursor info.\n");
  }
  cursor.bVisible = false;
  SetConsoleCursorInfo(handle, &cursor);
  Sleep(2000);
  cursor.bVisible = true;
  SetConsoleCursorInfo(handle, &cursor);
  Sleep(2000);
  return 0;
}
