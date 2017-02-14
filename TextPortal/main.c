#include <stdio.h>
#include <stdlib.h>
#include "setup.h"

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

int loadmap()
{
    system("cls");
    int i,j=0,input=0;
    printf("Load map:\n");
    color(white);
    printf("%2c",'0');
    color(black);
    for(i=1;i<10;i++)
        printf("%2d",i);
    while(input!=13)
    {
        input=get_code();
        setpos(1,j);
        color(black);
        printf("%2d",j);
        if(input==left)
            j--;
        else if(input==right)
            j++;
        if(j<0)
            j=9;
        else if(j>9)
            j=0;
        setpos(1,j);
        color(white);
        printf("%2d",j);
        color(black);
    }
    system("cls");
    return j;
}

void game()
{
    int i,j,num;
    char map[20][20];
    num=loadmap();
    FILE* mfile;
    if(num==0)
        mfile=fopen("maps/map0.txt","r");
    else if(num==1)
        mfile=fopen("maps/map1.txt","r");
    else if(num==2)
        mfile=fopen("maps/map2.txt","r");
    else if(num==3)
        mfile=fopen("maps/map3.txt","r");
    else if(num==4)
        mfile=fopen("maps/map4.txt","r");
    for(i=0;i<20;i++)
        {
            fscanf(mfile,"%s",map[i]);
            printf("%d",map[i][j]);
        }
    
}

void edit()
{
}

int main()
{
    int input=0;
    printf("Welcome to TextPortal\nPlay <P>     Editor <E>     Exit <Esc>");
    while(input!=esc)
    {
        input=get_code();
        if(input=='p')
            game();
        else if(input=='e')
            edit();
    }
    system("cls");
    printf("Bye~");
    sleep(1000);
    return 0;
}
