#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show(char words[],int time)
{
    printf("%s",words);
    sleep(time);
    system("cls");
}

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

void arrows(void)
{
    int i,j;
    for(j=0;j<40;j++)
    {
        i=rand()%4;
        if(i==0)
            show("¡ö",50);
        else if(i==1)
            show("¡ô",50);
        else if(i==2)
            show("¡÷",50);
        else if(i==3)
            show("¡õ",50);
        system("cls");
        sleep(10);
    }
    sleep(1000);
    show("...",3000);
    j=rand()%20+1;
    if(j==1)
        printf("Alright, what is the 1st direction? ");
    else if(j==2)
        printf("Alright, what is the 2nd direction? ");
    else if(j==3)
        printf("Alright, what is the 3rd direction? ");
    else
        printf("Alright, what is the %dth direction? ",j);
    i=get_code();
    if(i==up)
        printf("¡ô");
    else if(i==down)
        printf("¡õ");
    else if(i==left)
        printf("¡ö");
    else if(i==right)
        printf("¡÷");
    sleep(500);
    system("cls");
    show("Wrong direction...",2000);
    return;
}
        
void grids(void)
{
    char grid[10][10];
    int i,j,k,a,b,input=0;
    for(i=0;i<10;i++)
        for(j=0;j<10;j++)
            grid[i][j]=' ';
    for(i=0;i<10;i++)
        grid[i][0]=grid[0][i]=i+48;
    for(k=0;k<50;k++)
    {
        a=rand()%9+1;
        b=rand()%9+1;
        grid[a][b]='X';
        for(i=0;i<10;i++)
        {
            for(j=0;j<10;j++)
                printf("%2c",grid[i][j]);
            printf("\n");
        }
        grid[a][b]=' ';
        system("cls");
    }
    for(i=0;i<10;i++)
        {
            for(j=0;j<10;j++)
                printf("%2c",grid[i][j]);
            printf("\n");
        }
    sleep(1000);
    system("cls");
    show("...",2000);
    printf("Alright then... What are the coordinates where ""X"" appeared twice?\n");
    while(input<1||input>9)
    {
        fflush(stdin);
        printf("X-coor: ");
        scanf("%d",&input);
    }
    input=0;
    while(input<1||input>9)
    {
        fflush(stdin);
        printf("Y-coor: ");
        scanf("%d",&input);
    }
    system("cls");
    sleep(1000);
    show("... No it's not...",2000);
    return;
}
        
int nums()
{
    int input=0,num[10],i,score=0;
    for(i=0;i<10;i++)
    {
        num[i]=rand()%9+1;
        printf("%d",num[i]);
        sleep(1000);
        system("cls");
        sleep(50);
    }
    sleep(950);
    show("...",2000);
    sleep(50);
    show("..............",2000);
    printf("So... What is the ");
    i=rand()%10+1;
    if(i==1)
        printf("1st ");
    else if(i==2)
        printf("2nd ");
    else if(i==3)
        printf("3rd ");
    else    
        printf("%dth ",i);
    printf("number? ");
    scanf("%d",&input);
    system("cls");
    if(input==num[i-1])
    {
        show("Nice @_@",1000);
        score++;
    }
    else
        show("Yea... no it's not...",2000);
    i=rand()%10;
    printf("Next question... the number '%d' first appeared as the ?-th number? ",num[i]);
    fflush(stdin);
    scanf("%d",&input);
    system("cls");
    if(input-1==i)
    {
        show("Nice lol",1000);
        score++;
    }
    else 
        show("Well... Nope it's not...",2000);
    return score;
}
     
void display(int i,int j,int k)
{
    system("cls");
    printf("Slot machine(Operating)");
    printf("\nùÝùùùÞùùùÞùùùß\nùø%2dùø%2dùø%2dùø\nùø%2dùø%2dùø%2dùø¡ö\nùø%2dùø%2dùø%2dùø\nùãùùùäùùùäùùùå\n\n",(i+1)%9+1,(j+1)%9+1,(k+1)%9+1,i%9+1,j%9+1,k%9+1,(i-1)%9+1,(j-1)%9+1,(k-1)%9+1);
    sleep(50);
    return;
}

void slot(void)
{
    int i,j,k,input=0,time,c1,c2,c3,real;
    printf("Slot machine\n");
    printf("ùÝùùùÞùùùÞùùùß\nùø Xùø Xùø Xùø\nùø Xùø Xùø Xùø¡ö\nùø Xùø Xùø Xùø\nùãùùùäùùùäùùùå\n\n");
    printf("Press <Enter> to test your luck!\nPress <T> to give it a try first.\n\nInstruction: To win the mega prize, get three '7'\n");
    c1=rand()%9+1;
    c2=rand()%9+1;
    c3=rand()%9+1;
    system("cls");
    i=rand()%7+2;
    do
        j=rand()%7+2;
    while(i==j);
    do
        k=rand()%7+2;
    while(k==i||k==j);
        
    time=clock();
    while(1)
    {
        display(i,j,k);
        i++;
        j++;
        k++;
        if(kbhit())
        {
            getch();
            break;
        }
    }
    while(1)
    {
        display(i,j,k);
        j++;
        k++;
        if(kbhit())
        {
            getch();
            break;
        }
    }
    while(1)
    {
        display(i,j,k);
        k++;
        if(kbhit())
        {
            getch();
            break;
        }
    }
    display(i,j,k);
    system("pause");
    return; 
}
   
int main()
{
    srand(time(NULL));
    slot();
    return 0;
}
