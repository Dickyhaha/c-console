#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define i_length 40
#define j_length 40
#define sleep_time 100

int map[2][i_length][j_length];
int num;

enum{
    up=256+72,
    down=256+80,
    left=256+75,
    right=256+77,
    esc=27,
    black=0,
    yellow=1,
    cyan=2,
    purple=3,
};

void color(int color)
{
    switch(color)
    {
        case black:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
            break;
        case purple:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case cyan:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case yellow:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
    }
}

static int get_code(void)
{
    int ch=getch();
    if (ch==0||ch==224)
    ch=256+getch();
    return ch;
}

void setpos(int i,int j)
{
    COORD a_struct={j*2,i};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a_struct);
}

int count(int i1,int j1)
{
    int i,j,count=0;
    for(i=i1-1;i<=i1+1;i++)
        for(j=j1-1;j<=j1+1;j++)
            if(i>=0&&j>=0&&i<i_length&&j<j_length)
                if(map[num%2][i][j]==cyan)
                    count++;
    return count;
}

int main()
{
	ShowWindow( GetConsoleWindow() , SW_MAXIMIZE);
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    BOOL result;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo(myconsole, &CURSOR);
    
    int i,j,input;
  	
  	
    for(i=0;i<i_length;i++)
        for(j=0;j<j_length;j++)
            map[0][i][j]=map[1][i][j]=0;
  	
  	while(1)
    {
        color(black);
        input=0;
        printf("Edit mode - <SpaceBar> for yellow/black <z> for head <x> for tail <Enter> for start\n");
        for(j=0;j<j_length;j++)
            printf("%2c",'-');
        printf("\n");
        for(i=0;i<i_length;i++)
        {
            for(j=0;j<j_length;j++)
                printf("%2c",' ');
            printf("|\n");
        }
        for(j=0;j<j_length;j++)
            printf("%2c",'-');
        printf("\n");
        
        i=j=input=0;
        
        while(input!=13)
        {
            setpos(i+2,j);
            color(yellow);
            printf("%2c",' ');
            color(black);
            input=get_code();
            setpos(i+2,j);
            color(map[0][i][j]);
            printf("%2c",' ');
            color(black);
            if(input==up&&i>0)
                i--;
            else if(input==down&&i<i_length-1)
                i++;
            else if(input==left&&j>0)
                j--;
            else if(input==right&&j<j_length-1)
                j++;
            else if(input==' ')
            {
                if(map[0][i][j]==black)
                    map[0][i][j]=yellow;
                else 
                    map[0][i][j]=black;
            }
            else if(input=='z')
                map[0][i][j]=cyan;
            else if(input=='x')
                map[0][i][j]=purple;
            
        }
        system("cls");
        printf("Generation  0\n");
        for(i=0;i<i_length;i++)
        {
            for(j=0;j<j_length;j++)
            {
                color(map[0][i][j]);
                printf("%2c",' ');
            }
            printf("\n");
        }
        color(black);
        while(!kbhit())
        {
            setpos(0,6);
            printf("%d",num);
            for(i=0;i<i_length;i++)
                for(j=0;j<j_length;j++)
                {
                    if(map[num%2][i][j]==yellow)
                    {
                        if(count(i,j)==1||count(i,j)==2)
                        {
                            map[(num+1)%2][i][j]=cyan; 
                            setpos(i+1,j);
                            color(map[(num+1)%2][i][j]);
                            printf("%2c",' ');
                            color(black);
                        }
                        else 
                            map[(num+1)%2][i][j]=yellow;
                    }
                    else if(map[num%2][i][j]==cyan)
                    {
                        map[(num+1)%2][i][j]=purple;
                        setpos(i+1,j);
                        color(map[(num+1)%2][i][j]);
                        printf("%2c",' ');
                        color(black);
                    }
                    else if(map[num%2][i][j]==purple)
                    {
                        map[(num+1)%2][i][j]=yellow;
                        setpos(i+1,j);
                        color(map[(num+1)%2][i][j]);
                        printf("%2c",' ');
                        color(black);
                    }
                }
            num++;
            usleep(sleep_time*1000);
        }
        getch();
        fflush(stdout);
        for(i=0;i<i_length;i++)
            for(j=0;j<j_length;j++)
                map[0][i][j]=0;
        setpos(0,0);
    }
    return 0;
}
