#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

static int get_code(void)
{
    int ch=getch();
    if (ch==0||ch==224)
    ch=256+getch();
    return ch;
}


enum{
    scw=45,
    sch=50,
    up=256+72,
    down=256+80,
    left=256+75,
    right=256+77,
    esc=27
};

void game()
{                          
    char mymap[11][11],yourmap[11][11],input[2];             
    int i,j,k,dir,checkcoor=0,checkdir=0,myship[4][4],yourship[4][4],reset=0;
    
    while(reset==0)
    {
        for(i=0;i<4;i++)                                          //map initialize
        for(j=0;j<4;j++)
            myship[i][j]=yourship[i][j]=0;
        for(i=1;i<11;i++)
        for(j=1;j<11;j++)
        {
            mymap[i][j]=' ';
            yourmap[i][j]=' ';
        }
        for(i=0;i<11;i++)
        {
            yourmap[0][i]=mymap[0][i]=i+64;
            yourmap[i][0]=mymap[i][0]=i+47;
        }                                                          //end of map initialize
        for(k=0;k<4;k++)
        {   
            yourmap[0][0]=mymap[0][0]='\\';
            system("cls");
            checkcoor=checkdir=0;                                                                    
            while(checkcoor!=1||checkdir!=1)                      //Data validation
            {   
                printf("       Your Map\n");                        //display map
                for(i=0;i<11;i++)                                    
                {
                    for(j=0;j<11;j++)
                        printf("%2c",mymap[i][j]);
                    printf("\n");
                }                                                   //end of display map
                
    //printf("\n%d %d %d %d\n",myship[k-1][0],myship[k-1][1],myship[k-1][2],myship[k-1][3]);    show ship coordinates
                
                printf("\nShip %d:",k+1);
                checkcoor=checkdir=0;
                while(checkcoor!=1)
                {
                    scanf("%s",input);
                    if(input[0]>74)
                    input[0]-=32;
                    input[0]-=64;
                    input[1]-=47;
                    if(input[0]<0||input[0]>10||input[1]<0||input[1]>10||strlen(input)>2)
                        printf("Invalid input\nRe-enter: ");
                    else if(mymap[input[1]][input[0]]!=' ')
                        printf("Your ship will crash\nRe-enter: ");
                    else
                        checkcoor=1;
                }
                printf("Direction?");
                while(checkdir!=1)
                {
                    dir=get_code();
                    if(dir!=down&&dir!=up&&dir!=left&&dir!=right)
                        printf("Invalid input\nRe-enter: ");
                    else
                        checkdir=1;
                }
                if(dir==up)
                {
                    for(i=0;i<k+2;i++)
                    if(mymap[input[1]-i][input[0]]!=' ')
                        checkdir=0;
                    if(checkdir==1)
                    {
                        myship[k][0]=input[1];
                        myship[k][1]=myship[k][3]=input[0];
                        for(i=0;i<k+2;i++)
                            mymap[input[1]-i][input[0]]='X';
                        myship[k][2]=input[1]-i+1;
                    }
                }
                else if(dir==down)
                {
                    for(i=0;i<k+2;i++)
                    if(mymap[input[1]+i][input[0]]!=' ')
                        checkdir=0;  
                    if(checkdir==1)
                    {
                        myship[k][0]=input[1];
                        myship[k][1]=myship[k][3]=input[0];
                        for(i=0;i<k+2;i++)
                            mymap[input[1]+i][input[0]]='X';
                        myship[k][2]=input[1]+i-1;
                    }
                }
                else if(dir==left)
                {
                    for(i=0;i<k+2;i++)
                    if(mymap[input[1]][input[0]-i]!=' ')
                        checkdir=0;
                    if(checkdir==1)
                    {
                        myship[k][0]=myship[k][2]=input[1];
                        myship[k][1]=input[0];
                        for(i=0;i<k+2;i++)
                            mymap[input[1]][input[0]-i]='X';
                        myship[k][3]=input[0]-i+1;
                    }
                }
                else
                {
                    for(i=0;i<k+2;i++)
                    if(mymap[input[1]][input[0]+i]!=' ')
                        checkdir=0;
                    if(checkdir==1)
                    {
                        myship[k][0]=myship[k][2]=input[1];
                        myship[k][1]=input[0];
                        for(i=0;i<k+2;i++)
                            mymap[input[1]][input[0]+i]='X';
                        myship[k][3]=input[0]+i-1;
                    }
                }
                if(checkdir==0)
                {
                    system("cls");
                    printf("Your ship will crash\nRe-enter: ");
                    sleep(500);
                    system("cls");
                }
            }
        }
        system("cls");
        printf("       Your Map\n");                        //display map
        for(i=0;i<11;i++)                                    
        {
            for(j=0;j<11;j++)
                printf("%2c",mymap[i][j]);
            printf("\n");
        }                                                   //end of display map
        printf("\nPress any key to start, press <esc> to reset your map.");
        reset=getch();
        if(reset==esc)
            reset=0;
        else 
            reset=1;
    }                                                       //end of cutom position
    
    
}

void help()
{
    printf("help");
    sleep(1000);
    
}

int main()
{
    srand(time(NULL));
    char input;
    while(1)
    {
        system("cls");
        printf("Welcome to BattleShip.\n\n");
        printf("Start<S>   Help<H>   Exit<E>\n");
        input=getch();
        system("cls");
        if(input=='S'||input=='s')
        {
            game();
        }
        else if(input=='H'||input=='h')
        {
            help();
        }
        else if(input=='E'||input=='e')
        {
            printf("Bye~");
            sleep(1000);
            return 0;
        }
        else 
        {
            system("cls");
            printf("Invalid input.");
            sleep(1000);
        }
    }

}
