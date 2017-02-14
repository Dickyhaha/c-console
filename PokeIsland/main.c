#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char map[10][2][17][31];
char dialogue[12][100];
char quest[5][2][22][31]; 
char quests[5][20]={{"Out of fur...\0"},{"The hunger...\0"},{"Threats to us!\0"},{"The chosen one!\0"},{"The ultimate Rush!\0"}};
int pos[12][3]={{0,1,8},{0,2,2},{0,9,12},{0,15,6},{1,1,2},{1,1,4},{1,2,1},{1,2,2},{6,1,13},{8,2,10},{8,2,10},{8,2,15}};
int talk[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int mon[11][2];
int pmap,pi,pj,radius=4,stage,qnum=-1,done=0,maxhp,maxmp,basicatt,basicdef,bonusatt,bonusdef;
int lv,xp,hp,mp,att,def,money;
int a1num=0,a2num=0,a3num=0,a4num=0,a5num=0;

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


void show(char words[],int time)
{
    printf("%s",words);
    sleep(time);
    system("cls");
}

void showmission()
{
    if(qnum==0)
    {
        if(a1num+a2num+a3num+a4num==20)
        {
            done=1;
            printf("Quest 1 completed, go back to the mayor and claim your reward!\n__________________________\n\n");
            a1num=a2num=a3num=a4num=0;
        }
        else
            printf(" Fur collected: %d/20\n__________________________\n\n",a1num+a2num+a3num+a4num);
        
    }
    else if(qnum==1)
    {
        
        if(a2num==30)
        {
            done=1;
            printf("Quest 2 completed, go back to the mayor and claim your reward!\n__________________________\n\n");
            a1num=a2num=a3num=a4num=0;
        }
        else
            printf(" Meat collected: %d/30\n__________________________\n\n",a2num);
    }
    else if(qnum==2)
    {
        if(a3num==15&&quest[2][0][3][2]==' '&&quest[2][0][2][3]==' '&&quest[2][0][2][4]==' '&&quest[2][0][3][5]==' ')
        {
            done=1;
            printf("Quest 3 completed, go back to the mayor and claim your reward!\n__________________________\n\n");
            a1num=a2num=a3num=a4num=0;
        }
        else
            printf(" Spirit collected: %d/11\n__________________________\n\n",a3num);
    }
    else if(qnum==3)
    {
        if(a4num==12)
        {
            done=1;
            printf("Quest 4 completed, go back to the mayor and claim your reward!\n__________________________\n\n");
            a1num=a2num=a3num=a4num=0;
        }
        else
            printf(" Monsters killed: %d/12\n__________________________\n\n",a4num);
    }
    else if(qnum==4)
    {
        if(a1num==10&&a2num==10&&a3num==15&&a4num==12&&a5num==6)
        {
            done=1;
            printf("Quest 5 completed, go back to the mayor and claim your reward!\n__________________________\n\n");
            a1num=a2num=a3num=a4num=0;
        }
        else 
            printf("Area 1: %d/10   Area 2: %d/10   Area 3: %d/15   Area 4: %d/12   Area 5: %d/16\n__________________________\n\n",a1num,a2num,a3num,a4num,a5num);
    }
    else
    {
        printf("\n__________________________\n");
    }
}

void showmap()
{
    int i,j,radi=radius;
    if(pmap==6)
        radi=1;
    showmission();
    for(i=pi-radi;i<pi+radi+1;i++)
    {
        for(j=pj-radi;j<pj+radi+1;j++)
        {
            if(i<0||j<0||i>=17||j>=31)
            {
                color(black);
                printf("%2c",' ');
            }
            else if(i==pi&&j==pj)
            {
                color(purple);
                printf("%2c",'G');
            }
            else
            {
                color(map[pmap][1][i][j]);
                printf("%2c",map[pmap][0][i][j]);
            }
        }
        printf("\n");
    }
    color(black);
    printf("\n__________________________\n");;
}


void say(char word[])
{
    system("cls");
    showmap();
    printf("\n");
    show(word,3000);
}

void save(int i)
{
    FILE * pdata;
    pdata=fopen("ignoreme/position.txt","r+");
    fprintf(pdata,"%d %d %d %d %d  ",pmap,pi,pj,stage,i);
    fclose(pdata);
}

void savestat()
{
    FILE * stats;
    stats=fopen("ignoreme/stat.txt","r+");
    fprintf(stats,"%d\n%d\n%d\n%d\n%d\n%d\n%d",xp,maxhp,maxmp,basicatt,basicdef,bonusatt,bonusdef);
    fclose(stats);
    
    FILE *monay;
    monay=fopen("ignoreme/money.txt","r+");
    fprintf(monay,"%d",money);
    fclose(monay);
}

void calstat(int add)
{
    xp+=add;
    for(lv=0;lv<=25;lv++)
        if(50+lv*(5+lv)*10>xp)
            break;
    maxhp=50+lv*(lv+4);
    maxmp=20+4*lv;
    basicatt=5+lv*(lv+1)/2;
    basicdef=lv;
    savestat();
}

void move(int area,int qi,int qj)
{
    srand(time(NULL));
    int dir,i;
    if(area==0)
    {
        for(i=0;i<8;i++)
        {
            while(1)
            {
                quest[area][0][mon[i][0]][mon[i][1]]=' ';
                dir=rand()%5;
                if(dir==0&&quest[area][0][mon[i][0]-1][mon[i][1]]==' '&&mon[i][0]-1!=qi&&mon[i][1]!=qj)
                {
                    mon[i][0]--;
                    break;
                }
                else if(dir==1&&quest[area][0][mon[i][0]+1][mon[i][1]]==' '&&mon[i][0]+1!=qi&&mon[i][1]!=qj)
                {
                    mon[i][0]++;
                    break;
                }
                else if(dir==2&&quest[area][0][mon[i][0]][mon[i][1]-1]==' '&&mon[i][1]>3&&mon[i][0]!=qi&&mon[i][1]-1!=qj)
                {
                    mon[i][1]--;
                    break;
                }
                else if(dir==3&&quest[area][0][mon[i][0]][mon[i][1]+1]==' '&&mon[i][1]<17&&mon[i][0]!=qi&&mon[i][1]+1!=qj)
                {
                    mon[i][1]++;
                    break;
                }
                else if(dir==4)
                    break;
            }
            quest[area][0][mon[i][0]][mon[i][1]]='M';
        }
    }
    else if(area==1)
    {
        for(i=0;i<7;i++)
        {
            while(1)
            {
                quest[area][0][mon[i][0]][mon[i][1]]=' ';
                dir=rand()%5;
                if(dir==0&&quest[area][0][mon[i][0]-1][mon[i][1]]==' '&&mon[i][0]-1!=qi&&mon[i][1]!=qj)
                {
                    mon[i][0]--;
                    break;
                }
                else if(dir==1&&quest[area][0][mon[i][0]+1][mon[i][1]]==' '&&mon[i][0]+1!=qi&&mon[i][1]!=qj)
                {
                    mon[i][0]++;
                    break;
                }
                else if(dir==2&&quest[area][0][mon[i][0]][mon[i][1]-1]==' '&&mon[i][1]>3&&mon[i][1]!=7&&mon[i][0]!=qi&&mon[i][1]-1!=qj)
                {
                    mon[i][1]--;
                    break;
                }
                else if(dir==3&&quest[area][0][mon[i][0]][mon[i][1]+1]==' '&&mon[i][1]<15&&mon[i][1]!=6&&mon[i][0]!=qi&&mon[i][1]+1!=qj)
                {
                    mon[i][1]++;
                    break;
                }
                else if(dir==4)
                    break;
            }
            quest[area][0][mon[i][0]][mon[i][1]]='M';
        }
    }
    else if(area==2)
    {
        for(i=0;i<11;i++)
        {
            while(1)
            {
                quest[area][0][mon[i][0]][mon[i][1]]=' ';
                dir=rand()%5;
                if(dir==0&&quest[area][0][mon[i][0]-1][mon[i][1]]==' '&&mon[i][0]-1!=qi&&mon[i][1]!=qj)
                {
                    mon[i][0]--;
                    break;
                }
                else if(dir==1&&quest[area][0][mon[i][0]+1][mon[i][1]]==' '&&mon[i][0]+1!=qi&&mon[i][1]!=qj)
                {
                    mon[i][0]++;
                    break;
                }
                else if(dir==2&&quest[area][0][mon[i][0]][mon[i][1]-1]==' '&&mon[i][1]>3&&!(mon[i][0]>7&&mon[i][1]==9)&&mon[i][0]!=qi&&mon[i][1]-1!=qj)
                {
                    mon[i][1]--;
                    break;
                }
                else if(dir==3&&quest[area][0][mon[i][0]][mon[i][1]+1]==' '&&mon[i][0]!=qi&&mon[i][1]+1!=qj)
                {
                    mon[i][1]++;
                    break;
                }
                else if(dir==4)
                    break;
            }
            quest[area][0][mon[i][0]][mon[i][1]]='M';
        }
    }
    else if(area==3)
    {
        for(i=0;i<7;i++)
        {
            while(1)
            {
                quest[area][0][mon[i][0]][mon[i][1]]=' ';
                dir=rand()%5;
                if(dir==0&&quest[area][0][mon[i][0]-1][mon[i][1]]==' '&&mon[i][0]-1!=qi&&mon[i][1]!=qj)
                {
                    mon[i][0]--;
                    break;
                }
                else if(dir==1&&quest[area][0][mon[i][0]+1][mon[i][1]]==' '&&mon[i][0]!=10&&mon[i][0]+1!=qi&&mon[i][1]!=qj)
                {
                    mon[i][0]++;
                    break;
                }
                else if(dir==2&&quest[area][0][mon[i][0]][mon[i][1]-1]==' '&&mon[i][1]>3&&mon[i][0]!=qi&&mon[i][1]-1!=qj)
                {
                    mon[i][1]--;
                    break;
                }
                else if(dir==3&&quest[area][0][mon[i][0]][mon[i][1]+1]==' '&&mon[i][0]!=qi&&mon[i][1]+1!=qj)
                {
                    mon[i][1]++;
                    break;
                }
                else if(dir==4)
                    break;
            }
            quest[area][0][mon[i][0]][mon[i][1]]='M';
        }
    }
}

void showquest(int qmap,int qi,int qj)
{
    int radius=4,i,j;
    if(qmap==4)
        radius=5;
    system("cls");
    showmission();
    for(i=qi-radius;i<qi+radius+1;i++)
    {
        for(j=qj-radius;j<qj+radius+1;j++)
        {
            if(i<0||j<0||i>=22||j>=31)
            {
                color(black);
                printf("%2c",' ');
            }
            else if(i==qi&&j==qj)
            {
                color(purple);
                printf("%2c",'P');
            }
            else if(quest[qmap][0][i][j]=='M')
            {
                color(red);
                printf("%2c",'M');
            }
            else
            {
                color(quest[qmap][1][i][j]);
                printf("%2c",quest[qmap][0][i][j]);
            }
        }
        printf("\n");
    }
    color(black);
    printf("__________________________\n HP: %d/%d   MP: %d/%d   \n AD: %d(+%d) ARM: %d(+%d)\n__________________________\n",hp,maxhp,mp,maxmp,basicatt,bonusatt,basicdef,bonusdef);
    
}

void clear(int area)
{
    int i,j;
    for(i=0;i<22;i++)
        for(j=0;j<31;j++)
            if(quest[area][0][i][j]=='M')
                quest[area][0][i][j]=' ';
}

void battlesetup(area)
{
    int i;
    if(area==0)
    {
        mon[0][0]=4;
        mon[0][1]=4;
        mon[1][0]=3;
        mon[1][1]=7;
        mon[2][0]=4;
        mon[2][1]=10;
        mon[3][0]=3;
        mon[3][1]=13;
        mon[4][0]=6;
        mon[4][1]=15;
        mon[5][0]=9;
        mon[5][1]=13;
        mon[6][0]=12;
        mon[6][1]=15;
        mon[7][0]=14;
        mon[7][1]=13;
        for(i=0;i<8;i++)
            quest[0][0][mon[i][0]][mon[i][1]]='M';
        quest[0][0][12][22]=quest[0][0][14][22]='M';
    }
    else if(area==1)
    {
        mon[0][0]=3;
        mon[0][1]=4;
        mon[1][0]=7;
        mon[1][1]=5;
        mon[2][0]=11;
        mon[2][1]=4;
        mon[3][0]=3;
        mon[3][1]=13;
        mon[4][0]=6;
        mon[4][1]=9;
        mon[5][0]=8;
        mon[5][1]=13;
        mon[6][0]=11;
        mon[6][1]=9;
        for(i=0;i<7;i++)
            quest[1][0][mon[i][0]][mon[i][1]]='M';
        quest[1][0][6][19]=quest[1][0][8][19]=quest[1][0][7][20]='M';
    }
    else if(area==2)
    {
        mon[0][0]=3;
        mon[0][1]=5;
        mon[1][0]=6;
        mon[1][1]=9;
        mon[2][0]=3;
        mon[2][1]=15;
        mon[3][0]=6;
        mon[3][1]=19;
        mon[4][0]=5;
        mon[4][1]=25;
        mon[5][0]=10;
        mon[5][1]=28;
        mon[6][0]=14;
        mon[6][1]=27;
        mon[7][0]=15;
        mon[7][1]=19;
        mon[8][0]=16;
        mon[8][1]=13;
        mon[9][0]=19;
        mon[9][1]=16;
        mon[10][0]=17;
        mon[10][1]=23;
        for(i=0;i<11;i++)
            quest[2][0][mon[i][0]][mon[i][1]]='M';
        quest[2][0][15][3]=quest[2][0][15][4]=quest[2][0][16][2]=quest[2][0][16][5]='M';
    }
    else if(area==3)
    {
        mon[0][0]=2;
        mon[0][1]=6;
        mon[1][0]=5;
        mon[1][1]=8;
        mon[2][0]=6;
        mon[2][1]=12;
        mon[3][0]=2;
        mon[3][1]=16;
        mon[4][0]=5;
        mon[4][1]=17;
        mon[5][0]=1;
        mon[5][1]=21;
        mon[6][0]=3;
        mon[6][1]=26;
        for(i=0;i<7;i++)
            quest[3][0][mon[i][0]][mon[i][1]]='M';
        quest[3][0][15][24]=quest[3][0][15][26]=quest[3][0][15][28]=quest[3][0][16][25]=quest[3][0][16][27]='M';
    }
    else if(area==4)
        quest[4][0][3][8]=quest[4][0][5][5]=quest[4][0][5][11]=quest[4][0][9][5]=quest[4][0][9][11]=quest[4][0][11][8]='M';
}

void animation(int i,int monhp,int monatt)
{
    if(i==0)
    {
        system("cls");
        printf("HP: %d/%d   MP: %d/%d   \nAD: %d(+%d) ARM: %d(+%d)\n______________________________\n",hp,maxhp,mp,maxmp,basicatt,bonusatt,basicdef,bonusdef);
        printf("\n                    HP: %d\n              \\M    AD: %d\n               |\\\n      O        |\n     /|\\      / \\\n      |\n     / \\\n______________________________\n\nBasic <B>   Special <S>   Escape <E>",monhp,monatt); 
        sleep(500);
    }
    else if(i==1)
    {
        system("cls");
        printf("HP: %d/%d   MP: %d/%d   \nAD: %d(+%d) ARM: %d(+%d)\n______________________________\n",hp,maxhp,mp,maxmp,basicatt,bonusatt,basicdef,bonusdef);
        printf("\n                    HP: %d\n               M    AD: %d\n              /|\\\n      O/       |\n     /|       / \\\n      |\n     / \\\n______________________________\n\nBasic <B>   Special <S>   Escape <E>",monhp,monatt); 
        sleep(500);
    }
    system("cls");
    printf("HP: %d/%d   MP: %d/%d   \nAD: %d(+%d) ARM: %d(+%d)\n______________________________\n",hp,maxhp,mp,maxmp,basicatt,bonusatt,basicdef,bonusdef);
    printf("\n                    HP: %d\n               M    AD: %d\n              /|\\\n      O        |\n     /|\\      / \\\n      |\n     / \\\n______________________________\n\nBasic <B>   Special <S>   Escape <E>",monhp,monatt); 
}

int box(int i)
{
    printf("\n");
    int j,num;
    char element[i];
    for(j=0;j<i;j++)
        element[j]=' ';
    element[rand()%i]='C';
    for(j=0;j<(i-1)/2;j++)
    {
        do
        {
            num=rand()%i;
        }while(element[num]!=' ');
        element[num]='N';
        do
        {
            num=rand()%i;
        }while(element[num]!=' ');
        element[num]='M';
    }
    num=-1;
    while(1)
    {
        num=(num+1)%i;
        system("cls");
        for(j=0;j<i;j++)
        {
            if(j==num)
                color(white);
            printf("%c ",element[j]);
            color(black);
        }
        sleep(50);
        if(kbhit())
            if(getch()==' ')
                break;
    }
    sleep(1000);
    if(element[num]=='M')
        return 0;
    else if(element[num]=='C')
        return 2;
    else if(element[num]=='N')
        return 1;
}

void fight(int area,int monhp,int monatt)
{
    int input,i;
    if(area==-1)
    {
        maxhp=500;
        hp=500;
        basicatt=att=10;
        maxmp=100;
        mp=100;
    }
    while(monhp>0&&hp>0)
    {
        mp+=maxmp*0.1;
        if(mp>maxmp)
            mp=maxmp;
        animation(2,monhp,monatt);
        while(input!='b'&&input!='s'&&input!='e')
        {
            input=0;
            input=getch();
            if(input=='b')
            {
                i=box(3);
                if(i!=0)
                {
                    if(att>monhp)
                        monhp=0;
                    else
                        monhp-=att*i;
                }
                animation(1,monhp,monatt);
            }
            else if(input=='s')
            {
                if(mp>=maxmp*0.2)
                {
                    mp-=maxmp*0.2;
                    i=box(9);
                    if(i!=0)
                    {
                        if(2*att>monhp)
                            monhp=0;
                        else
                            monhp-=att*i*2;
                    }
                    animation(1,monhp,monatt);
                }
                else 
                {
                    printf("\n\nNot enough mp!");
                    sleep(500);
                    animation(0,monhp,monatt);
                    input=0;
                }
            }
            else if(input=='e')
            {
                return;
            }
        }
        input=0;
        sleep(500);
        animation(0,monhp,monatt);
        if(monatt>def)
            hp-=monatt-def;
        else 
            hp--;
        if(hp<0)
            hp=0;
    }
    if(hp==0)
    {
        animation(2,monhp,monatt);
        sleep(1000);
        system("cls");
        printf("...");
        sleep(1000);
        return;
    }
    else
    {
        if(area==-1)
        {
            animation(2,monhp,monatt);
            sleep(1000);
            system("cls");
            printf("Boom!");
            sleep(2000);
            return;
        }
        else if(qnum!=-1)
        {
            if(area==0)
                a1num++;
            else if(area==1)
                a2num++;
            else if(area==2)
                a3num++;
            else if(area==3)
                a4num++;
            else if(area==4)
                a5num++;
        }
        system("cls");
        printf("Victory!\nXP+%d   $+%d",area+1,area+1);
        money+=area+1;
        calstat(area+1);
        sleep(2000);
        return;
    }
}   

int battle(int area)
{
    int i,j,k,qi,qj,dir,t=clock();
    battlesetup(area);
    
    FILE *stat;
    stat=fopen("ignoreme/stat.txt","r");
    if(stat!=NULL)
    {
        fscanf(stat,"%d",&xp);
        fscanf(stat,"%d",&maxhp);
        fscanf(stat,"%d",&maxmp);
        fscanf(stat,"%d",&basicatt);
        fscanf(stat,"%d",&basicdef);
        fscanf(stat,"%d",&bonusatt);
        fscanf(stat,"%d",&bonusdef);
    }
    fclose(stat);
    hp=maxhp;
    mp=maxmp;
    att=basicatt+bonusatt;
    def=basicdef+bonusdef;
    
    if(area==0)
    {
        qi=3;
        qj=1;
    }
    else if(area==1)
    {
        qi=7;
        qj=1;
    }
    else if(area==2)
    {
        qi=4;
        qj=1;
    }
    else if(area==3)
        qi=qj=1;
    else
    {
        qi=7;
        qj=8;
    }
    
    showquest(area,qi,qj);
    while(1)
    {
        if(clock()-t>1000)
        {
            t=clock();
            hp+=0.1*maxhp;
            if(hp>maxhp)
                hp=maxhp;
            mp+=0.05*maxmp;
            if(mp>maxmp)
                mp=maxmp;
            move(area,qi,qj);
            showquest(area,qi,qj);
        }
        if(kbhit())
        {
            dir=0;
            dir=get_code();
            if(dir==up)
            {
                if(quest[area][0][qi-1][qj]==' ') 
                    qi--;
                else if(quest[area][0][qi-1][qj]=='O')
                {
                    clear(area);
                    return;
                }
            }
            else if(dir==down)
            {
                if(quest[area][0][qi+1][qj]==' ') 
                    qi++;
                else if(quest[area][0][qi+1][qj]=='O')
                {
                    clear(area);
                    return;
                }
            }
            else if(dir==left)
            {
                if(quest[area][0][qi][qj-1]==' ') 
                    qj--;
                else if(quest[area][0][qi][qj-1]=='O')
                {
                    clear(area);
                    return;
                }
            }
            else if(dir==right)
            {
                if(quest[area][0][qi][qj+1]==' ') 
                    qj++;
                else if(quest[area][0][qi][qj+1]=='O')
                {
                    clear(area);
                    return;
                }
            }
            else if(dir==' ')
            {
                if(quest[area][0][qi-1][qj]=='M'||quest[area][0][qi+1][qj]=='M'||quest[area][0][qi][qj-1]=='M'||quest[area][0][qi][qj+1]=='M')
                {
                    for(i=0;i<5;i++)
                    {
                        sleep(250);
                        system("cls");
                        sleep(250);
                        showquest(area,qi,qj);
                    }
                    if(area==0)
                    {
                        if(qj<18)
                            fight(area,60,4);
                        else 
                            fight(area,100,10);
                    }
                    else if(area==1)
                    {
                        if(qj<16)
                            fight(area,150,15);
                        else 
                            fight(area,250,40);
                    }
                    else if(area==2)
                    {
                        if(!(qi>7&&qj<9))
                            fight(area,300,50);
                        else 
                            fight(area,450,100);
                    }
                    else if(area==3)
                    {
                        if(qi<12)
                            fight(area,500,115);
                        else 
                            fight(area,650,200);
                    }
                    else if(area==4)
                            fight(area,1000,300);
                }
            }
            showquest(area,qi,qj);
        } 
    }
}

int choose(int j)
{
    int i;
    system("cls");
    printf("So here are some tasks\nI need you to do for me...\n¡@¡@¡@¡@¡@¡@¡@v\n¡@¡@¡@¡@¡@¡@¡@¢Ý\n¡@¡@¡@¡@¡@¡@¡þ¡U¢@\n");
    for(i=0;i<30;i++)
        printf("_");
    printf("\n");
    for(i=0;i<5;i++)
    {
        if(i==j)
            color(white);
        printf("%s\n",quests[i]);
        color(black);
    }
}

void showman()
{
    system("cls");
    printf("\n\n\n¡@¡@¡@¡@¡@¡@¡@¢Ý\n¡@¡@¡@¡@¡@¡@¡þ¡U¢@\n______________________________");
    printf("\n");
}

void mission()
{
    int i=0,choice;
    while(1)
    {
        choose(i);
        choice=get_code();
        if(choice==up)
        {
            if(i>0)
                i--;
        }
        else if(choice==down)
        {
            if(i<4)
                i++;
        }
        else if(choice==esc)
        {
            system("cls");
            printf(":(...");
            sleep(1000);
            system("cls");
            showmap();
            return;
        }
        else if(choice==13)
        {
            showman();
            if(i==0)
                printf("Our town used to be well-known for our monster fur-coat...\nBut as time gone by the brave fighters are growing old...\nThey don't have the strength to fight those monsters already...\nSo we need you to go to any area,\ncollect 20 monster fur and come back to me.\nThere will be reward!");
            else if(i==1)
                printf("OMG! We are running out of food!\nYou know we used to have brave fighters to worry about that...\nI don't even know how we are still alive...\nAnyway...\nCould you please bring us some food?\nP.S. Only the meat from the monsters of area 2 is edible.");
            else if(i==2)
                printf("OMG! AGAIN! HA!...\nThe monsters are attacking!\nPlease be a brave fighter and help us counter-strike their queen!\nAnd while you are there in area 3,\ncan you bring me some extra monster spirit too?\nThanks :)");
            else if(i==3)
                printf("You know...\nAfter all those stuff you've done for us...\nI kinda think that you're the next chosen brave fighter...\nYou're brave, you're strong, and that skill...\nIt's almost as if you're a pirate!\nHAHA! Just kidding...\nBut you're not... are you?...\nAnyway, prove your quality as the chosen one!\nGo to area 4 and destroy them!");
            else if(i==4)
                printf("This last task may seem a little bit too hard...\nBut since you're the chosen brave fighter, I guess you'll be fine.\nGo to area 1 through 4, destory all of them.\nThen go to area 5, wreck them and take the treasure!\nBut remember... you have to finish area 5 in no more then 5 minutes!");
            printf("\n\nDo you want to take this mission? Yes <Enter>/No <Esc>\n");
            while(1)
            {
                choice=getch();
                if(choice==13)
                {
                    showman();
                    printf("Are you sure? I mean it's kinda dangerous...\nYou don't really have to do that...\nSure <Enter>/Not sure <Esc>\n");
                    while(1)
                    {
                        choice=getch();
                        if(choice==13)
                        {
                            a1num=a2num=a3num=a4num=0;
                            printf("\nCool! Thank you and good luck!");
                            sleep(2000);
                            qnum=i;
                            system("cls");
                            showmap();
                            return;
                        }
                        else if(choice==esc)
                        {
                            showman();
                            printf(":(...");
                            sleep(1000);
                            break;
                        }
                    }
                    break;
                }
                else if(choice==esc)
                {
                    printf(":(...");
                    sleep(1000);
                    break;
                }
            }
            
        }
    } 
}

void banner(char word[],int time)
{
    int i,j;
    for(j=0;word[j]!='\0';j++);
    for(i=0;i<j;i++)
    {
        printf("%c",word[i]);
        if(word[i]!=' '&&word[i]!='\n')
            sleep(100);
    }
    sleep(time);
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
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN);
            break;
        case blue:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            break;
        case yellow:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_GREEN);
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

void setup()
{
    int i,j,k;
    for(i=0;i<12;i++)
        for(j=0;j<50;j++)
            dialogue[i][j]='\0';
    FILE *word;
    word=fopen("ignoreme/words.txt","r");
    if(word!=NULL)
    {
        for(i=0;i<12;i++)
        {
            fgets(dialogue[i],100,word);
        }
        
        fclose(word);       
    }
    
    for(i=0;i<10;i++)
        for(j=0;j<17;j++)
            for(k=0;k<32;k++)
            {
                map[i][0][j][k]=' ';
                map[i][1][j][k]=black;
            }
    for(i=0;i<5;i++)
        for(j=0;j<22;j++)
            for(k=0;k<31;k++)
            {
                quest[i][0][j][k]=' ';
                quest[i][1][j][k]=black;
            }
            
    for(i=0;i<12;i++)
        map[pos[i][0]][0][pos[i][1]][pos[i][2]]='o';
    map[6][0][1][13]=' ';
            
    //map0 setup
    for(i=0;i<14;i++)
        map[0][0][0][i]='.';
    for(i=0;i<12;i++)
        map[0][0][i][0]=map[0][0][i][13]='.';
    for(i=0;i<5;i++)
        map[0][0][i+12][i+1]=map[0][0][i+12][12-i]='.';
    map[0][0][16][6]=map[0][0][16][7]='.';
    for(i=0;i<17;i++)
        for(j=0;j<14;j++)
            map[0][1][i][j]=yellow;
    for(i=0;i<6;i++)
        for(j=0;j<i;j++)
        {
            map[0][1][i+11][j]=map[0][1][i+11][13-j]=black;
        }
    map[0][0][0][6]=map[0][0][0][7]='_';
    map[0][1][2][2]=map[0][1][1][8]=map[0][1][9][12]=map[0][1][15][6]=cyan;
    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
        {
            map[0][1][i+6][j+6]=black;
            map[0][0][i+6][j+6]='.';
        }
        
    //map1 setup
    for(i=1;i<4;i++)
        for(j=1;j<5;j++)
            map[1][1][i][j]=white;
    for(i=0;i<5;i++)
        map[1][0][i][0]=map[1][0][i][5]='.';
    for(i=0;i<6;i++)
        map[1][0][0][i]=map[1][0][4][i]='.';
    map[1][0][4][4]=map[1][0][4][3]='_';
    map[1][1][1][4]=yellow;
    map[1][0][1][4]='X';
    map[1][1][2][1]=red;
    map[1][1][1][2]=cyan;
    map[1][1][2][2]=purple;
    
    
    //map2 setup
    for(i=0;i<5;i++)
        for(j=0;j<14;j++)
            map[2][1][i][j]=blue;
    for(i=0;i<14;i++)
        map[2][1][5][i]=cyan;
    for(i=0;i<8;i++)
        for(j=0;j<23;j++)
            map[2][1][i+6][j]=white;
    for(i=0;i<12;i++)
    {
        map[2][1][6][i+1]=cyan;
        map[2][1][7][i+1]=map[2][1][8][i+1]=yellow;
        map[2][1][9][i+1]=green;
    }
    for(i=0;i<3;i++)
        for(j=0;j<21;j++)
            map[2][1][i+10][j+1]=green;
    for(i=0;i<3;i++)
        for(j=0;j<9;j++)
            map[2][1][i+6][j+14]=black;
    map[2][1][12][22]=black;
    for(i=0;i<14;i++)
        map[2][0][0][i]='.';
    for(i=0;i<8;i++)
        map[2][0][i+1][0]=map[2][0][i+1][13]='.';
    for(i=0;i<21;i++)
        map[2][0][9][21-i]=map[2][0][13][21-i]='.';
    for(i=0;i<5;i++)
        map[2][0][9+i][0]=map[2][0][9+i][22]='.';
    map[2][0][9][1]='_';
    map[2][0][12][22]=' ';
    
    //map3 setup
    for(i=0;i<20;i++)
    {
        map[3][1][0][i]=map[3][1][2][i]=red;
        map[3][1][1][i]=green;
        map[3][0][0][i]=map[3][0][2][i]='.';
    }
    map[3][1][1][0]=black;
    
    //map4 setup
    for(i=0;i<11;i++)
        for(j=0;j<11;j++)
            map[4][1][i+1][j+1]=white;
    for(i=0;i<13;i++)
    {
        map[4][1][0][i]=map[4][1][12][i]=map[4][1][i][0]=map[4][1][i][12]=purple;
        map[4][0][0][i]=map[4][0][12][i]=map[4][0][i][0]=map[4][0][i][12]='.';
    }
    for(i=0;i<11;i++)
        map[4][1][6][i]=red;
    map[4][0][6][0]=' ';
    map[4][1][6][11]=blue;
    map[4][1][12][9]=white;
    map[4][0][12][9]=' ';
    for(i=0;i<4;i++)
    {
        map[4][1][1][i+2]=yellow;
        map[4][1][11][i+2]=green;
    }
    map[4][1][1][7]=map[4][1][1][8]=map[4][1][1][9]=green;
    
    //map5 setup
    for(i=0;i<17;i++)
        for(j=0;j<26;j++)
        {
            map[5][1][i][j]=red;
            map[5][0][i][j]='.';
        }
    for(i=0;i<14;i++)
        for(j=0;j<6;j++)
        {
            map[5][1][i+3][j+20]=black;
            map[5][0][i+3][j+20]=' ';
        }
    for(i=0;i<8;i+=2)
    {
        for(j=9;j>i;j--)
        {
            map[5][1][i+3][j]=map[5][1][i+3][17-j]=map[5][1][15-i][j]=map[5][1][15-i][17-j]=black;
            map[5][0][i+3][j]=map[5][0][i+3][17-j]=map[5][0][15-i][j]=map[5][0][15-i][17-j]=' ';
        }
        for(j=5;j>i;j--)
        {
            map[5][1][j+3][i+1]=map[5][1][15-j][i+1]=map[5][1][j+3][16-i]=map[5][1][14-j][16-i]=black;
            map[5][0][j+3][i+1]=map[5][0][15-j][i+1]=map[5][0][j+3][16-i]=map[5][0][14-j][16-i]=' ';
        }
    }
    for(i=1;i<=5;i+=2)
    {
        map[5][1][9][i]=black;
        map[5][0][9][i]=' ';
    }
    for(i=0;i<8;i+=2)
    {
        map[5][1][i+9][i+11]=black;
        map[5][0][i+9][i+11]=' ';
    }
    map[5][1][0][1]=black;
    map[5][0][0][1]=' ';
    for(i=0;i<24;i++)
    {
        map[5][1][1][i+1]=black;
        map[5][0][1][i+1]=' ';
    }
    for(i=0;i<14;i++)
    {
        map[5][1][i+2][j+13]=black;
        map[5][0][i+2][j+13]=' ';
    }
    map[5][1][1][25]=blue;
    map[5][0][1][25]=' ';
    map[5][1][9][7]=green;
    
    //map6 setup
    char maze[289]={"0000000000000000011110111111101110000101010101000100111110101010111001000001010101000011011110111011100010100000000001001101011111111110010010100010000100111111011111101001000100000001000010111111111011100101000001010001001111011110111010010000000000010100111111111111101000000000000000010"};
    for(i=0;i<17;i++)
        for(j=0;j<17;j++)
        {
            if(maze[17*i+j]=='1')
                map[6][1][i][j]=white;
            else 
                map[6][0][i][j]='.';
        }
    
    //map7 setup
    for(i=0;i<14;i++)
        for(j=0;j<23;j++)
        {
            map[7][0][i][j]=map[2][0][i][j];
            map[7][1][i][j]=map[2][1][i][j];
        }
    map[7][0][9][1]=' ';
    
    //map8 setup
    for(i=0;i<13;i++)
        for(j=0;j<31;j++)
            map[8][1][i][j]=yellow;
    for(i=0;i<31;i++)
        map[8][0][0][i]=map[8][0][12][i]='.';
    for(i=0;i<10;i++)
        map[8][0][i+2][0]=map[8][0][i+2][30]='.';
    map[8][1][1][0]=black;
    map[8][1][1][30]=green;
    char village[200]={"    .   .    .          .    ... .  . .  .  .    .        .... ....  .    .                   ......                                                   .                       ..  ...                  "};
    for(i=0;i<8;i++)
        for(j=0;j<25;j++)
            map[8][0][i+1][j+1]=village[25*i+j];
    map[8][0][9][7]='.';
    for(i=0;i<23;i++)
        map[8][0][10][i+7]='.';
    for(i=0;i<22;i++)
        map[8][1][10][i+8]=green;
    map[8][0][11][7]='|';
    map[8][1][10][1]=map[8][1][10][2]=map[8][1][10][3]=map[8][1][11][3]=white;
    map[8][0][10][1]=map[8][0][10][2]=map[8][0][10][3]=map[8][0][11][3]='.';
    map[8][1][2][10]=map[8][1][2][15]=map[8][1][3][24]=map[8][1][11][2]=cyan;
    map[8][0][2][10]=map[8][0][2][15]=map[8][0][11][2]='o';
    map[8][0][3][24]='M';
    
    //map9 setup
    for(i=0;i<6;i++)
        for(j=4;j<10;j++)
        {
            map[9][0][2*i][j+2]='.';
            map[9][1][2*i][j+2]=red;
        }
    for(i=0;i<11;i++)
        if(i!=5)
        {
            map[9][0][i][4]='.';
            map[9][1][i][4]=red;
        }
    map[9][1][4][0]=map[9][1][4][1]=map[9][1][6][0]=map[9][1][6][1]=map[9][1][0][5]=map[9][1][10][5]=map[9][1][4][2]=map[9][1][4][3]=map[9][1][6][2]=map[9][1][6][3]=red;
    map[9][0][4][0]=map[9][0][4][1]=map[9][0][6][0]=map[9][0][6][1]=map[9][0][0][5]=map[9][0][10][5]=map[9][0][4][2]=map[9][0][4][3]=map[9][0][6][2]=map[9][0][6][3]='.';
    for(i=1;i<=5;i++)
        map[9][0][2*i-1][6]=i+48;
        
    //quest0 etup
    for(i=0;i<18;i++)
        for(j=0;j<26;j++)
            quest[0][0][i][j]='.';
    for(i=0;i<9;i++)
        for(j=0;j<7;j++)
            quest[0][0][i][j+19]=' ';
    for(i=0;i<10;i++)
        for(j=0;j<10;j++)
            quest[0][0][i+8][j]=' ';
    for(i=0;i<6;i++)
        for(j=0;j<17;j++)
        {
            quest[0][0][i+1][j+1]=' ';
            quest[0][1][i+1][j+1]=green;
        }
    for(i=0;i<10;i++)
        for(j=0;j<7;j++)
        {
            quest[0][0][i+7][j+11]=' ';
            quest[0][1][i+7][j+11]=green;
        }
    for(i=0;i<7;i++)
        for(j=0;j<6;j++)
        {
            quest[0][0][i+10][j+19]=' ';
            quest[0][1][i+10][j+19]=green;
        }
    quest[0][0][13][18]=' ';
    quest[0][1][13][18]=green;
    quest[0][1][3][1]=white;
    quest[0][0][3][1]='O';
    
    //quest1 setup
    for(i=0;i<15;i++)
        for(j=0;j<17;j++)
            quest[1][0][i][j]='.';
    for(i=0;i<7;i++)
        for(j=0;j<7;j++)
            quest[1][0][i+4][j+16]='.';
    for(i=0;i<13;i++)
        for(j=0;j<6;j++)
        {
            quest[1][0][i+1][j+1]=' ';
            quest[1][1][i+1][j+1]=cyan;
        }
    for(i=0;i<13;i++)
        for(j=0;j<9;j++)
        {
            quest[1][0][i+1][j+7]=' ';
            quest[1][1][i+1][j+7]=blue;
        }
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
        {
            quest[1][0][i+5][j+17]=' ';
            quest[1][1][i+5][j+17]=blue;
        }
    quest[1][0][7][16]=' ';
    quest[1][1][7][16]=blue;
    quest[1][1][7][1]=white;
    quest[1][0][7][1]='O';
    
    //quest2 setup
    for(i=0;i<29;i++)
        quest[2][0][0][i]=quest[2][0][21][i]='.';
    for(i=0;i<25;i++)
        quest[2][0][8][i]=quest[2][0][13][i]='.';
    for(i=0;i<22;i++)
        quest[2][0][i][29]='.';
    for(i=0;i<7;i++)
        quest[2][0][i+1][0]=quest[2][0][i+14][0]=quest[2][0][i+7][25]='.';
    quest[2][0][7][25]=' ';
    for(i=0;i<20;i++)
        for(j=0;j<28;j++)
            quest[2][1][i+1][j+1]=white;
    for(i=0;i<6;i++)
        for(j=0;j<25;j++)
            quest[2][1][i+8][j+1]=black;
    for(i=0;i<8;i++)
    {
        quest[2][1][18][i+1]=black;
        quest[2][0][18][i+1]='.';
    }
    for(i=0;i<4;i++)
    {
        quest[2][1][i+14][8]=black;
        quest[2][0][i+14][8]='.';
    }
    quest[2][1][18][3]=quest[2][1][18][4]=white;
    quest[2][0][18][3]=quest[2][0][18][4]=' ';
    quest[2][1][4][1]=white;
    quest[2][0][4][1]='O';
    
    //quest3 setup
    char quest4[589]={"1111111111100111111111111111110100000000010010000000000000001011111000001001000001111100000100000100000100100000100010000010000010000010010000010001000001000001000001111000001000101010100000100000000000000100010101010000011111111111111110001010101000000000000000000000000101010100000000000000000000000010101010000000000000000000000001010101000000000000000000000001111011110000000000000000000000100000001000000000000000000000010000000100000000000000000000001000000010000000000000000000000100000001000000000000000000000010000000100000000000000000000001000000010000000000000000000000111111111"};
    for(i=0;i<19;i++)
        for(j=0;j<31;j++)
            if(quest4[31*i+j]=='1')
            {
                quest[3][1][i][j]=red;
                quest[3][0][i][j]='.';
            }
    quest[3][1][1][1]=white;
    quest[3][0][1][1]='O';
    
    //quest4 setup
    char circle[255]={"000000111110000000000112222211000000012222222221000001222222222221000122222222222221001222222222222210122222222222222211222222222222222112222222222222221012222222222222100122222222222221000122222222222100000122222222210000000112222211000000000011111000000"};
    for(i=0;i<15;i++)
        for(j=0;j<17;j++)
            if(circle[17*i+j]=='1')
            {
                quest[4][1][i][j]=red;
                quest[4][0][i][j]='.';
            }
            else if(circle[17*i+j]=='2')
                quest[4][1][i][j]=yellow;
    quest[4][1][7][8]=white;
    quest[4][0][7][8]='O';
          
}

int game(int stage)
{
    int i,j,k,dir;
    
    if(stage==1)
    {   
        while(!(talk[0]*talk[1]*talk[2]*talk[3]))
        {
            system("cls");
            showmap();
            dir=0;
            dir=get_code();
            if(dir==left)
            { 
                if(map[pmap][0][pi][pj-1]==' ')
                    pj--;
            }
            else if(dir==right)
            {
                if(map[pmap][0][pi][pj+1]==' ')
                    pj++;
            }
            else if(dir==up)
            {
                if(map[pmap][0][pi-1][pj]==' ')
                    pi--;
            }
            else if(dir==down)
            {
                if(map[pmap][0][pi+1][pj]==' ')
                    pi++;
            }
            else if(dir==' ')
            {
                for(i=0;i<4;i++)
                    if((pi==pos[i][1]&&(pj-pos[i][2])*(pj-pos[i][2])==1)||(pj==pos[i][2]&&(pi-pos[i][1])*(pi-pos[i][1])==1))
                        break;
                if(i!=4)
                {
                    system("cls");
                    showmap();
                    printf("\n");
                    for(j=0;dialogue[i][j]!='\0';j++)
                        printf("%c",dialogue[i][j]);
                    talk[i]=1;
                    while(!kbhit());
                }
            }
            else if(dir==esc)
            {
                system("cls");
                printf("Do you want to save? (Y/N)");
                if(getch()=='y')
                    save(1);
                system("cls");
                printf("Bye :(");
                sleep(1000);
                return 0;
            }
        }
    return 1;
    }//end of stage 1
    else if(stage==2)
    {
        map[0][0][0][6]=map[0][0][0][7]=' ';
        while(!(pi==0&&(pj==6||pj==7)))
        {
            system("cls");
            showmap();
            dir=0;
            dir=get_code();
            if(dir==left)
            { 
                if(map[pmap][0][pi][pj-1]==' ')
                    pj--;
            }
            else if(dir==right)
            {
                if(map[pmap][0][pi][pj+1]==' ')
                    pj++;
            }
            else if(dir==up)
            {
                if(map[pmap][0][pi-1][pj]==' ')
                    pi--;
            }
            else if(dir==down)
            {
                if(map[pmap][0][pi+1][pj]==' ')
                    pi++;
            }
            else if(dir==' ')
            {
                for(i=0;i<4;i++)
                    if((pi==pos[i][1]&&(pj-pos[i][2])*(pj-pos[i][2])==1)||(pj==pos[i][2]&&(pi-pos[i][1])*(pi-pos[i][1])==1))
                        break;
                if(i!=4)
                {
                    system("cls");
                    showmap();
                    printf("\n");
                    printf("...");
                    while(!kbhit());
                }
            }
            else if(dir==esc)
            {
                system("cls");
                printf("Do you want to save? (Y/N)");
                if(getch()=='y')
                    save(1);
                system("cls");
                printf("Bye :(");
                sleep(1000);
                return 0;
            }
        }
    return 1;
    }//end of stage 2
    else if(stage==3)
    {
        while(!((pi==4&&(pj=3||pj==4))&&talk[5]))
        {
            if(talk[5])
                map[1][0][4][3]=map[1][0][4][4]=' ';
            system("cls");
            showmap();
            dir=0;
            dir=get_code();
            if(dir==left)
            { 
                if(map[pmap][0][pi][pj-1]==' ')
                    pj--;
            }
            else if(dir==right)
            {
                if(map[pmap][0][pi][pj+1]==' ')
                    pj++;
            }
            else if(dir==up)
            {
                if(map[pmap][0][pi-1][pj]==' ')
                    pi--;
            }
            else if(dir==down)
            {
                if(map[pmap][0][pi+1][pj]==' ')
                    pi++;
            }
            else if(dir==' ')
            {
               for(i=4;i<8;i++)
                    if((pi==pos[i][1]&&(pj-pos[i][2])*(pj-pos[i][2])==1)||(pj==pos[i][2]&&(pi-pos[i][1])*(pi-pos[i][1])==1))
                        break;
                if(i!=8)
                {
                    system("cls");
                    showmap();
                    printf("\n");
                    for(j=0;dialogue[i][j]!='\0';j++)
                        printf("%c",dialogue[i][j]);
                    talk[i]=1;
                    while(!kbhit());
                }
            }
            else if(dir==esc)
            {
                system("cls");
                printf("Do you want to save? (Y/N)");
                if(getch()=='y')
                    save(1);
                system("cls");
                printf("Bye :(");
                sleep(1000);
                return 0;
            }
        }
    return 1;
    }// end of stage 3
    else if(stage==4)
    {   
        map[2][0][9][1]=' '; //to be removed
        while(!(talk[8]&&pmap==6&&pi==16&&pj==15))
        {
            system("cls");
            showmap();
            dir=get_code();
            if(dir==left)
            {
                if(pmap==3&&pi==1&&pj==0)
                {
                    pmap=2;
                    pi=12;
                    pj=22;
                }
                else if(pmap==4&&pi==6&&pj==0)
                {
                    pmap=3;
                    pi=1;
                    pj=19;
                }
                else if(pmap==5&&pi==9&&pj==7)
                {
                    pmap=6;
                    pi=1;
                    pj=0;
                }
                else if(pmap==6&&pi==1&&pj==0)
                {
                    pmap=5;
                    pi=9;
                    pj=7;
                }
                else    if(map[pmap][0][pi][pj-1]==' ')
                    pj--;
            }
            else if(dir==right)
            {
                
                if(pmap==5&&pi==1&&pj==25)
                {
                    system("cls");
                    printf("You drowned in water...\n");
                    pmap=2;
                    pi=rand()%5+1;
                    pj=rand()%12+1;
                    sleep(3000);
                }
                else if(pmap==2&&pi==12&&pj==22)
                {
                    pmap=3;
                    pi=1;
                    pj=0;
                }
                else if(pmap==3&&pi==1&&pj==19)
                {
                    pmap=4;
                    pi=6;
                    pj=0;
                }
                else if(map[pmap][0][pi][pj+1]==' ')
                    pj++;
            }
            else if(dir==up)
            {
                if(pmap==5&&pi==0&&pj==1)
                {
                    pmap=4;
                    pi=12;
                    pj=9;
                }
                else if(map[pmap][0][pi-1][pj]==' ')
                    pi--;
            }
            else if(dir==down)
            {
                if(pmap==4&&pi==12&&pj==9)
                {
                    pmap=5;
                    pi=0;
                    pj=1;
                }
                else if(pmap==6&&pi==16&&pj==15)
                {
                    map[6][1][1][13]=purple;
                    map[6][0][1][13]='@';
                    if(talk[8])
                    {
                        showmap();
                        sleep(1000);
                        return 1;
                    }
                    else
                    {
                        pmap=2;
                        pi=7;
                        pj=6;
                    }
                }
                else if(map[pmap][0][pi+1][pj]==' ')
                    pi++;
            }
            else if(dir==' ')
            {
                if(pmap==6&&pi==1&&pj==14)
                {
                    system("cls");
                    showmap();
                    printf("\n");
                    for(j=0;dialogue[8][j]!='\0';j++)
                        printf("%c",dialogue[8][j]);
                    talk[8]=1;
                    for(j=0;dialogue[9][j]!='\0';j++)
                        printf("%c",dialogue[9][j]);
                    talk[9]=1;
                    while(!kbhit());
                }
            }
            else if(dir==esc)
            {
                system("cls");
                printf("Do you want to save? (Y/N)");
                if(getch()=='y')
                    save(1);
                system("cls");
                printf("Bye :(");
                sleep(1000);
                return 0;
            }
        }
    }//end of stage 4
    else if(stage==5)
    {
        while(1)
        {
            system("cls");
            showmap();
            dir=get_code();
            if(dir==left)
            {
                if(pmap==8&&pi==1&&pj==0)
                {
                    pmap=7;
                    pi=12;
                    pj=22;
                }
                else if(pmap==9)
                {
                    if(pi==5&&pj==0)
                    {
                        pmap=8;
                        pi=1;
                        pj=30;
                    }
                    else if(map[pmap][0][pi][pj-1]!='.')
                        pj--;
                }
                else if(map[pmap][0][pi][pj-1]==' ')
                    pj--;
            }
            else if(dir==right)
            {
                if(pmap==8&&pi==1&&pj==30)
                {
                    pmap=9;
                    pi=5;
                    pj=0;
                }
                else if(pmap==7&&pi==12&&pj==22)
                {
                    pmap=8;
                    pi=1;
                    pj=0;
                }
                else if(pmap==9)
                {
                    if(pj==11)
                        battle((pi-1)/2);
                    else if(map[pmap][0][pi][pj+1]!='.')
                        pj++;
                }
                else if(map[pmap][0][pi][pj+1]==' ')
                    pj++;
            }
            else if(dir==up)
            {
                if(map[pmap][0][pi-1][pj]==' ')
                    pi--;
            }
            else if(dir==down)
            {
                if(map[pmap][0][pi+1][pj]==' ')
                    pi++;
            }
            else if(dir==' ')
            {
                if(pmap==8&&((pi==1&&pj==10)||(pi==2&&pj==11)))
                    printf("Hey! Who says you can come in!");
                else if(pmap==8&&((pi==1&&pj==15)||(pi==2&&pj==16)))
                    printf("Hey! Go to the house on your left!");
                char haha;
                if(pmap==8&&((pi==3&&pj==23)||(pi==2&&pj==24))) 
                {
                    system("cls");
                    showmap();
                    if(qnum==-1)
                    {
                        printf("Hey! I'm the mayer of this tiny little town.\nCan you help me for the tasks?\nThere will be rewards!\nYes <Enter>/No <Esc>");
                        while(1)
                        {
                            haha=getch();
                            if(haha==13)
                            {
                                mission();
                                done=0;
                                break;
                            }
                            else if(haha==esc)
                            {
                                system("cls");
                                showmap();
                                printf(":(...");
                                break;
                            }
                        }
                    }
                    else
                    {
                        if(done==0)
                        {
                            printf("You've already taken a quest! Do you want to give up the quest?\nYes <Enter>/No <Esc>");
                            while(1)
                            {
                                haha=getch();
                                if(haha==13)
                                {
                                    system("cls");
                                    showmap();
                                    printf(":(...");
                                    qnum=-1;
                                    a1num=a2num=a3num=a4num=a5num=done=0;
                                    break;
                                }
                                else if(haha==esc)
                                {
                                    system("cls");
                                    showmap();
                                    printf("Cool! Keep going bro!");
                                    break;
                                }
                            }
                        
                        }
                        else 
                        {
                            system("cls");
                            showmap();
                            printf("Nice job! Here's your reward! You deserve it!\nXP+%d   $+%d",qnum*10+10,qnum*50+20);
                            xp+=qnum*10+10;
                            money+=qnum*50+20;
                            savestat();
                            qnum=-1;
                            a1num=a2num=a3num=a4num=a5num=done=0;
                            while(!kbhit());
                        }
                    }
                }   
                else if(pmap==8&&pi>8&&pj<5)
                {
                    printf("Hi, I'm the shop owner, you can now check out our items!");
                    FILE *shop;
                    shop=fopen("ignoreme/canbuy.txt","w+");
                    fprintf(shop,"1");
                    fclose(shop);
                    while(!kbhit());
                }
                FILE *shop;
                shop=fopen("ignoreme/canbuy.txt","w+");
                rewind(shop);
                shop=fopen("ignoreme/canbuy.txt","w+");
                fprintf(shop,"0");
                fclose(shop);
                while(!kbhit());
            }
            else if(dir==esc)
            {
                system("cls");
                printf("Do you want to save? (Y/N)");
                if(getch()=='y')
                    save(1);
                system("cls");
                printf("Bye :(");
                sleep(1000);
                return 0;
            }
        }
    }//end of stage 5
}

void story(int stage)
{
    int i;
    if(stage==1)
    {
        show("...",2000);
        banner("27/02/2014",2000);
        printf("\n\n");
        banner("Th' sea be calm, th' air be still...\n",1000);
        banner("We've be stavin' fer six nights.\n",1000);
        banner("Th' cap'n 'n th' seniors have locked themselves\n",0);
        banner("in th' cabin discussin' their wee plans...\n\n",1000);
        banner("Me hungry, ",500);
        banner("me wan food...\n",1000);
        banner("I should go check out my mateys...",2000);
        system("cls");
    }
    else if(stage==2)
    {
        sleep(1000);
        system("cls");
        sleep(1000);
        banner("Bang!\n",500);
        banner("ARHHHHHHHHHHHH!!!",2000);
        system("cls");
        banner("Holy crap, what was that!\n",500);
        banner("The sound came from the captain's room!\n",500);
        banner("I should probably go and see what happened...",1000);
        system("cls");
    }
    else if(stage==3)
    { 
        pmap=1;
        pi=3;
        pj=4; 
        system("cls");
        sleep(1000);
        showmap();
        sleep(1000);
        show("\nCaptain! What are you doing?!",2000);
        say("Get out! You should not be here!");
        say("No! I will fight you to protect my mateys!");
        say("Well then, let the battle begin!");
        sleep(1000);
        system("cls");
        fight(-1,100,5);
        system("cls");
        say("Arhhh...How did you do that...");
        say("Because I'm batman...");
        say("Nah not really, I'm just strong bro.");
        say("...");
        say("Oh look, a key dropped out from your pocket.");
        say("Is it for the chest over there?");
        say("...");
        system("cls");
    }
    else if(stage==4)
    {
        pmap=0;
        pi=1;
        pj=6;
        map[0][0][0][6]=map[0][0][0][7]='_';
        for(i=0;i<10;i++)
        {
            system("cls");
            printf("\n");
            showmap();
            sleep(250);
            system("cls");
            showmap();
            sleep(250);
        }
        sleep(1750);
        say("Wh...What was that!");
        say("Watch out! Our ship is hit by an iceberg!");
        say("OMG! Rose! Where are you?!");
        say("Wait... I'm not Jack, this isn't titanic...");
        say("What was I thinking LOL");
        say("Anyway... ARHHH!!!");
        system("cls");
        sleep(5000);
        pmap=2;
        pi=7;
        pj=6;
        say("...");
        system("cls");
    }
    else if(stage==5)
    {
        pmap=7;
        pi=7;
        pj=6;
        sleep(1000);
        system("cls");
        sleep(3000);
        show("...",2000);
        say("...");
        say("Wh... where am I?...");
        say("Why does this place look so familiar?...");
        say("Was that a dream?...");
        say("Am I still dreaming?...");
        say("Wish I had a spintop...");
        say("Okay I gotta stop acting like Leonardo lolol...");
        say("Anyway...");
        system("cls");
    }
}

int main()
{
    srand(time(NULL));
    int i,j,skip;
    setup();
    FILE * pdata;
    pdata=fopen("ignoreme/position.txt","r+");
    if(pdata!=NULL)
    {
        fscanf(pdata,"%d",&pmap);
        fscanf(pdata,"%d",&pi);
        fscanf(pdata,"%d",&pj);
        fscanf(pdata,"%d",&stage);
        fscanf(pdata,"%d",&skip);
    }
    fclose(pdata);
    FILE * monayy;
    monayy=fopen("ignoreme/money.txt","r+");
    fscanf(monayy,"%d",&money);
    fclose(monayy);
    while(1)
    {
        if(!skip)
            story(stage);
        else
        {
            skip=0;
            save(1);
        }
        if(game(stage)==0)
            break;
        stage++;
        save(0);
    }
}
