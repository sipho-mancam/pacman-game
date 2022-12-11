#ifndef ESD_H_INCLUDED
#define ESD_H_INCLUDED
#include <windows.h>

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
}

void setColor(int c)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

void clrscr()
{
    int i,j;
    for(i=0;i<30;i++)
    {
        for(j=0;j<100;j++)
        {
            gotoxy(j,i);
            printf(" ");
        }
    }
    gotoxy(0,0);
}

void box(int y, int x, int w, int h)
{
    for(size_t width=0; width<=w;++width)
    {
        gotoxy(x+1+(width-1),y);
        printf("%c",205);
        gotoxy(x+1+(width-1),y+h);
        printf("%c",205);
    }
    for(size_t height=0;height<h;++height)
    {
        gotoxy(x,(height-1)+y+1);
        printf("%c",186);
        gotoxy(x+w,(height-1)+y+1);
        printf("%c",186);
    }
    gotoxy(x,y);
    printf("%c",201);
    gotoxy(x+w,y);
    printf("%c",187);
    gotoxy(x,y+h);
    printf("%c",200);
    gotoxy(x+w,y+h);
    printf("%c",188);

}



#endif // ESD_H_INCLUDED
