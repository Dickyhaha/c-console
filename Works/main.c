#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

char map[2][23][31][41]; //  color/map/i/j
int pos[4];         // map/i/j/dir
char dir[4]={'^','>','v','<'};
int buffpos[3];     // map//i/j
int buff;

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

void cls()
{
    COORD a_struct={0,0};
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

void showmap()
{
    int i,j,lim;
    cls();
    for(i=0;i<31;i++)
    {
        lim=1;
        for(j=0;j<41;j++)
            if(map[1][pos[0]][i][j]!=black)
                lim=0;
        if(lim==1)
        {
            lim=i;
            break;
        }
        else 
            lim=31;
    }
    if(pos[0]!=15)
        printf("\n%2c",' ');
    for(i=0;i<lim;i++)
    {
        for(j=0;j<41;j++)
        {
            if(i==pos[1]&&j==pos[2])
            {
                color(purple);
                printf("%2c",dir[pos[3]]);
            }
            else
            {
                color(map[1][pos[0]][i][j]);
                printf("%2c",map[0][pos[0]][i][j]);
            }
            color(black);   
        }
        if(pos[0]!=15)
            printf("\n%2c",' ');
        else 
            printf("\n");
    }
    //printf("\n %d %d %d  %d",buffpos[0],buffpos[1],buffpos[2],buff);
}

void train()
{
    system("cls");
    int choice=0,input;
    char names[4][7]={"D-TOWN","COURT","MALL","PIER"};
    char train[2][68]={"   _____ _____   ---|MTR|=|MTR|---| |O-O-O|O-O-O| |-----------------","   _____ _____   ---|MTR|=|MTR|--- | O-O-O O-O-O | -----------------"};
    int i,j,k=0,time=clock(),show=1;
    while(1)
    {
        if(kbhit())
        {
            cls();
            input=get_code();
            if(input==up)
                choice--;
            else if(input==down)
                choice++;
            else if(input==13)
            {
                if(choice==0)
                {
                    pos[0]=2;
                    pos[1]=11;
                    pos[2]=14;
                    pos[3]=2;
                }
                else if(choice==1)
                {
                    pos[0]=7;
                    pos[1]=9;
                    pos[2]=1;
                    pos[3]=0;
                }
                else if(choice==2)
                {
                    pos[0]=9;
                    pos[1]=pos[2]=0;
                    pos[3]=1;
                }
                else if(choice==3)
                {
                    pos[0]=17;
                    pos[1]=pos[2]=0;
                    pos[3]=1;
                }
                system("cls");
                return;
            }
            if(choice<0)
                choice=3;
            else if(choice>3)
                choice=0;
            show=1;
        }
        if(clock()-time>=500)
        {
            system("cls");
            time=clock();
            show=1;
            k++;
        }
        if(show==1)
        {
            printf("\n");
            for(i=0;i<4;i++)
            {        
                printf("%2c",' ');
                color(white);
                for(j=0;j<17;j++)
                    printf("%2c",train[k%2][i*17+j]);
                color(black);
                printf("  ");
                if(i==choice)
                    color(white);
                for(j=0;names[i][j]!='\0';j++)
                    printf("%c ",names[i][j]);
                if(i==choice)
                    color(black);
                printf("\n");
            }
            show=0;
        }
    }
}

int checkmap(int face)
{
    int i;
    switch(face)
    {
        case up:
            pos[3]=0;
            if(pos[0]==2)
            {
                if(pos[1]==4&&(pos[2]==21||pos[2]==22))
                {
                    pos[0]=0;
                    pos[1]=6;
                    pos[2]-=20;
                    system("cls");
                    return 0;
                }
                else if(map[0][pos[0]][pos[1]-2][pos[2]]>='A'&&map[0][pos[0]][pos[1]-2][pos[2]]<='I')
                {
                    map[0][3][2][2]=map[0][2][pos[1]-2][pos[2]];
                    buffpos[0]=pos[0];
                    buffpos[1]=pos[1];
                    buffpos[2]=pos[2];
                    pos[0]=3;
                    pos[1]=4;
                    pos[2]=2;
                    system("cls");
                    return 0; 
                }
                else if(pos[1]==11&&pos[2]==14)
                {
                    train();
                    return 0;
                }
            }
            else if(pos[0]==4&&pos[1]==1)
            {
                if(pos[2]>11&&pos[2]<17)
                {
                    pos[0]=2;
                    pos[1]=19;
                    system("cls");
                    return 0;
                }
                else if(map[0][4][pos[1]-1][pos[2]]=='_'&&pos[2]<10)
                {
                    map[1][6][4][0]=map[1][4][pos[1]-1][pos[2]];
                    if(map[0][4][pos[1]-1][pos[2]-1]=='_')
                        pos[2]=4;
                    else
                        pos[2]=3;
                    pos[0]=6;
                    pos[1]=4;
                    system("cls");
                    return 0;
                }
                else if(map[0][4][pos[1]-1][pos[2]]=='_'&&pos[2]>18)
                {
                    map[1][5][9][0]=map[1][4][pos[1]-1][pos[2]];
                    if(map[0][4][pos[1]-1][pos[2]-1]=='_')
                        pos[2]=4;
                    else
                        pos[2]=3;
                    pos[0]=5;
                    pos[1]=9;
                    system("cls");
                    return 0;
                }
            }
            else if(pos[0]==7&&pos[1]==1&&pos[2]>2&&pos[2]<6)
            {
                pos[0]=8;
                pos[1]=5-pos[2];
                pos[2]=10;
                pos[3]=3;
                system("cls");
                return 0;
            }
            else if((pos[0]==10||pos[0]==11)&&map[0][pos[0]][pos[1]-1][pos[2]]=='_')
            {
                for(i=0;i<3;i++)
                    buffpos[i]=pos[i];
                for(i=0;i<3;i++)
                    if(pos[2]==2+i||pos[2]==6+i||pos[2]==10+i||pos[2]==14+i||pos[2]==21+i||pos[2]==25+i)
                        buff=pos[2]=1+i; 
                pos[0]=13;
                pos[1]=7; 
                    system("cls");
                return 0;
            }
            else if(pos[0]==14&&pos[1]==0&&pos[2]>0&&pos[2]<4)
            {
                pos[0]=buffpos[0];
                pos[1]=buffpos[1];
                pos[2]+=buffpos[2]-buff;
                buff=buffpos[0]=buffpos[1]=buffpos[2]=0;
                system("cls");
                return 0;
            }
            else if(pos[0]==18&&pos[1]==1&&pos[2]>17&&pos[2]<22)
            {
                pos[0]=19;
                pos[1]=30;
                pos[2]-=2;
                system("cls");
                return 0;
            }
            return 1;
            break;
        case down:
            pos[3]=2;
            if(pos[0]==0&&pos[1]==6&&(pos[2]==1||pos[2]==2))
            {
                pos[0]=2;
                pos[1]=4;
                pos[2]+=20;
                system("cls");
                return 0;
            }
            else if(pos[0]==2&&pos[1]==19&&pos[2]>11&&pos[2])
            {
                pos[0]=4;
                pos[1]=0;
                system("cls");
                return 0;
            }
            else if(pos[0]==3&&pos[1]==4&&pos[2]==2)
            {
                pos[0]=buffpos[0];
                pos[1]=buffpos[1];
                pos[2]=buffpos[2];
                buff=buffpos[0]=buffpos[1]=buffpos[2]=0;
                system("cls");
                return 0;
            }
            else if(pos[0]==5&&pos[1]==9&&(pos[2]==3||pos[2]==4))
            {
                pos[0]=4;
                pos[1]=1;
                if(map[1][5][9][0]==blue)
                    pos[2]+=16;
                else if(map[1][5][9][0]==yellow)
                    pos[2]+=20;
                else if(map[1][5][9][0]==red)
                    pos[2]+=24;
                system("cls");
                return 0;
            }
            else if(pos[0]==6&&pos[1]==4&&(pos[2]==3||pos[2]==4))
            {
                pos[0]=4;
                pos[1]=1;
                if(map[1][6][4][0]==blue)
                    pos[2]+=5;
                else if(map[1][6][4][0]==yellow)
                    pos[2]++;
                else if(map[1][6][4][0]==red)
                    pos[2]-=3;
                system("cls");
                return 0;
            }
            else if(pos[0]==7&&pos[1]==9&&pos[2]==1)
            {
                train();
                return 0;
            }
            else if((pos[0]==10||pos[0]==11)&&((pos[1]==8&&pos[2]>1&&pos[2]<9)||(pos[1]==17&&pos[2]>12&&pos[2]<28)))
            {
                for(i=0;i<3;i++)
                    buffpos[i]=pos[i];
            }
            else if(pos[0]==13&&pos[1]==7&&pos[2]>0&&pos[2]<4)
            {
                pos[0]=buffpos[0];
                pos[1]=buffpos[1];
                pos[2]+=buffpos[2]-buff;
                buffpos[0]=buffpos[1]=buffpos[2]=0;
                system("cls");
                return 0;
            }
            else if(pos[0]==19&&pos[1]==30&&pos[2]>15&&pos[2]<20)
            {
                pos[0]--;
                pos[1]=1;
                pos[2]+=2;
                system("cls");
                return 0;
            }
            else if(pos[0]==21&&pos[1]==8)
            {
                pos[0]=20;
                pos[1]=9-pos[2];
                pos[2]=1;
                pos[3]=1;
                system("cls");
                return 0;
            }
            return 1;
            break;
        case left:
            pos[3]=3;
            if((pos[0]==9&&pos[1]==0&&pos[2]==0)||(pos[0]==17&&pos[1]==0&&pos[2]==0))
            {
                train();
                return 0;
            }
            else if(pos[0]==10)
            {
                if(pos[1]>10&&pos[1]<15&&pos[2]==11)
                {
                    pos[0]=12;
                    pos[1]-=10;
                    pos[2]=9;
                    system("cls");
                    return 0;
                }
                else if(pos[1]==4&&pos[2]==0)
                {
                    pos[0]=9;
                    pos[1]=0;
                    pos[2]=22;
                    system("cls");
                    return 0;
                }
            }
            else if(pos[0]==11&&pos[1]>12&&pos[1]<15&&pos[2]==11)
            {
                pos[0]=10;
                pos[2]=31;
                system("cls");
                return 0;
            }
            else if(pos[0]==15)
            {
                if(pos[1]>13&&pos[1]<16&&pos[2]==12)
                {
                    pos[0]=11;
                    pos[1]--;
                    pos[2]=31;
                    system("cls");
                    return 0;
                }
                else if(pos[1]>3&&pos[1]<7&&pos[2]==0)
                {
                    system("cls");
                    printf("Opps, you fell off...");
                    sleep(2000);
                    pos[0]=pos[3]=0;
                    pos[1]=pos[2]=3;
                    system("cls");
                    return 0;
                }
            }
            else if(pos[0]==20&&pos[1]>2&&pos[1]<6&&pos[2]==1)
            {
                pos[0]=21;
                pos[2]=9-pos[1];
                pos[1]=8;
                pos[3]=0;
                system("cls");
                return 0;
            }
            return 1;
            break;
        case right:
            pos[3]=1;
            if(pos[0]==0&&pos[1]==0&&pos[2]==6)
            {
                pos[0]=1;
                pos[2]=4;
                system("cls");
                return 0;
            }
            else if(pos[0]==1&&pos[1]==0&&pos[2]==4)
            {
                pos[0]=0;
                pos[2]=6;
                system("cls");
                return 0;
            }
            else if(pos[0]==8&&pos[1]<3&&pos[2]==10)
            {
                pos[0]=7;
                pos[2]=3+pos[1];
                pos[1]=0;
                system("cls");
                return 0;
            }
            else if(pos[0]==9&&pos[2]==22)
            {
                pos[0]=10;
                pos[1]=4;
                pos[2]=1;
                pos[3]=2;
                system("cls");
                return 0;
            }
            else if(pos[0]>9&&pos[0]<12&&pos[1]>12&&pos[1]<15&&pos[2]==31)
            {
                if(pos[0]==10)
                {
                    pos[2]=11;
                    pos[0]++;
                }
                else
                {
                    pos[0]=15;
                    pos[1]++;
                    pos[2]=12;
                }
                system("cls");
                return 0;
            }
            else if(pos[0]==12&&pos[1]>0&&pos[1]<5&&pos[2]==9)
            {
                pos[0]=10;
                pos[1]+=10;
                pos[2]=11;
                system("cls");
                return 0;
            }
            else if(pos[0]==15&&(pos[1]==14||pos[1]==15)&&pos[2]==33)
            {
                system("cls");
                printf("Opps, you fell off...");
                sleep(2000);
                pos[0]=pos[3]=0;
                pos[1]=pos[2]=3;
                system("cls");
                return 0;
            }
            return 1;
            break;
    }
}

void comment(char words[])
{
    printf("%s",words);
    while(1)
        if(kbhit())
        {
            system("cls");
            break;
        }
}

int checkblock(int face)
{
    int vert=0,hori=0;
    if(face==up)
        vert=-1;
    else if(face==down)
        vert=1;
    else if(face==left)
        hori=-1;
    else if(face==right)
        hori=1;
    char target=map[0][pos[0]][pos[1]+vert][pos[2]+hori];
    int color=map[1][pos[0]][pos[1]+vert][pos[2]+hori];
    switch(pos[0])
    {
        case 0:
            if(target>='A'&&target<='O')
                return 0;
            break;
        case 1:
            if(target!=' '&&target!='|')
                return 0;
            break;
        case 2:
            if(color!=white||target=='O'||target=='x')
                return 0;
            break;
        case 3:
            if(target>='A'&&target<='O')
                return 0;
            break;
        case 4:
            if(target!=' ')
                return 0;
            break;
        case 5:
            if((target!='o'&&target!=' '&&target!='_')||color!=white||(target=='_'&&pos[1]<8))
                return 0;
            break;
        case 6:
            if((!(target=='o'||target==' '||target=='_')||color!=white)||(map[0][pos[0]][pos[1]][pos[2]]=='o'&&target=='_')||(map[1][pos[0]][pos[1]-1][pos[2]]==green&&target=='_'))
                return 0;
            break;
        case 7:
            if(target!=' '&&target!='=')
                return 0;
            break;
        case 8:
            if(color!=white)
                return 0;
            break;
        case 9:
            break;
        case 10:
            if(pos[1]>1&&pos[1]<9&&pos[2]==18&&face==right)
            {
                comment("\nShop closed, come never.");
                return 0;
            }
            else if(color!=white)
                return 0;
            break;
        case 11:
            if(color!=white)
                return 0;
            break;
        case 12:
            if(color!=white||(pos[2]<8&&target!=' ')||(pos[2]==8&&pos[1]>0&&pos[1]<5&&face==left))
                return 0;
            break;
        case 13:
            if(color!=white||(pos[1]<6&&target!=' '))
                return 0;
            break;
        case 14:
            if(color!=white||(pos[1]>1&&target!=' '))
                return 0;
            break;
        case 15:
            if(color==yellow)
                return 0;
            break;
        case 16:
            break;
        case 17:
            if(target=='x'||color==blue||target=='.')
                return 0;
            break;
        case 18:
            if(color==yellow||color==blue||target=='x')
                return 0;
            break;
        case 19:
            if(color==yellow||color==red)
                return 0;
            break;
        case 20:
            if(target!=' '&&!(pos[2]<3&&target=='|'))
                return 0;
            break;
        case 21:
            if(target!=' '&&!(pos[1]>6&&target=='_'))
                return 0;
            break;
        case 22:
            if(target!=' '&&target!='|')
                return 0;
            break;
        return 1;
            
    }
}

void merry()
{
    int time=clock(),time1=time,i;
    system("cls");
    for(i=0;i<3;i++)
        buffpos[i]=pos[i];
    pos[0]=2;
    pos[1]=pos[2]=-1;
    while(clock()-time<5000)
    {
        if(clock()-time1>500)
        {
            map[0][2][1][12]=map[0][2][3][12]=map[0][2][2][11]=map[0][2][2][13]=' ';
            map[0][2][1][11]=map[0][2][1][13]=map[0][2][3][11]=map[0][2][3][13]='O';
            map[0][2][2][12]='x';
        }
        if(clock()-time1>1000)
        {
            map[0][2][1][12]=map[0][2][3][12]=map[0][2][2][11]=map[0][2][2][13]='O';
            map[0][2][1][11]=map[0][2][1][13]=map[0][2][3][11]=map[0][2][3][13]=' ';
            map[0][2][2][12]='+';
            time1=clock();
        }
        showmap();
    }
    map[0][2][1][12]=map[0][2][3][12]=map[0][2][2][11]=map[0][2][2][13]='O';
    map[0][2][1][11]=map[0][2][1][13]=map[0][2][3][11]=map[0][2][3][13]=' ';
    map[0][2][2][12]='+';
    for(i=0;i<3;i++)
    {
        pos[i]=buffpos[i];
        buffpos[i]=0;
    }
}

void save()
{
}



void view()
{
    int i=0,j=0,k=0,input=0;
    while(input!=esc)
    {
        system("cls");
        printf("\n%2c",' ');
        for(i=0;i<5;i++)
        {
            for(j=k;j<k+10;j++)
            {
                color(map[1][16][i][j]);
                printf("%2c",map[0][16][i][j]);
                color(black);
            }
            printf("\n%2c",' ');
        }
        while(1)
        {
            input=get_code();
            if(input==right&&k<30)
            {
                k++;
                break;
            }
            else if(input==left&&k>0)
            {
                k--;
                break;
            }
            else if(input==' '&&k==30)
            {
                comment("\nSo you found me :) Well that's it lol");
                break;
            }
            else if(input==esc)
                break;
        }
    }
}

char touch(int face)
{
    int vert=0,hori=0,input;
    if(face==0)
        vert=-1;
    else if(face==2)
        vert=1;
    else if(face==3)
        hori=-1;
    else if(face==1)
        hori=1;
    char target=map[0][pos[0]][pos[1]+vert][pos[2]+hori];
    int color=map[1][pos[0]][pos[1]+vert][pos[2]+hori];
    printf("\n");
    switch(pos[0])
    {
        case 0:
            if(target=='O')
                comment("It's a couch, you can sit on it.");
            break;
        case 1:
            if(target=='@')
                comment("Outdated computer, you might want to change one.");
            else if(target=='['&&pos[2]>0)
                comment("Let's face it, you don't have any new clothes to change.");
            else if(target==']'||target=='[')
                comment("Well this is a bed.");
            else if(target=='s')
                comment("You wish you can save this game.");
            break;
        case 2:
            if(target=='O')
            {
                printf("Press <R> to ride, <ESC> to leave.");
                while(1)
                {
                    input=get_code();
                    if(input=='r')
                    {
                        merry();
                        break;
                    }
                    else if(input==esc)
                        break;
                }
                system("cls");
            }
            else if(target=='x')
                comment("Try walk through the door, not the fence.");
            break;
        case 3:
            if(target=='O')
                comment("It's a couch, you can sit on it.");
            else if(pos[1]==0&&pos[2]==4&&face==1)
                comment("Don't you think it's impolite to visit others' bedrooms?");
            else if(target=='B')
            {
                printf("Press <V> to view profile, <Q> to do quests, <ESC> to leave.");
                while(1)
                {
                    input=get_code();
                    if(input=='v')
                    {
                        comment("\nBob\nAge: 22\nGender: Male\nPost-criminal (got thrown into jail once for robbing a bank)\nKnow many drug dealers and post-criminals like him\nGeorge was his cellmate");
                        break;
                    }
                    else if(input == 'q')
                        return 'b';
                    else if(input==esc)
                        break;
                }
                system("cls");
            }
            else if(target=='C')
            {
                printf("Press <V> to view profile, <Q> to do quests, <ESC> to leave.");
                while(1)
                {
                    input=get_code();
                    if(input=='v')
                    {
                        comment("\nCharlie\nAge: 77\nServe as a military as a teenager\nLoves cats, good friend of Fred\nFriendly, knowledgeable  and generous");
                        break;
                    }
                    else if(input == 'q')
                        return 'c';
                    else if(input==esc)
                        break;
                }
                system("cls");
            }
            else if(target=='F')
            {
                printf("Press <V> to view profile, <Q> to do quests, <ESC> to leave.");
                while(1)
                {
                    input=get_code();
                    if(input=='v')
                    {
                        comment("\nFred\nAge: 46\nGender: Male\nOwner of a pet shop in ABC shopping center\nPet lover, loves talking about pets");
                        break;
                    }
                    else if(input == 'q')
                        return 'f';
                    else if(input==esc)
                        break;
                }
                system("cls");
            }
            else if(target=='G')
            {
                printf("Press <V> to view profile, <Q> to do quests, <ESC> to leave.");
                while(1)
                {
                    input=get_code();
                    if(input=='v')
                    {
                        comment("\nGeorge\nKeen Gambler ever since he got released from jail\nIs a burden to his in groups\nHave a skyrocketing amount of debt");
                        break;
                    }
                    else if(input == 'q')
                        return 'g';
                    else if(input==esc)
                        break;
                }
                system("cls");
            }
            else if(target>='A'&&target<='I')
                comment("...");
            break;
        case 5:
            if(color==green)
                comment("You see nothing... Because there's nothing on it.");
            break;
        case 6:
            if(color==green)
                comment("A sentence with very light color appeared as you see carefully...\nIt says: \"You see nothing... Because there's nothing on it.\"");
            break;
        case 7:
            if(target=='O')
                comment("Follow the light... It will guide you...\nTo that entrance right there.");
            break;
        case 8:
            if(pos[1]==3&&pos[2]==5)
                return 'p';
            else if(pos[1]<4&&color==blue)
                comment("Desks, obviously.");
            
            break;
        case 9:
            if(target>='A'&&target<='Z')
                comment("Yes Yes Yes you can walk pass it.");
            break;
        case 10:
            if(color==blue)
                comment("Shops! So many shops!");
            else if(color==yellow)
                comment("Escalators! So few escalators!");
            break;
        case 11:
            if(color==blue)
                comment("Told you, there are so many shops");
            else if(color==yellow)
                comment("Yup, still so few escalators.");
            break;
        case 12:
            if(map[0][pos[0]][pos[1]][pos[2]-2]=='O'||map[0][pos[0]][pos[1]-2][pos[2]]=='O')
                comment("Shopkeeper: How may I help you?\nYou: Uh...\nShopkeeper: I'm sorry we have nothing to sell.");
            break;
        case 13:
            if(map[0][pos[0]][pos[1]-2][pos[2]]=='O'||map[0][pos[0]][pos[1]][pos[2]+2]=='O')
                comment("Shopkeeper: How may I help you?\nYou: Uh...\nShopkeeper: I'm sorry we have nothing to sell.");
            break;
        case 14:
            if(map[0][pos[0]][pos[1]+2][pos[2]]=='O'||map[0][pos[0]][pos[1]][pos[2]-2]=='O')
                comment("Shopkeeper: How may I help you?\nYou: Uh...\nShopkeeper: I'm sorry we have nothing to sell.");
            break;
        case 15:
            if(color==yellow)
                comment("Stop checking on the escalators man, they are just escalators.");
            else if(color==red)
                comment("Go ahead, walk further.");
            else if(target>='A'&&target<='Z')
            {
                printf("Press <V> to watch view, <ESC> to leave.");
                while(1)
                {
                    input=get_code();
                    if(input=='v')
                    {
                        system("cls");
                        view();
                        break;
                    }
                    else if(input==esc)
                        break;
                }
                system("cls");
            }
            break;
        case 17:
            if(color==blue)
                comment("My bonnie is over this ocean. My bonnie is over the sea...\nOh wait this is not singing time.");
            else if(color==red&&pos[1]==5&&pos[2]==13)
            {
                printf("Press <Enter> to take the yacht, <ESC> to leave.");
                while(1)
                {
                    input=get_code();
                    if(input==13)
                    {
                        system("cls");
                        pos[0]=18;
                        pos[1]=17;
                        pos[2]=18;
                        printf("~~~~~~~");
                        sleep(2000);
                        system("cls");
                        showmap();
                        comment("\nHere you are. What? You thought you were taking a yacht?\nWell... the thing is... life is full of wonder...(Gets punched)... Im sorry :(");
                        break;
                    }
                    else if(input==esc)
                        break;
                }
                system("cls");
            }
            break;
        case 18:
            if(color==blue)
                comment("My bonnie...\nI'm sorry.");
            else if(color==yellow)
                comment("Behold, this mysterious color of yellow represents the meaning of life.\nOr to quote the famous philosopher: The meaning of life is represented by the color yellow.");
            else if(color==red)
                comment("You sure you want to go in? Red means danger you know.");
            else if(color==black&&pos[1]==17&&pos[2]==18)
            {
                printf("Press <Enter> to take the submarine, <ESC> to leave.");
                while(1)
                {
                    input=get_code();
                    if(input==13)
                    {
                        system("cls");
                        pos[0]=17;
                        pos[1]=5;
                        pos[2]=13;
                        printf("~~~~~~~");
                        sleep(2000);
                        system("cls");
                        showmap();
                        comment("\nHere you are.");
                        break;
                    }
                    else if(input==esc)
                        break;
                }
                system("cls");
            }
            break;
        case 19:
            if(color==red)
                comment("Yeah don't jump in.");
            else if(color==blue)
                comment("It might not look like a bridge, but it is.");
            else if(color==yellow)
                comment("Please, just don't check on anything in yellow anymore.");
            break;
        case 20:
            if(target=='-'&&(pos[1]==2||pos[1]==6))
                comment("Ah... The ocean... It is so...\nDark because it's deep under the ocean man.");
            else if(target=='@')
            {
                map[0][20][5][15]=map[0][20][4][19]=' ';
                showmap();
                comment("Well that was easy.");
            }
            else if(target=='o')
                comment("I think it's pretty self-explanatory, plus this is quite tiring.");
            break;
        case 21:
            if(color==black)
                comment("If you are looking for a way out, this is not quite the right way.");
            break;
        case 22:
            if(target=='@')
                comment("Surprise! All those were not real! Ha... Ok I'm out of ideas.");
            break; 
    }
    showmap();
    return 0;
}

char move()
{
    int input=get_code();
    if(input==up&&checkmap(up)&&checkblock(up))
    {
        if(pos[1]!=0&&map[1][pos[0]][pos[1]-1][pos[2]]!=black)
            pos[1]--;
        pos[3]=0;
    }
    else if(input==right&&checkmap(right)&&checkblock(right))
    {
        if(map[1][pos[0]][pos[1]][pos[2]+1]!=black) 
            pos[2]++;
        pos[3]=1;
    }
    else if(input==down&&checkmap(down)&&checkblock(down))
    {
        if(map[1][pos[0]][pos[1]+1][pos[2]]!=black) 
            pos[1]++;
        pos[3]=2;
    }
    else if(input==left&&checkmap(left)&&checkblock(left))
    {
        if(pos[2]!=0&&map[1][pos[0]][pos[1]][pos[2]-1]!=black)
            pos[2]--;
        pos[3]=3;
    }
    else if(input==' ')
       return touch(pos[3]);
    showmap();
}

void say(char words[])
{
    int i;
    for(i=0;words[i]!='\0';i++)
    {
        printf("%c",words[i]);
        //sleep(50);
    }
    while(getch()!=13);
    system("cls");
}

void initialize()
{
    int i,j,k;
    for(k=0;k<23;k++)
        for(i=0;i<31;i++)
            for(j=0;j<41;j++)
            {
                map[0][k][i][j]=' ';
                map[1][k][i][j]=black;
            }
    //reset^
    for(i=0;i<7;i++)
        for(j=0;j<7;j++)
            map[1][0][i][j]=white;
    map[0][0][0][0]=map[0][0][0][2]=map[0][0][2][0]='O';
    map[0][0][0][1]='_';
    map[0][0][1][0]='|';
    map[0][0][0][6]='|';
    map[0][0][6][1]=map[0][0][6][2]='_';
    //D living room^
    for(i=0;i<4;i++)
        for(j=0;j<5;j++)
            map[1][1][i][j]=white;
    map[0][1][0][4]='|';
    map[0][1][0][0]=map[0][1][0][1]='@';
    map[0][1][3][0]=map[0][1][2][4]=map[0][1][3][4]='[';
    map[0][1][3][2]=']';
    map[0][1][3][1]='s'; 
    //D bedroom^
    for(i=0;i<21;i++)
        for(j=0;j<29;j++)
            map[1][2][i][j]=white;
    for(i=0;i<6;i++)
        map[1][2][i][15]=black;
    for(i=0;i<9;i++)
        map[1][2][5][i]=black;
    map[1][2][5][13]=map[1][2][5][14]=black;
    for(i=10;i<13;i++)
        for(j=13;j<16;j++)
            map[1][2][i][j]=black;
    map[1][2][11][14]=map[1][2][12][14]=white;
    for(i=0;i<21;i++)
        map[1][2][20][i+4]=black;
    for(i=0;i<4;i++)
        for(j=0;j<6;j++)
            map[1][2][i][j+19]=purple;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            map[1][2][i+7][j+3]=map[1][2][i+13][j+23]=red;
            map[1][2][i+7][j+8]=map[1][2][i+13][j+18]=yellow;
            map[1][2][i+7][j+18]=map[1][2][i+13][j+8]=green;
            map[1][2][i+7][j+23]=map[1][2][i+13][j+3]=blue;
        }
    map[0][2][1][12]=map[0][2][3][12]=map[0][2][2][11]=map[0][2][2][13]='O';
    map[0][2][2][12]='+';
    map[0][2][1][21]='D';
    map[0][2][1][22]='C';
    map[0][2][3][21]=map[0][2][3][22]='_';
    map[0][2][9][4]=map[0][2][15][4]=map[0][2][9][9]=map[0][2][15][9]=map[0][2][9][19]=map[0][2][15][19]=map[0][2][9][24]=map[0][2][15][24]='_';
    map[0][2][11][14]=map[0][2][12][14]='=';
    for(i=0;i<9;i++)
        map[0][2][19][i+3]=map[0][2][19][i+17]='x';
    map[0][2][20][3]=map[0][2][20][25]='x';
    for(i=0;i<5;i++)
        map[0][2][19][i+12]='_';
    map[0][2][8][4]='A';
    map[0][2][8][9]='B';
    map[0][2][8][19]='C';
    map[0][2][8][24]='E';
    map[0][2][14][4]='F';
    map[0][2][14][9]='G';
    map[0][2][14][19]='H';
    map[0][2][14][24]='I';
    //Community^
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            map[1][3][i][j]=white;
    map[0][3][0][0]=map[0][3][0][2]=map[0][3][2][0]='O';
    map[0][3][0][1]='_';
    map[0][3][1][0]=map[0][3][0][4]='|';
    map[0][3][4][2]='_';
    //Friend bedrooms^
    for(i=0;i<4;i++)
        for(j=0;j<11;j++)
            map[1][4][i+1][j]=white;
    for(i=0;i<6;i++)
        for(j=0;j<17;j++)
            map[1][4][i+1][j+12]=white;
    for(i=0;i<5;i++)
        map[1][4][0][i+12]=white;
    map[1][4][4][11]=white;
    for(i=0;i<2;i++)
    {
        map[1][4][0][i]=map[1][4][0][i+27]=red;
        map[1][4][0][i+4]=map[1][4][0][i+23]=yellow;
        map[1][4][0][i+8]=map[1][4][0][i+19]=blue;
    }
    for(i=0;i<29;i++)
        if(map[1][4][0][i]!=black)
            map[0][4][0][i]='_';
    //Classrooms^
    for(i=0;i<10;i++)
        for(j=0;j<8;j++)
            map[1][5][i][j]=white;
    for(i=0;i<6;i++)
        map[1][5][0][i+1]=green;
    map[0][5][3][0]=map[0][5][3][5]=map[0][5][6][0]=map[0][5][6][5]='[';
    map[0][5][3][1]=map[0][5][3][6]=map[0][5][6][1]=map[0][5][6][6]='_';
    map[0][5][3][2]=map[0][5][3][7]=map[0][5][6][2]=map[0][5][6][7]=']';
    map[0][5][4][1]=map[0][5][4][6]=map[0][5][7][1]=map[0][5][7][6]='o';
    map[0][5][9][3]=map[0][5][9][4]='_';
    //Normal Classrooms^
    for(i=0;i<5;i++)
        for(j=0;j<8;j++)
            map[1][6][i][j]=white;
    for(i=0;i<6;i++)
        map[1][6][0][i+1]=green;
    map[0][6][2][0]=map[0][6][2][5]='[';
    map[0][6][2][1]=map[0][6][2][6]='_';
    map[0][6][2][2]=map[0][6][2][7]=']';
    map[0][6][3][1]=map[0][6][3][6]='o';
    map[0][6][4][3]=map[0][6][4][4]='_';
    //Secret Classrooms^
    for(i=0;i<7;i++)
        for(j=0;j<9;j++)
            map[1][7][i+1][j]=green;
    for(i=0;i<3;i++)
    {
        map[0][7][0][i]=map[0][7][0][i+6]='X';
        map[1][7][0][i+3]=white;
        map[0][7][0][i+3]='_';
    }
    map[1][7][8][1]=map[1][7][9][1]=white;
    map[0][7][8][1]=map[0][7][9][1]='=';
    for(i=0;i<4;i++)
        map[0][7][i+1][2]='|';
    map[0][7][1][6]='|';
    map[1][7][5][0]=map[1][7][5][2]=map[1][7][5][6]=map[1][7][2][6]=yellow;
    map[0][7][5][0]=map[0][7][5][2]=map[0][7][5][6]=map[0][7][2][6]='O';
    map[0][7][2][7]=map[0][7][2][8]=map[0][7][5][1]=map[0][7][5][3]=map[0][7][5][4]=map[0][7][5][5]='_';
    //Court yard^
    for(i=0;i<9;i++)
        for(j=0;j<11;j++)
            map[1][8][i][j]=white;
    for(i=0;i<2;i++)
        map[1][8][i][1]=map[1][8][i][3]=map[1][8][i][7]=blue;
    for(i=0;i<5;i++)
        map[1][8][2][i+3]=blue;
    for(i=0;i<4;i++)
        map[1][8][4][i+1]=map[1][8][4][i+6]=blue;
    map[1][8][5][1]=map[1][8][5][4]=map[1][8][5][6]=map[1][8][5][9]=blue;
    for(i=0;i<2;i++)
    {
        map[1][8][i+7][2]=map[1][8][i+7][8]=blue;
        map[0][8][5][i+2]=map[0][8][5][i+7]='o';
    }
    map[1][8][7][5]=map[1][8][1][2]=blue;
    for(i=0;i<9;i++)
        for(j=0;j<11;j++)
            if(map[1][8][i][j]==blue)
                map[0][8][i][j]='|';
    for(i=0;i<3;i++)
        map[0][8][i][10]='|';
    map[0][8][1][1]=map[0][8][2][3]=map[0][8][2][7]='o';
    map[0][8][1][2]='_';
    for(i=0;i<3;i++)
        map[0][8][2][i+4]='_';
    for(i=0;i<4;i++)
        map[0][8][4][i+1]=map[0][8][4][i+6]='_';
    for(i=0;i<2;i++)
        for(j=0;j<5;j++)
            map[0][8][i+7][j+3]='o';
    map[0][8][7][5]='_';
    //Court^
    for(i=0;i<23;i++)
        map[1][9][0][i]=white;
    map[0][9][0][0]=map[0][9][0][1]=map[0][9][0][22]='|';
    map[0][9][0][5]='M';
    map[0][9][0][6]='A';
    map[0][9][0][7]=map[0][9][0][8]='L';
    map[0][9][0][10]='T';
    map[0][9][0][11]='H';
    map[0][9][0][12]='I';
    map[0][9][0][13]='S';
    map[0][9][0][15]='W';
    map[0][9][0][16]='A';
    map[0][9][0][17]='Y';
    map[0][9][0][19]='-';
    map[0][9][0][20]='>';
    //Mall Entrance^
    for(k=0;k<2;k++)
    {
        for(i=0;i<9;i++)
            for(j=0;j<19;j++)
                map[1][k+10][i][j]=white;
        for(i=0;i<8;i++)
            for(j=0;j<21;j++)
                map[1][k+10][i+10][j+11]=white;
        for(i=0;i<7;i++)
            map[1][k+10][9][i+11]=white;
        for(i=0;i<5;i++)
            map[1][k+10][0][4*i+1]=map[1][k+10][17][4*i+12]=blue;
        for(i=0;i<3;i++)
            map[1][k+10][8][4*i+1]=map[1][k+10][4*i+1][18]=map[1][k+10][10][4*i+20]=blue;
        map[1][k+10][12][31]=map[1][k+10][15][31]=yellow;
        map[0][k+10][12][31]=map[0][k+10][15][31]='^';
        for(i=0;i<15;i++)
        {
            if(map[1][k+10][0][i+2]!=blue)
                map[0][k+10][0][i+2]='_';
            if(map[1][k+10][17][i+13]!=blue)
                map[0][k+10][17][i+13]='_';
        }
        for(i=0;i<7;i++)
        {
            if(map[1][k+10][8][i+2]!=blue)
                map[0][k+10][8][i+2]='_';
            if(map[1][k+10][10][i+21]!=blue)
                map[0][k+10][10][i+21]='_';
            if(map[1][k+10][i+2][18]!=blue)
                map[0][k+10][i+2][18]='|';
        }
        map[0][k+10][13][31]=map[0][k+10][14][31]=map[0][k+10][4][0]='|';
    }
    map[1][10][10][11]=map[1][10][15][11]=blue;
    for(i=0;i<4;i++)
            map[0][10][i+11][11]='|';
    //Mall G/F^
    map[1][11][12][11]=map[1][11][15][11]=yellow;
    map[0][11][12][11]=map[0][11][15][11]='v';
    for(i=0;i<2;i++)
            map[0][11][i+13][11]='|';
    map[0][11][4][0]=' ';
    //Mall 1/F^
    for(i=0;i<6;i++)
        for(j=0;j<10;j++)
            map[1][12][i][j]=white;
    for(k=0;k<3;k++)
    {
        map[0][12][2][3+2*k]=map[0][12][3][3+2*k]='|';
        map[0][12][1][3+2*k]=map[0][12][4][3+2*k]='x';
    }
    for(i=0;i<4;i++)
        map[0][12][i+1][9]='|';
    map[0][12][0][1]=map[0][12][1][1]='|';
    map[0][12][2][0]='_';
    map[0][12][2][1]='x';
    map[0][12][1][0]='O';
    map[1][12][0][9]=map[1][12][5][9]=blue;
    //Face right shop^
    for(i=0;i<8;i++)
        for(j=0;j<5;j++)
            map[1][13][i][j]=white;
    map[0][13][1][0]=map[0][13][5][0]=map[0][13][1][2]=map[0][13][3][4]=map[0][13][5][4]='x';
    map[0][13][2][0]=map[0][13][3][0]=map[0][13][4][0]=map[0][13][4][4]='|';
    map[0][13][0][3]='O';
    map[0][13][0][2]='|';
    map[0][13][1][3]=map[0][13][1][4]='_';
    for(i=0;i<3;i++)
        map[0][13][7][i+1]='_';
    map[1][13][7][0]=map[1][13][7][4]=blue;
    //Casier up shops^
    for(i=0;i<8;i++)
        for(j=0;j<5;j++)
        {
            map[1][14][i][j]=white;
            map[0][14][i][j]=map[0][13][7-i][4-j];
        }
    map[1][14][0][0]=map[1][14][0][4]=blue;
    //Casier down shops^
    for(i=0;i<9;i++)
        for(j=0;j<19;j++)
            map[1][15][i+1][j+1]=white;
    for(i=0;i<8;i++)
        for(j=0;j<21;j++)
            map[1][15][i+11][j+12]=white;
    for(i=0;i<8;i++)
        map[1][15][10][i+12]=white;
    for(i=0;i<4;i++)
        map[1][15][0][i+8]=white;
    map[0][15][0][8]='V';
    map[0][15][0][9]='I';
    map[0][15][0][10]='E';
    map[0][15][0][11]='W';
    for(i=0;i<3;i++)
    {
        map[1][15][i+4][0]=red;
        map[0][15][i+4][0]='!';
    }
    map[1][15][14][33]=map[1][15][15][33]=red;
    map[0][15][14][33]=map[0][15][15][33]='!';
    map[1][15][13][12]=map[1][15][16][12]=yellow;
    map[0][15][13][12]=map[0][15][16][12]='v';
    map[0][15][14][12]=map[0][15][15][12]='|';
    //Mall Roof^
    for(i=0;i<40;i++)
    {
        for(j=0;j<2;j++)
            map[1][16][j][i]=cyan;
        for(j=0;j<3;j++)
            map[1][16][j+2][i]=green;
    }
    for(i=0;i<10;i++)
    {
        map[0][16][2][4*i+1]=map[0][16][3][4*i]=map[0][16][3][4*i+1]=map[0][16][3][4*i+2]='^';
        map[0][16][4][4*i+1]='|';
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<2;j++)
            map[1][16][j][11*i+2]=map[1][16][j][11*i+3]=white;
        map[1][16][1][11*i+1]=map[1][16][1][11*i+4]=white;
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<2;j++)
            map[1][16][j][11*i+8]=map[1][16][j][11*i+9]=white;
        map[1][16][1][11*i+7]=map[1][16][0][11*i+10]=white;
    }
    map[0][16][0][38]=':';
    map[0][16][0][39]=')';
    //View^
    for(i=0;i<18;i++)
        for(j=0;j<31;j++)
            map[1][17][i][j]=yellow;
    map[1][17][0][0]=map[1][17][0][1]=white;
    map[0][17][0][0]=map[0][17][0][1]='|';
    map[1][17][1][0]=map[1][17][1][1]=black;
    for(k=0;k<3;k++)
    {
        for(i=0;i<14;i++)
            for(j=0;j<7;j++)
                map[1][17][i+4][9*k+j+3]=blue;
        map[1][17][4][9*k+3]=map[1][17][4][9*k+4]=map[1][17][4][9*k+9]=map[1][17][5][9*k+4]=yellow;
        for(i=0;i<7;i++)
            map[0][17][2][9*k+i+3]='x';
        map[0][17][3][9*k+3]=map[0][17][4][9*k+3]=map[0][17][4][9*k+9]='x';
        for(i=0;i<4;i++)
            map[0][17][3][9*k+i+5]='|';
        map[0][17][3][9*k+4]='\\';
        map[0][17][4][9*k+4]=map[0][17][5][9*k+4]='=';
        
    }
    map[1][17][17][0]=map[1][17][17][30]=blue;
    for(i=0;i<3;i++)
        for(j=0;j<31;j++)
            map[1][17][i+18][j]=blue;
    for(k=0;k<2;k++)
    {
        for(i=0;i<8;i++)
            for(j=0;j<5;j++)
            {
                map[1][17][i+7][9*k+j+4]=white;
            }
        for(i=0;i<2;i++)
            for(j=0;j<3;j++)
            {
                map[1][17][i+5][9*k+j+5]=white;
            }
        map[1][17][4][9*k+6]=white;
        map[1][17][15][9*k+4]=map[1][17][15][9*k+8]=white;
    }
    for(i=0;i<12;i++)
        for(j=0;j<14;j++)
            if(map[1][17][i+4][j+4]==white)
                map[0][17][i+4][j+4]='.';
    for(k=0;k<2;k++)
    {
        for(i=0;i<7;i++)
            for(j=0;j<3;j++)
                map[0][17][i+7][9*k+j+5]=' ';
        map[0][17][5][9*k+6]=map[0][17][6][9*k+6]=' ';
        map[0][17][14][9*k+5]=map[0][17][14][9*k+6]=map[0][17][14][9*k+7]='^';
    }
    for(i=0;i<12;i++)
        for(j=0;j<5;j++)
            if(map[1][17][i+4][j+13]==white)
                map[1][17][i+4][j+13]=red;
    map[0][17][8][6]='B';
    map[0][17][9][6]='O';
    map[0][17][10][6]='A';
    map[0][17][11][6]='T';
    map[0][17][8][15]='Y';
    map[0][17][9][15]='A';
    map[0][17][10][15]='C';
    map[0][17][11][15]='H';
    map[0][17][12][15]='T';
    //Pier^
    for(i=0;i<10;i++)
        for(j=0;j<20;j++)
            map[1][18][i+21][j]=green;
    for(i=0;i<5;i++)
        for(j=0;j<19;j++)
            map[1][18][i+16][j+1]=green;
    for(i=0;i<4;i++)
        for(j=0;j<18;j++)
            map[1][18][i+12][j+2]=green;
    for(i=0;i<2;i++)
        for(j=0;j<17;j++)
            map[1][18][i+10][j+3]=green;
    for(i=0;i<2;i++)
        for(j=0;j<16;j++)
            map[1][18][i+8][j+4]=green;
    for(k=0;k<5;k++)
        for(i=0;i<16-k;i++)
            map[1][18][8-k][19-i]=green;
    for(k=0;k<3;k++)
        for(i=0;i<10-2*k;i++)
            map[1][18][3-k][i+10+2*k]=green;
    map[1][18][0][18]=map[1][18][0][19]=red;
    for(i=0;i<4;i++)
        for(j=0;j<19;j++)
            map[1][18][i+27][j+1]=blue;
    for(k=0;k<2;k++)
    {
        for(i=0;i<2;i++)
            for(j=0;j<18-k;j++)
                map[1][18][i+25-2*k][j+2+k]=blue;
        for(i=0;i<16-k;i++)
            map[1][18][22-k][i+4+k]=blue;
    }
    for(k=0;k<4;k++)
        for(j=0;j<14-2*k;j++)
            map[1][18][20-k][j+6+2*k]=blue;
    for(i=0;i<5;i++)
        map[1][18][16][i+15]=blue;
    map[1][18][21][0]=map[1][18][16][1]=map[1][18][12][2]=map[1][18][8][4]=map[1][18][5][7]=map[1][18][2][12]=yellow;
    for(i=0;i<5;i++)
        map[1][18][i+1][17]=yellow;
    for(i=0;i<31;i++)
        for(j=0;j<20;j++)
            map[1][18][i][39-j]=map[1][18][i][j];
    for(i=0;i<62;i++)
        for(j=0;j<40;j++)
            if(map[1][18][i][j]==yellow)
                map[0][18][i][j]='^';
            else if(map[1][18][i][j]==red)
                map[0][18][i][j]='_';
    map[1][18][16][18]=map[1][18][17][18]=green;
    for(i=0;i<9;i++)
        for(j=0;j<5;j++)
            map[1][18][i+18][j+18]=black;
    for(i=0;i<12;i++)
        for(j=0;j<3;j++)
            map[1][18][i+16][j+19]=black;
    for(i=0;i<3;i++)
        map[1][18][i+21][17]=map[1][18][i+21][23]=black;
    map[1][18][28][20]=map[1][18][29][19]=map[1][18][29][21]=black;
    map[0][18][19][19]='S';
    map[0][18][19][20]='U';
    map[0][18][19][21]='B';
    for(i=0;i<3;i++)
        map[0][18][i+21][20]='|';
    for(i=0;i<6;i++)
        map[0][18][14][i+17]='x';
    map[0][18][15][17]='x';
    map[0][18][15][18]='\\';
    for(i=0;i<3;i++)
        map[0][18][15][i+19]='|';
    map[0][18][16][18]=map[0][18][17][18]=map[0][18][19][33]='=';
    //Secret Island^
    for(k=0;k<3;k++)
        for(i=0;i<3;i++)
            for(j=0;j<18-k;j++)
            map[1][19][16-3*k-i][k+j]=green;
    for(k=0;k<5;k++)
        for(j=0;j<15-k;j++)
            map[1][19][7-k][3+k+j]=green;
    for(k=0;k<3;k++)
        for(j=0;j<10-3*k;j++)
            map[1][19][2-k][8+j+3*k]=green;
    for(k=0;k<2;k++)
    {
        for(i=0;i<3;i++)
            map[1][19][16-i-2*k][8+k]=black;
        for(i=0;i<2;i++)
            map[1][19][12-i-k][10+k]=black;
        for(i=0;i<3;i++)
            map[1][19][9-k][12+2*k+i]=black;
    }
    map[1][19][10][12]=map[1][19][8][17]=black;
    for(i=0;i<8;i++)
       for(j=17;map[1][19][i+9][j]!=black;j--)
           map[1][19][i+9][j]=red;
    for(i=0;i<17;i++)
        for(j=0;j<18;j++)
            map[1][19][30-i][j]=map[1][19][i][j];
    for(i=0;i<35;i++)
        for(j=0;j<18;j++)
            map[1][19][i][35-j]=map[1][19][i][j];
    for(i=0;i<8;i++)
        for(j=0;j<2;j++)
            map[1][19][i+8][j+17]=blue;
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
            map[0][19][i+7][j+17]='=';
        map[1][19][7][3*i+16]=black;
    }
    map[1][19][30][15]=map[1][19][30][20]=yellow;
    map[0][19][30][15]=map[0][19][30][20]='^';
    for(i=0;i<4;i++)
        map[0][19][30][i+16]='_';
    //Volcano^
    for(i=0;i<9;i++)
        for(j=0;j<24;j++)
            map[1][20][i][j]=blue;
    for(i=0;i<7;i++)
        for(j=0;j<15;j++)
            map[1][20][i+1][j+1]=yellow;
    for(i=0;i<5;i++)
        for(j=0;j<4;j++)
            map[1][20][i+2][j+16]=yellow;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            map[1][20][i+3][j+20]=yellow;
    for(i=1;i<8;i++)
        for(j=1;j<23;j++)
            if(map[1][20][i][j]==yellow&&(map[1][20][i+1][j]==blue||map[1][20][i-1][j]==blue||map[1][20][i][j+1]==blue||map[1][20][i][j-1]==blue||map[1][20][i+1][j+1]==blue||map[1][20][i-1][j-1]==blue||map[1][20][i+1][j-1]==blue||map[1][20][i-1][j+1]==blue))
                map[0][20][i][j]='x';
    for(i=0;i<3;i++)
    {
        map[0][20][1][4*i+4]=map[0][20][7][4*i+4]='-';
        map[0][20][i+3][1]='|';
    }
    map[0][20][2][2]=map[0][20][6][2]=map[0][20][2][14]='O';
    for(i=0;i<4;i++)
        map[0][20][3][6+i]=map[0][20][5][6+i]='o';
    map[0][20][4][5]=map[0][20][4][10]='o';
    map[0][20][4][6]='[';
    map[0][20][4][9]=']';
    map[0][20][4][7]=map[0][20][4][8]=map[0][20][2][12]='-';
    map[0][20][2][11]=map[0][20][2][13]='>';
    map[0][20][3][15]=map[0][20][4][15]='x';
    map[0][20][5][15]=map[0][20][4][19]='|';
    map[0][20][5][18]='@';
    map[0][20][4][21]='?';
    //Sunken ship^
    for(i=0;i<9;i++)
        for(j=0;j<3;j++)
            map[1][21][i][j+4]=green;
    for(i=0;i<7;i++)
        for(j=0;j<2;j++)
            map[1][21][i+1][j+2]=map[1][21][i+1][j+7]=green;
    for(i=0;i<5;i++)
        map[1][21][i+2][1]=map[1][21][i+2][9]=green;
    map[1][21][4][0]=map[1][21][4][10]=green;
    map[0][21][2][2]=map[0][21][6][7]='O';
    map[0][21][2][4]=map[0][21][6][5]='-';
    map[0][21][2][3]=map[0][21][2][5]='<';
    map[0][21][6][4]=map[0][21][6][6]='>';
    for(i=0;i<3;i++)
        map[0][21][8][i+4]='_';
    //Ball room^
    for(i=0;i<3;i++)
        for(j=0;j<5;j++)
            map[1][22][i][j]=white;
    map[0][22][0][0]='[';
    map[0][22][0][2]=']';
    map[0][22][0][3]='-';
    map[0][22][0][4]='@';
    map[0][22][2][4]='|';
    //Reality^
}


int main()
{   
    srand(time(NULL));
    initialize();
    pos[0] = 1;
    pos[1] = 3;
    pos[2] = 1;
    pos[3] = 0;
    showmap();
    int num;
    while(1)
    {   FILE * stage;
        stage = fopen("ignoreme/one.txt","r+");
        fscanf(stage,"%d",&num);
        if(num == 000000000)
        {
            system("cls");
            say("...");
            say("......");
            say("7:30 a.m....");
            say("So today's my birthday.");
            say("My birthday cake was gone couple days ago...");
            say("I gotta find it before my birthday ends...");
            say("I better get up and meet my friends downstairs to find out who stole my cake.");
            rewind(stage);
            fprintf(stage,"%d",818776660);
            fclose(stage);
            showmap();
        }
        else if(num == 818776660)
        {
            while(pos[0]!=0)
                move();
            sleep(1000);
            system("cls");
            say("...");
            say("WHY IS NOBODY HERE?!");
            say("GUYS!!!!!");
            say("#^$%*f&%o^&@u$$@^n%&^d$*&$t#%h$&%i$^$%s%$^&$%&");
            say("I'm gonna find you guys!");
            rewind(stage);
            fprintf(stage,"%d",173910160);
            fclose(stage);
            system("cls");
            showmap();
            
        }
        else if(num==173910160)
        {
            char guy;
            rewind(stage);
            while(1)
            {
                guy=move();
                if(guy=='b')
                {
                    fprintf(stage,"%d",656704352);
                    break;
                }
                else if(guy=='c')
                {
                    fprintf(stage,"%d",585207357);
                    break;
                }
                else if(guy=='f')
                {
                    fprintf(stage,"%d",923272598);
                    break;
                }
                else if(guy=='g')
                {
                    fprintf(stage,"%d",453540160);
                    break;
                }
            }
            fclose(stage);
        }
        else if(num==656704352)
        {
            char guy;
            if(pos[0]==3)
            {
                system("cls");
                showmap();
                say("\n\nYou: Hey Bob, why didn't you come to...");
                showmap();
                say("\n\nBob: Hey did u see Gorge these days? I couldn't find him anywhere.");
                showmap();
                say("\n\nYou: Ehh...");
                showmap();
                say("\n\nBob: Hope he can get away with those loan sharks ha.");
                showmap();
                say("\n\nBob: By the way are you free today? Sorry that was stupid, you are certainly free today.");
                showmap();
                say("\n\nYou: Ehh...");
                showmap();
                say("\n\nBob: My friend's kinda running into some sort of trouble in the shopping mall.\nI need you to get him my suitcase if you know what I mean.\nI think u can find it at the volcano.");
                showmap();
                say("\n\nYou: Well...");
                showmap();
                say("\n\nBob: Cool, then off you go.");
                system("cls");
                say("Bob's mission #1\nFind the case(Indicated as \"X\") around the volcano area.\nGet the case to Bob's friend(Indicated as \"M\") in the mall.\nBe careful not to touch the guards(Indicated as \"O\") around the case.");
                showmap();
            }
            while(pos[0] != 19)
                move();
            int mon[2];
            map[0][19][15][18]='X';
            mon[0]=17;
            mon[1]=19;
            while(pos[0]!=19||pos[1]!=15||pos[2]!=18)
            {
                if(rand()%2==0);
                {
                    map[0][19][6][mon[0]] = map[0][19][6][mon[1]] = ' ';
                    mon[0] = 33-mon[0];
                    mon[1] = 37-mon[1];
                    map[0][19][6][mon[0]] = map[0][19][6][mon[1]] = 'O';
                    showmap();
                }
                if(kbhit())
                move();
                if(pos[1] == 6 && (pos[2] == mon[0] || pos[2] == mon[1]))
                {
                    pos[1] = 27;
                    pos[2] = 18;
                    showmap();
                }
            }
            map[0][19][15][18]=' ';
            map[0][19][6][mon[0]] = map[0][19][6][mon[1]] = ' ';
            map[0][15][1][19] = 'M';
            while(!(pos[0]==15&&((pos[1]==1&&pos[2]==18)||(pos[1]==2&&pos[2]==19))))
                move();
            showmap();
            say("\n\nM: Hey look it's the case! Thanks a lot pal!\nTell Bob that I've got it though. Bye!");
            map[0][15][1][19] = ' ';
            showmap();
            while(1)
            {
                guy=move();
                if(guy=='b')
                {
                    system("cls");
                    showmap();
                    say("\n\nBob: Heyy you survived! What a tough guy, what do you say you and I work together from now on huh?");
                    showmap();
                    say("\n\nYou: Ehh...");
                    showmap();
                    say("\n\nBob: OK I changed my mind, but keep the good work :D");
                    break;
                }
            }
            rewind(stage);
            fprintf(stage,"%d",107638522);
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            system("cls");
            showmap();
        }
        else if(num==107638522)
        {
            char guy;
            while(1)
            {
                guy=move();
                if(guy=='b')
                {
                    system("cls");
                    showmap();
                    say("\n\nBob: Hey man, I've got something for you.");
                    showmap();
                    say("\n\nYou: What is it?");
                    showmap();
                    say("\n\nBob: I've heard that the old man next door was sent to the hospital yesterday.\nRumor has it that he's got a large safe in his house.");
                    showmap();
                    say("\n\nYou: You mean Charlie? I thought...");
                    showmap();
                    say("\n\nThis time you'll be working with my man again, just bring me whatever's in the safe, cool?");
                    showmap();
                    say("\n\nEhh...");
                    showmap();
                    say("\n\nAlright! I'm waiting for good news!");
                    system("cls");
                    say("\n\nBob's mission #2\nMeet Bob's man(\"M\") in the mall.\nPay a visit to Charlie's house and crack his safe.");
                    showmap();
                    map[0][11][10][31]='M';
                    while(pos[0]!=11||!((pos[1]==10&&pos[2]==30)||(pos[1]==11&&pos[2]==31))) 
                        move();
                    showmap();
                    say("\n\nM: Hey! You Bob's man yeah? Cool let's roll.");
                    map[0][11][10][31]=' ';
                    showmap();
                    while(pos[0]!=3||map[0][3][2][2]!='C')
                        move();
                    system("cls");
                    int i,j;
                    printf("\n%2c",' ');
                    for(i=0;i<4;i++)
                    {
                        for(j=0;j<5;j++)
                        {
                            color(white);
                            if(map[0][3][i][j]!='C')
                                printf("%2c",map[0][3][i][j]);
                            else 
                                printf("%2c",' ');
                        }
                        color(black);
                        printf("\n%2c",' ');
                    }
                    color(white);
                    printf("%2c%2c%2c%2c%2c",' ','D','_','M',' ');
                    color(black);
                    say("...");
                    printf("\n%2c",' ');
                    for(i=0;i<4;i++)
                    {
                        for(j=0;j<5;j++)
                        {
                            color(white);
                            if(map[0][3][i][j]!='C')
                                printf("%2c",map[0][3][i][j]);
                            else 
                                printf("%2c",' ');
                        }
                        color(black);
                        printf("\n%2c",' ');
                    }
                    color(white);
                    printf("%2c%2c%2c%2c%2c",' ','D','_','M',' ');
                    color(black);
                    say("\n\nM: Alright! Here we go!");
                    char password[20] = {"@$^$#^CAKE*^#@!#@%^&"};
                    int time=clock();
                    int a=0;
                    while(1)
                    {
                        if(clock()-time>50)
                        {
                            time=clock();
                            cls();
                            for(i=a;i<a+4;i++)
                                printf("%2c",password[i]);
                            a=(a+1)%20;
                        }
                        if(kbhit())
                        {
                            getch();
                            sleep(1000);
                            if(a==6)
                                break;
                            else
                                a=rand()%16;
                        }
                    }
                    system("cls");
                    printf("\n%2c",' ');
                    for(i=0;i<4;i++)
                    {
                        for(j=0;j<5;j++)
                        {
                            color(white);
                            if(map[0][3][i][j]!='C')
                                printf("%2c",map[0][3][i][j]);
                            else 
                                printf("%2c",' ');
                        }
                        color(black);
                        printf("\n%2c",' ');
                    }
                    color(white);
                    printf("%2c%2c%2c%2c%2c",' ','D','_','M',' ');
                    color(black);
                    say("\n\nM: NICE! Now let's get this \"thing\" to Bob.");
                    showmap();
                    while(1)
                    {
                        guy=move();
                        if(guy=='b')
                        {
                            system("cls");
                            showmap();
                            say("\n\nBob: Awesome! Now let's open it and see what's so good inside!");
                            Sleep(2000);
                            say("...");
                            say("You: MY CAKE!!!!!!!!!!!!!!!!!!......\"3\"");       //maybe change to many 'M'
                            break;
                        }
                    }
                    break;
                }
                else if(guy!=0)
                    comment("\nYou can't do this person's quests right now. <SpaceBar>");
            }
            rewind(stage);
            fprintf(stage,"000000000");
            fclose(stage);
            return 0;
        }
        else if(num==585207357)
        {
            char guy;
            if(pos[0]==3)
            {
                system("cls");
                showmap();
                say("\n\nCharlie: ...");
                showmap();
                say("\n\nCharlie: ......");
                showmap();
                say("\n\nCharlie: Oh hey! Sorry I couldn't hear you. What brings you here young man?");
                showmap();
                say("\n\nYou: You know that cake you guys gave me? It was gone, and I didn't eat it.");
                showmap();
                say("\n\nCharlie: Hmm... What a bummer!\nUnfortunately I'm so busy right now, otherwise I'm more than willing to help you!");
                showmap();
                say("\n\nYou: How 'bout this, I help you with your stuff, you help me with mine.");
                showmap();
                say("\n\nCharlie: That actually sounds pretty good!");
                say("Charlie's mission #1\nGo to the supermarket(The largest store on G/F in the mall)\nGet all the stuff in red within 1min.");
                showmap();
            }
            while(pos[0]!=12)
                move();
            system("cls");
            int time,stuff,coor[2],time2;
            while(1)
            {
                showmap();
                say("\n\nOwner: Hey boy, wanna buy some stuff? You gotta hurry coz I'm closing!\nGo to the left hand side of the item you want.");
                showmap();
                time=clock();
                time2=time;
                stuff=0;
                coor[0]=rand()%2+2;
                coor[1]=2*(rand()%3)+3;
                map[1][12][coor[0]][coor[1]]=red;
                while(clock()-time<60000&&stuff<50)
                {
                    if(kbhit())
                    {
                        move();
                        printf("\n%d  \n%d/50",60-(clock()-time)/1000,stuff);
                    }
                    if(clock()-time2>1000)
                    {
                        time2=clock();
                        showmap();
                        printf("\n%d  \n%d/50",60-(clock()-time)/1000,stuff);
                    }
                    if(map[1][12][pos[1]][pos[2]+1]==red)
                    {
                        map[1][12][coor[0]][coor[1]]=white;
                        coor[0]=rand()%2+2;
                        coor[1]=2*(rand()%3)+3;
                        map[1][12][coor[0]][coor[1]]=red;
                        stuff++;
                    }
                }
                map[1][12][coor[0]][coor[1]]=white;
                if(stuff==50)
                    break;
                else
                {
                    system("cls");
                    showmap();
                    say("\n\nYou: Dang...");
                }
            }
            system("cls");
            showmap();
            say("\n\nYou: Cool! I've got all 20 items!");
            showmap();
            while(1)
            {
                guy=move();
                if(guy=='c')
                {
                    system("cls");
                    showmap();
                    say("\n\nCharlie: Good job on the groceries! I didn't expect you to get it done this fast!");
                    break;
                }
            }
            rewind(stage);
            fprintf(stage,"%d",167066756);
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            system("cls");
            showmap();
        }
        else if(num==167066756)
        {
            char guy;
            while(1)
            {
                guy=move();
                if(guy=='c')
                {
                    system("cls");
                    showmap();
                    say("\n\nCharlie: ...(Cough cough cough)...");
                    showmap();
                    say("\n\nYou: You OK there?");
                    showmap();
                    say("\n\nCharlie: Well... I'm sorry, but I think I'm sick... I think I need to go to the hospital...");
                    showmap();
                    say("\n\nYou: ...");
                    showmap();
                    say("\n\nCharlie: I'm wondering if you can take care of my cat Wicky?");
                    showmap();
                    say("\n\nYou: Alright... But my cake...");
                    showmap();
                    say("\n\nCharlie: Just be careful, she likes to scratch people.");
                    say("Charlie's mission #2\nKeep Wicky(\"W\") in your house but avoid touching\nHang in there for 2min.");
                    showmap();
                    while(pos[0]!=0)
                        move();
                    system("cls");
                    int cat[2];
                    int time,time2;
                    while(1)
                    {
                        cat[0]=0;
                        cat[1]=1;
                        time=clock();
                        time2=time;
                        map[0][0][cat[0]][cat[1]]='W';
                        showmap();
                        say("\n\nYou: There you are Wicky~");
                        while(clock()-time<120000&&!(pos[1]==cat[0]&&pos[2]==cat[1]))
                        {
                            if(kbhit())
                            {
                                move();
                                printf("\n%d  ",120-(clock()-time)/1000);
                            }
                            if(clock()-time2>500)
                            {
                                time2=clock();
                                map[0][0][cat[0]][cat[1]]=' ';
                                if((cat[0]-pos[1])*(cat[0]-pos[1])>(cat[1]-pos[2])*(cat[1]-pos[2]))
                                {
                                    if(cat[0]-pos[1]>0)
                                        cat[0]--;
                                    else if(cat[0]-pos[1]<0)
                                        cat[0]++;
                                }
                                else 
                                {
                                    if(cat[1]-pos[2]>0)
                                        cat[1]--;
                                    else if(cat[1]-pos[2]<0)
                                        cat[1]++;
                                }
                                map[0][0][cat[0]][cat[1]]='W';
                                showmap();
                                printf("\n%d  ",120-(clock()-time)/1000);
                            }
                        }
                        map[0][0][cat[0]][cat[1]]=' ';
                        system("cls");
                        showmap();
                        if(pos[1]==cat[0]&&pos[2]==cat[1])
                            say("\n\nYou: Dang...");
                        else
                        {
                            say("\n\nYou: Phew... That wasn't so hard~");
                            break;
                        }
                    }
                    while(1)
                    {
                        guy=move();
                        if(guy=='c')
                        {
                            system("cls");
                            showmap();
                            say("\n\nCharlie: Hey... (Cough cough), you did it!... Thank you...");
                            break;
                        }
                    }
                    break;
                }
                else if(guy!=0)
                    comment("\nYou can't do this person's quests right now. <SpaceBar>");
            }
            rewind(stage);
            fprintf(stage,"%d",419368867);
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            showmap();
        }
        else if(num==419368867)
        {
            char guy;
            while(1)
            {
                guy=move();
                if(guy=='c')
                {
                    system("cls");
                    showmap();
                    say("\n\nCharlie: Hey listen... I'm really sorry not being able to help you find your cake...");
                    showmap();
                    say("\n\nYou: It's OK, just take care.");
                    showmap();
                    say("\n\nCharlie: No you don't understand... I... Ughhhh!");
                    showmap();
                    say("\n\nYou: Charlie! Charlie!");
                    say("Charlie's mission #3\nCharlie's heart has stopped, you need to do CPR on him.\nBe careful, don't press too soft or too hard!");
                    int success=0,number,til,ran,time,i,input;
                    for(number=0;number<20;number++)
                    {
                        time=clock();
                        til=0;
                        ran=rand()%20;
                        while(1)
                        {
                            if(kbhit())
                            {
                                input=getch();
                                if(input==' ')
                                {
                                    if(til==ran)
                                        success++;
                                    sleep(500);
                                    break;
                                }
                            }
                            if(clock()-time>75)
                            {
                                til=(til+1)%20;
                                time=clock();
                                cls();
                                for(i=0;i<20;i++)
                                {
                                    if(i<=til)
                                        color(white);
                                    if(i==ran)
                                        printf("%2c",'O');
                                    else
                                        printf("%2c",'X');
                                    color(black);
                                }
                                printf("\n\n%d/20",success);
                                printf("\n\n%d  %d  ",ran,til);
                            }       
                        }
                    }
                    system("cls");
                    sleep(1000);
                    if(success>=15)
                    {
                        say("Charlie! Wake up!");
                        sleep(2000);
                        showmap();
                        say("\n\nCharlie: (Cough)... What happened...?");
                        showmap();
                        say("\n\nYou: Your heart stopped beating so I did a CPR on you...");
                        showmap();
                        say("\n\nCharlie: Thank you... for saving my life...");
                        showmap();
                        say("\n\nYou: Glad you're fine...");
                        showmap();
                        say("\n\nYou: By the way... You gonna tell me where's my cake now?");
                        showmap();
                        say("\n\nCharlie: I... I have no idea... I'll help you find it... maybe...");
                        say("...");
                    }
                    else
                    {
                        say("...");
                        say("CHARLIE!!");
                        rewind(stage);
                        fprintf(stage,"000000000");
                        fclose(stage);
                        return 0;
                    }
                    break;
                }
                else if(guy!=0)
                    comment("\nYou can't do this person's quests right now. <SpaceBar>");
            }
            rewind(stage);
            fprintf(stage,"%d",552050506);
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            showmap();
        }
        else if(num==552050506)
        {
            map[0][8][1][5]=='P';
            char guy;
            while(1)
            {
                guy=move();
                if(guy=='p')
                {
                    system("cls");
                    showmap();
                    say("\n\nPolice: How may I help you?");
                    showmap();
                    say("\n\nYou: I want to report someone for stealing my cake.");
                    showmap();
                    say("\n\nPolice: Well... OK... Who do you wanna report?\n(Type letter or <esc>)");
                    int input;
                    while(input!=esc)
                    {
                        showmap();
                        printf("\n\n");
                        input=getch();
                        if(input=='c')
                        {
                            system("cls");
                            sleep(5000);
                            say("Local news report: A recent cake thief has been captured and charged for intentional self-feeding, the cake has returned to its owner...");
                            sleep(2000);
                            break;
                        }
                        else if(input=='d')
                            say("Police: Yea right.");
                        else if(input>='a'&&input<='i')
                        {
                            system("cls");
                            sleep(5000);
                            say("You bastard! I trusted you all along and now you're not believing in me?! Die!......\"5\"");
                            say("BANG!");
                            say("...");
                            sleep(2000);
                            break;
                        }
                    }
                }
                break;
            }
            rewind(stage);
            fprintf(stage,"000000000");
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            showmap();
        }
        else if(num==923272598)         
        {
            char guy;
            if(pos[0]==3)
            {
                system("cls");
                showmap();
                say("\n\nFred: Hey what are you doing here, don't get in my way, I'm in trouble now.");
                showmap();
                say("\n\nYou: Tell me brother, what is it?");
                showmap();
                say("\n\nFred: There's this manatee in my store in the mall, but he's missing now. I gotta find him.");
                showmap();
                say("\n\nYou: Maybe I can help you find him if you can help me with...");
                showmap();
                say("\n\nFred: Really? That'd be great! But please, be fast!");
                showmap();
                say("\n\nYou: ...");
                say("Fred's mission #1\nFind Fred's manatee(\"T\"), he could be anywhere!\nGet back to Fred in 2mins!");
            }
            int time,time2;
            while(1)
            {
                showmap();
                map[0][6][0][7]='T';
                time=clock();
                time2=time;
                while(clock()-time<120000&&pos[0]!=6)
                {
                    if(kbhit())
                    {
                        move();
                        printf("\n\n%d",120-(clock()-time)/1000);
                    }
                    if(clock()-time2>1000)
                    {
                        time2=clock();
                        showmap();
                        printf("\n\n%d",120-(clock()-time)/1000);
                    }
                }
                system("cls");
                showmap();
                if(pos[0]==6)
                {
                    say("\n\nYou: There you are!");
                    map[0][6][0][7]=' ';
                    showmap();
                }
                else
                {
                    say("\n\nYou: Dang...");
                    continue;
                }
                while(clock()-time<120000&&!(pos[0]==3&&map[0][3][2][2]=='F'))
                {
                    if(kbhit())
                    {
                        move();
                        printf("\n\n%d",120-(clock()-time)/1000);
                    }
                    if(clock()-time2>1000)
                    {
                        time2=clock();
                        showmap();
                        printf("\n\n%d",120-(clock()-time)/1000);
                    }
                }
                system("cls");
                showmap();
                if(pos[0]==3&&map[0][3][2][2]=='F')
                {
                    say("\n\nFred: That's fabulous! Thanks for the help!");
                    break;
                }
                else
                    say("\n\nYou: Dang...");
            }
            rewind(stage);
            fprintf(stage,"%d",222076849);
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            showmap();
        }
        else if(num==222076849)
        {
            char guy;
            while(1)
            {
                guy=move();
                if(guy=='f')
                {
                    system("cls");
                    showmap();
                    say("\n\nFred: Hey buddy, I've got a good news for you!");
                    showmap();
                    say("\n\nYou: Really?! Did you find my...");
                    showmap();
                    say("\n\nFred: Tomorrow my manatee's 2years and 45days old! Isn't it exciting?");
                    showmap();
                    say("\n\nYou: ...@#&^$%$&%$%@...");
                    showmap();
                    say("\n\nFred: Here's what I think: you go get a birthday cake for him,\nand I'm gonna think where to put the cake... :)");
                    showmap();
                    say("\n\nYou: ._________________. Alright.");
                    say("Fred's mission #2\nSimple one, go to the bakery store and choose a cake for Fred's manatee.\nBe careful, get the one that is edible for animals!");
                    while(!(pos[0]==14&&buffpos[0]==11&&buffpos[1]==8&&buffpos[2]>1&&buffpos[2]<5))
                        move();
                    showmap();
                    say("\n\nCake Shop Owner: Welcome to Blah Bakery! How can I help you?");
                    showmap();
                    say("\n\nYou: I wanna buy a cake... not for me.");
                    showmap();
                    say("\n\nCake Shop Owner: Sure! Which one do you want?(1-3)\n");
                    char input=0;
                    while(input<'1'&&input>'3')
                        input=getch();
                    showmap();
                    say("\n\nCake Shop Owner: Here you go!Good luck :o)");
                    while(1)
                    {
                        guy=move();
                        if(guy=='f')
                        {
                            system("cls");
                            showmap();
                            say("\n\nFred: Great! Here you are! Let's see what you got for my dear manatee.");
                            sleep(2000);
                            if(input==1)
                            {
                                showmap();
                                say("\n\nFred: Look! He likes it!! Thanks man!");
                                break;
                            }
                            else
                            {
                                say("Fred: Manatee...?");
                                say("Fred: Manatee!!");
                                say("You killed my manatee!!! How could you!!!");
                                say("You: I...");
                                say("Unforgivable! Die!!!");
                                say("BANG");
                                sleep(5000);
                                rewind(stage);
                                fprintf(stage,"000000000");
                                fclose(stage);
                                return 0;
                            }
                        }
                    }
                    break;
                }
                else if(guy!=0)
                    comment("\nYou can't do this person's quests right now. <SpaceBar>");
            }
            rewind(stage);
            fprintf(stage,"%d",100114448);
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            showmap();
        }
        else if(num==100114448)
        {
            char guy;
            while(1)
            {
                guy=move();
                if(guy=='f')
                {
                    system("cls");
                    showmap();
                    say("\n\nFred: Hey! Good to see you again! Tell you what, I'm going to visit the volcano tomorrow!");
                    showmap();
                    say("\n\nYou: But what about your store?");
                    showmap();
                    say("...............");
                    showmap();
                    say("\n\nFred: How about you take the place... Yeah! See? I've thought about it!");
                    showmap();
                    say("\n\nYou: But I...");
                    showmap();
                    say("\n\nFred: Come on, help your good 'ol friend out here :')");
                    say("Fred's mission #3\nHelp Fred to manage his pet store on the upper right corner on 1/F.\nCalm the pets when they are angry(Red)");
                    showmap();
                    while(!(buffpos[0]==11&&buffpos[1]==10&&buffpos[2]>24&&buffpos[2]<28))
                        move();
                    showmap();
                    say("Alright... I'm on my own now... But let's do this.");
                    int time,time2,time3;
                    int pet,number;
                    while(1)
                    {
                        time=clock();
                        time2=time;
                        pet=rand()%4;
                        if(pet<3)
                            map[1][13][2+pet][0]=red;
                        else 
                            map[1][13][4][4]=red;
                        while(clock()-time<120000)
                        {
                            if(kbhit())
                            {
                                move();
                                if(map[1][13][pos[1]][pos[2]-1]==red||map[1][13][pos[1]][pos[2]+1]==red)
                                {
                                    map[1][13][pos[1]][pos[2]-1]=map[1][13][pos[1]][pos[2]+1]=white;
                                    pet=rand()%4;
                                    if(pet<3)
                                    map[1][13][2+pet][0]=red;
                                    else 
                                    map[1][13][4][4]=red;
                                    time3=clock();
                                }
                                
                            }
                            if(clock()-time2>1000)
                            {
                                showmap();
                                printf("\n\n%d  ",120-(clock()-time)/1000);
                            }
                            if(clock()-time3>1000)
                            {
                                map[1][13][pos[1]][pos[2]-1]=map[1][13][pos[1]][pos[2]+1]=white;
                                showmap();
                                say("\n\nDang...");
                                continue;
                            }
                        }
                        map[1][13][pos[1]][pos[2]-1]=map[1][13][pos[1]][pos[2]+1]=white;
                        showmap();
                        say("I made it! Yeah!");
                        break;
                    }
                    while(!(pos[0]==3&&map[0][3][2][2]=='F'))
                        move();
                    system("cls");
                    sleep(2000);
                    say("\n\nYou: Fred...?");
                    say("\n\nDCPD! Freeze!");
                    say("\n\nYou: What?! What happened?");
                    say("\n\nYou are now under arrest as a suspect of Fred F.'s murder!");
                    say("\n\nYou: ... WHAT?!");
                    say("\n\nFred's body was found under the sea in the volcano area!");
                    say("\n\nYou: I...");
                    say("Stop talking! GET OVER HERE!......\"6\"");
                    say("...");
                    sleep(2000);
                    rewind(stage);
                    fprintf(stage,"000000000");
                    fclose(stage);
                    return 0;
                }
                else if(guy!=0)
                    comment("\nYou can't do this person's quests right now. <SpaceBar>");
            }
            
        }
        else if(num==453540160)
        {
            char guy;
            if(pos[0]==3)
            {
                system("cls");
                showmap();
                say("\n\nGeorge: 'Sup homie?");
                showmap();
                say("\n\nYou: I'm trying to find my cake... it's been gone for days...");
                showmap();
                say("\n\nGeorge: Cakes? I ain't saw no cakes! Now Imma do sth real big here you know what I'm sayin'?");
                showmap();
                say("\n\n(Door smashing, light went out)");
                showmap();
                say("\n\nGeorge: Oh Sh...!");
                showmap();
                say("\n\nGeorge: Alright homie, you wanna know where yo cake went,\nyou better make sure I get out here safe you know what I'm sayin'?");
                say("George's mission #1\nGet George out of his house by giving him directions.\nFollow the intructions and press the same arrow keys in 5seconds.\nGet all correct to pass.");
            }
            int success,i,j,time,input,til;
            char dir[10];
            while(1)
            {
                success=0;
                for(i=0;i<20;i++)
                {
                    system("cls");
                    til=0;
                    for(j=0;j<10;j++)
                    {
                        dir[j]=rand()%4;
                        if(dir[j]==0)
                            dir[j]='^';
                        else if(dir[j]==1)
                            dir[j]='v';
                        else if(dir[j]==2)
                            dir[j]='>';
                        else if(dir[j]==3)
                            dir[j]='<';
                        printf("%2c",dir[j]);
                    }
                    printf("\n\n%d/%d  ",success,20-i);
                    time=clock();
                    while(clock()-time<5000&&til<10)
                    {
                        if(kbhit())
                        {
                            input=get_code();
                            fseek(stdin,0,SEEK_END);
                            cls();
                            if(input==up&&dir[til]=='^')
                                til++;
                            else if(input==down&&dir[til]=='v')
                                til++;
                            else if(input==left&&dir[til]=='<')
                                til++;
                            else if(input==right&&dir[til]=='>')
                                til++;
                            else if(til>0)
                                til--;
                            cls();
                            for(j=0;j<10;j++)
                            {
                                if(j<til)
                                    color(white);
                                printf("%2c",dir[j]);
                                color(black);
                            }
                            printf("\n\n%d/%d  ",success,20-i);
                        }
                    }
                    fseek(stdin,0,SEEK_END);
                    if(til==10)
                        success++;
                }
                system("cls");
                showmap();
                if(success==20)
                {
                    say("\n\nGeorge: Phew, thanks for the help homie, I owe you once.");
                    break;
                }
                else
                    say("\n\nDang...");
            }
            rewind(stage);
            fprintf(stage,"%d",279607743);
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            showmap();
        }
        else if(num==279607743)
        {
            char guy;
            while(1)
            {
                guy=move();
                if(guy=='g')
                {
                    system("cls");
                    showmap();
                    say("\n\nGeorge: Hey homie, thanks for the help again.");
                    showmap();
                    say("\n\nYou: No problem, now can you help me find my cake?");
                    showmap();
                    say("\n\nGeorge: Cake? What cake?");
                    showmap();
                    say("\n\nYou: ...");
                    showmap();
                    say("\n\nGeorge: Anyway, I know a casino in the mall, we gon' make big money in there you know what I'm sayin?");
                    showmap();
                    say("\n\nGeorge: When you get big money you can go buy the \"Cake\" or somethin you know what I'm sayin?");
                    showmap();
                    say("\n\nYou: ._.");
                    say("George's mission #2\nMeet George in the casino in the top left corner on 1/F\nPlay black jack and win $1000.");
                    showmap();
                    while(!(pos[0]==13&&buffpos[0]==11&&buffpos[1]==1&&buffpos[2]>1&&buffpos[2]<5))
                        move();
                    map[0][13][4][2]='G';
                    showmap();
                    say("\n\nGeorge: Yo homie you know how to play black jack?\nIt's easy, you draw cards, you win, you earn money.");
                    int money,i,card[3],opp;
                    char input;
                    while(1)
                    {
                        money=0;
                        for(i=0;i<50;i++)
                        {
                            input=0;
                            system("cls");
                            card[0]=rand()%13+1;
                            card[1]=rand()%13+1;
                            if(card[0]>10)
                                card[0]=10;
                            if(card[1]>10)
                                card[1]=10;
                            if(card[0]==1&&card[1]<=10)
                                card[0]=11;
                            else if(card[1]==1&&card[0]<=10)
                                card[1]=11;
                            opp=card[0]+card[1];
                            
                            card[0]=rand()%13+1;
                            card[1]=rand()%13+1;
                            card[2]=rand()%13+1;
                            if(card[0]>10)
                                card[0]=10;
                            if(card[1]>10)
                                card[1]=10;
                            if(card[2]>10)
                                card[2]=10;
                            while(1)
                            {
                                showmap();
                                printf("\n\nYou: %d  %d  \nOpponent:\nMoney: %d\nTrials: %d\n\n<D>raw   <H>old",card[0],card[1],money,50-i);
                                input=getch();
                                if(input=='d')
                                {
                                    if(card[0]==1&&card[1]+card[2]<=10)
                                        card[0]=11;
                                    else if(card[1]==1&&card[0]+card[2]<=10)
                                        card[1]=11;
                                    else if(card[2]==1&&card[0]+card[1]<=10)
                                         card[2]=11;
                                    break;
                                }
                                else if(input=='h')
                                {
                                    if(card[0]==1&&card[1]<=10)
                                        card[0]=11;
                                    else if(card[1]==1&&card[0]<=10)
                                        card[1]=11;
                                    card[2]=0;
                                    break;
                                }
                            }
                            system("cls");
                            showmap();
                            printf("\n\nYou: %d  \nOpponent: %d  \nMoney: %d\nTrials: %d",card[0]+card[1]+card[2],opp,money,50-i);
                            sleep(2000);
                            if(card[0]+card[1]+card[2]<=21&&card[0]+card[1]+card[2]>=opp)
                                money+=25;
                        }
                        if(money>1000)
                        {
                            say("\n\nYou: Awesome!");
                            showmap();
                            say("\n\nGeorge: Awesome! Now gimme yo money fool!");
                            break;
                        }
                        else
                            say("\n\nCrap...");
                    }
                    map[0][13][4][2]=' ';
                    break;
                }
                else if(guy!=0)
                    comment("\nYou can't do this person's quests right now. <SpaceBar>.");
            }
            rewind(stage);
            fprintf(stage,"%d",72961321);
            fclose(stage);
            printf("Autosaved");
            while(getch()!=13);
            showmap();
        }
        else if(num==72961321)
        {
            char guy;
            while(1)
            {
                guy=move();
                if(guy=='g')
                {
                    system("cls");
                    showmap();
                    say("\n\nGeorge: Alright listen, this is going to be the biggest plan I have.");
                    showmap();
                    say("\n\nYou: I...");
                    showmap();
                    say("\n\nGeorge: Shhh... Meet me at the casino.");
                    say("George's mission #3\nMeet George at the casino and prepare for the biggest challenge.");
                    showmap();
                    while(!(pos[0]==13&&buffpos[0]==11&&buffpos[1]==1&&buffpos[2]>1&&buffpos[2]<5))
                        move();
                    map[0][13][4][2]='H';
                    map[0][13][6][1]='G';
                    showmap();
                    say("\n\nHost: Ladies and Gentlemen, in front of you lies the biggest diamond in the world.");
                    showmap();
                    say("\n\nHost: In order to win it, you must gamble with your life! Now anyone wants to try?");
                    showmap();
                    say("\n\n(You got pushed to the front)");
                    showmap();
                    say("\n\nHost: Looks like we have a challenger!!!");
                    showmap();
                    say("\n\nYou: ...");
                    showmap();
                    say("\n\nHost: Next to the diamond there's 5 cards\nOne has \"O\" at the back, and the others has \"X\".");
                    showmap();
                    say("\n\nHost: If you get the O card, you win the diamond! But if you get the X card...");
                    int input=0,ind=0,i;
                    while(input!=13)
                    {
                        showmap();
                        printf("\n\n");
                        for(i=0;i<5;i++)
                        {
                            if(i==ind)
                                color(white);
                            printf("%2c",'?');
                            color(black);
                        }
                        input = get_code();
                        if(input==left&&ind>0)
                            ind--;
                        else if(input == right && ind<4)
                            ind++;
                    }
                    input = rand()%5;
                    showmap();
                    printf("\n\n");
                    for(i=0;i<5;i++)
                    {
                        if(i==ind)
                            color(white);
                        if(i==input)
                            printf("%2c",'O');
                        else
                            printf("%2c",'X');
                        color(black);
                    }
                    while(getch()!=13);
                    system("cls");
                    sleep(5000);
                    if(input==ind)
                    {
                        showmap();
                        say("\n\nHost: Congradulations!! This man just won the biggest diamond in the world!");
                        say("...");
                        say("BOOM!");
                        say("Robbery!!");
                        showmap();
                        say("\n\nRobber: This is a great week! First a cake, then a diamond!");
                        showmap();
                        say("\n\nYou: It's you!");
                        showmap();
                        say("\n\nRobber: Oh hey there b-day boy, too bad you can't see the cake ever again!");
                        say("BANG!!......\"2\"");
                        say("...");
                        sleep(5000);
                    }
                    else
                    {
                        say("Host: ... Sorry boy...");
                        say("BANG!!!");
                        sleep(5000);
                    }
                    break;
                }
                else if(guy!=0)
                    comment("\nYou can't do this person's quests right now. <SpaceBar>.");
            }
            rewind(stage);
            fprintf(stage,"000000000");
            fclose(stage);
            return 0;
        }
    }
}
