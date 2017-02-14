#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int i_length;
int j_length;

enum{
    scw=45,
    sch=50,
    up=256+72,
    down=256+80,
    left=256+75,
    right=256+77,
    esc=27,
    black=0,
    red=1,
    green=2,
    blue=3,
    yellow=4,
    cyan=5,
    purple=6,
    white=7,
};

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

static int get_code(void)
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
        case black:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
            break;
        case red:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case green:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case blue:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case yellow:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case cyan:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case purple:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case white:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN);
            break;
    } 
}

int touch(int map[2*i_length-1][2*j_length-1],int i,int j)
{
    int counter=0;
    if(map[i-2][j]==2||i==0)
        counter++;
    if(map[i+2][j]==2||i==2*i_length-2)
        counter++;
    if(map[i][j-2]==2||j==0)
        counter++;
    if(map[i][j+2]==2||j==2*j_length-2)
        counter++;
        
    if(counter==4)
        return 0;
    else
        return 1;
}

void solve(int map[2*i_length-1][2*j_length-1])
{
    setpos(2*i_length,0);
    printf("\n\n\n");
    int i,j=0,counter=2;
    int stack[4*i_length*j_length][2];
    for(i=0;i<4*i_length*j_length;i++)
        stack[i][0]=stack[i][1]=-1;
    i=2*i_length-2;
    stack[0][0]=i;
    stack[0][1]=j;
    setpos(i,j);
    color(yellow);
    printf("%2c",' ');
    if(map[i-1][j]==2)
        i--;
    else
        j++;
    setpos(i,j);
    printf("%2c",' ');
    color(black);
    stack[1][0]=i;
    stack[1][1]=j;
    while(i!=0||j!=2*j_length-2)
    {
        if(map[i-1][j]==2&&stack[counter-2][0]!=i-1&&i>0)
        {
            i--;
            stack[counter][0]=i;
            stack[counter][1]=j;
            counter++;
        }
        else if(map[i+1][j]==2&&stack[counter-2][0]!=i+1&&i<2*i_length-2)
        {
            i++;
            stack[counter][0]=i;
            stack[counter][1]=j;
            counter++;
        }
        else if(map[i][j-1]==2&&stack[counter-2][1]!=j-1&&j>0)
        {
            j--;
            stack[counter][0]=i;
            stack[counter][1]=j;
            counter++;
        }
        else if(map[i][j+1]==2&&stack[counter-2][1]!=j+1&&j<2*j_length-2)
        {
            j++;
            stack[counter][0]=i;
            stack[counter][1]=j;
            counter++;
        }
        else if(i!=0||j!=2*j_length-2)
        {
            map[i][j]=1;
            setpos(i,j);
            color(white);
            printf("%2c",' ');
            color(black);
            stack[counter-1][0]=stack[counter-1][1]=-1;
            counter--;
            i=stack[counter-1][0];
            j=stack[counter-1][1];
        }
        setpos(i,j);
        color(yellow);
        printf("%2c",' ');
        color(black);
        //setpos(2*i_length+3,0);
        //printf("%d:      %d     %d    ",counter,i,j);
        int k;
		for(k=0;k<100000;k++)
           	sleep(0);
    }
}

int main()
{
    nocur();
    printf("Enter dimensions (i,j): ");
    scanf("%d %d",&i_length,&j_length);
    system("cls");
    srand(time(NULL));
    int map[2*i_length-1][2*j_length-1];
    int i,j,num,counter=1;
    int stack[i_length*j_length][2];
    for(i=0;i<2*i_length-1;i++)
        for(j=0;j<2*j_length-1;j++)
            map[i][j]=1;
    for(i=0;i<2*i_length-1;i+=2)
        for(j=0;j<2*j_length-1;j+=2)
            map[i][j]=0;
        
    for(i=0;i<i_length*j_length;i++)
        stack[i][0]=stack[i][1]=-1;
    
    for(i=0;i<2*i_length-1;i++)
    {
        for(j=0;j<2*j_length-1;j++)
        {
            color(red);
            printf("%2c",' ');
        }
        printf("\n");
        color(black);
    }
    for(i=0;i<2*i_length-1;i+=2)
        for(j=0;j<2*j_length-1;j+=2)
        {
            setpos(i,j);
            printf("%2c",' ');
        }
    
    i=2*i_length-2;
    j=0;
    map[i][j]=2;
    stack[0][0]=i;
    stack[0][1]=j;
    setpos(2*i_length-2,0);
    color(white);
    printf("%2c",' ');
    color(black);
    while(stack[0][0]!=-1)
    {
        if(touch(map,i,j))
        {
            while(1)
            {
                num=rand()%4;
                if(num==0&&j>0&&map[i][j-2]!=2)
                {
                    map[i][j-1]=map[i][j-2]=2;
                    setpos(i,j-1);
                    color(white);
                    printf("%2c",' ');
                    setpos(i,j-2);
                    printf("%2c",' ');
                    color(black);
                    j-=2;
                    break;
                }
                else if(num==1&&i>0&&map[i-2][j]!=2)
                {
                    map[i-1][j]=map[i-2][j]=2;
                    setpos(i-1,j);
                    color(white);
                    printf("%2c",' ');
                    setpos(i-2,j);
                    printf("%2c",' ');
                    color(black);
                    i-=2;
                    break;
                }
                else if(num==2&&j<2*j_length-2&&map[i][j+2]!=2)
                {
                    map[i][j+1]=map[i][j+2]=2;
                    setpos(i,j+1);
                    color(white);
                    printf("%2c",' ');
                    setpos(i,j+2);
                    printf("%2c",' ');
                    color(black);
                    j+=2;
                    break;
                }
                else if(num==3&&i<2*i_length-2&&map[i+2][j]!=2)
                {
                    map[i+1][j]=map[i+2][j]=2;
                    setpos(i+1,j);
                    color(white);
                    printf("%2c",' ');
                    setpos(i+2,j);
                    printf("%2c",' ');
                    color(black);
                    i+=2;
                    break;
                }
            }
            stack[counter][0]=i;
            stack[counter][1]=j;
            counter++;
            int k = 0;
			for(k=0;k<1000000;k++)
            	sleep(0);
        }
        else
        {
            stack[counter][0]=stack[counter][1]=-1;
            counter--;
            i=stack[counter][0];
            j=stack[counter][1];
        }
        //setpos(0,2*j_length+5);
        //printf("%d:   %d    %d    ",counter,i,j);
    }
    i=2*i_length-2;
    j=0;
    setpos(i,j);
    color(blue);
    printf("%2c",' ');
    //setpos(2*i_length,0);
    color(black);
    //printf("Press <s> to solve");
    while(i!=0||j!=2*j_length-2)
    {
        while(1)
        {
            num=get_code();
            if(num==left&&map[i][j-1]==2&&j>0)
            {
                setpos(i,j);
                color(white);
                printf("%2c",' ');
                j--;
                setpos(i,j);
                color(blue);
                printf("%2c",' ');
                color(black);
                break;
            }
            else if(num==up&&map[i-1][j]==2&&i>0)
            {
                setpos(i,j);
                color(white);
                printf("%2c",' ');
                i--;
                setpos(i,j);
                color(blue);
                printf("%2c",' ');
                color(black);
                break;
            }
            else if(num==right&&map[i][j+1]==2&&j<2*j_length-2)
            {
                setpos(i,j);
                color(white);
                printf("%2c",' ');
                j++;
                setpos(i,j);
                color(blue);
                printf("%2c",' ');
                color(black);
                break;
            }
            else if(num==down&&map[i+1][j]==2&&i<2*i_length-2)
            {
                setpos(i,j);
                color(white);
                printf("%2c",' ');
                i++;
                setpos(i,j);
                color(blue);
                printf("%2c",' ');
                color(black);
                break;
            }
            else if(num=='s')
            {
                solve(map);
                getch();
                return 0;
            }
        }
    }
    system("cls");
    printf("YAY");
    int k;
	for(k=0;k<1000000;k++)
        sleep(0);
    color(black);
    return 0;
}
