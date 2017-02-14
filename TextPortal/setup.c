#include <windows.h>
#include "setup.h"

void nocur()
{
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    BOOL result;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo(myconsole, &CURSOR);
}

void setpos(int i,int j)
{
    COORD a_struct={j*2,i};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a_struct);
}

int get_code()
{
    int ch=getch();
    if (ch==0||ch==224)
    ch=256+getch();
    return ch;
}

void color(int color)
{
    switch(color)
    {
        case 0:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
            break;
        case 1:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case 2:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case 3:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case 4:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case 5:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case 6:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case 7:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN);
            break;
    } 
}

