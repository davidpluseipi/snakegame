#include<graphics.h>
#include<conio.h>
int main()
{
   int gd = DETECT, gm;

   initgraph(&gd, &gm, "C:\\MinGW\\BGI");

   getch();
   closegraph();
   return 0;
}
