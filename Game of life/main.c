#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define i_length 35
#define j_length 80
#define sleep_time 100000

int map[2][i_length][j_length];
int num;

enum{
    up=256+72,
    down=256+80,
    left=256+75,
    right=256+77,
    esc=27,
    black=0,
    white=1,
};

void color(int color)
{
    switch(color)
    {
        case black:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
            break;
        case white:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN);
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
                count+=map[num%2][i][j];
    count-=map[num%2][i1][j1];
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
    
    while(1)
    {
        num=0;
        for(i=0;i<i_length;i++)
        for(j=0;j<j_length;j++)
            map[0][i][j]=map[1][i][j]=0;
        color(black);
        printf("Edit mode - Press <SpaceBar> to toggle cell\n");
        for(j=0;j<j_length;j++)
            printf("%2c",'-');
        printf("\n");
        for(i=0;i<i_length;i++)
        {
            for(j=0;j<j_length;j++)
                printf("%2c",' ');
            printf("%2c\n",'|');
        } 
        for(j=0;j<j_length;j++)
            printf("%2c",'-');
        i=j=input=0;
        while(input!=13)
        {
            setpos(i+2,j);
            color(white);
            printf("%2c",' ');
            color(black);
            input=get_code();
            if(map[0][i][j]!=1)
            {
                setpos(i+2,j);
                color(black);
                printf("%2c",' ');
            }
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
                map[0][i][j]=(map[0][i][j]+1)%2;
                setpos(i+2,j);
                color(white);
                printf("%2c",' ');
                color(black);
            }
        }
        system("cls");
        printf("Generation  0\n");
        for(i=0;i<i_length;i++)
        {
            for(j=0;j<j_length;j++)
            {
                color(map[0][i][j]);
                printf("%2c",' ');
                color(black);
            }
            printf("\n");
        }
        while(!kbhit())
        {
            setpos(0,6);
            printf("%d",num);
            for(i=0;i<i_length;i++)
                for(j=0;j<j_length;j++)
                {
                    if(map[num%2][i][j])
                        map[(num+1)%2][i][j]=(count(i,j)==2||count(i,j)==3);
                    else
                        map[(num+1)%2][i][j]=(count(i,j)==3);
                    if(map[(num+1)%2][i][j]!=map[num%2][i][j]&&!(map[(num+1)%2][i][j]))
                    {
                        setpos(i+1,j);
                        color(black);
                        printf("%2c",' ');
                    }
                }
            for(i=0;i<i_length;i++)
                for(j=0;j<j_length;j++)
                {
                    if(map[(num+1)%2][i][j])
                    {
                        setpos(i+1,j);
                        color(white);
                        printf("%2c",' ');
                        color(black);
                    }
                    map[num%2][i][j]=0;
                }
            num++;
            usleep(sleep_time);
        }
        getch();
        system("cls");
    }
    return 0;
}
