#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int ch,posk=0,posi=7,posj=4,i,j,k,level,key[6][3],allget=0,ki,kj,kk,mon[6][6][2],mi,mj,blood=0,movex,movey,randnum,diff;
    char map[6][9][9];

    printf("Please select a level.\n(Easy) 1 - 5 (Hard)\n");
    diff=getch()-48;
    
    
    while(diff<1||diff>5)
    {
        printf("Invalid input.");
        sleep(500);
        system("cls");
        printf("Please select a level.\n(Easy) 1 - 5 (Hard)\n");
        diff=getch()-48;
    }
    
    blood=6-diff;
    //blood=99999;                                     //test infinite blood
   
    for(level=1;level<=6;level++)
    {
        map[posk][posi][posj]='P';
        
        for(k=0;k<6;k++)                           //map initialize
        for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            map[k][i][j]=' ';
        
        for(k=0;k<6;k++)
            map[k][4][4]=k+49;
               
        for(k=0;k<6;k++)                         //key position initialize
            key[k][0]=6;
        
        for(i=0;i<6;i++)                             
        {
            do
            {
                kk=rand()%6;
            }while(key[kk][0]!=6);
            key[kk][0]=i;
        }
        for(i=0;i<6;i++)                             
        {
            do
            {
                ki=rand()%7+1;
                kj=rand()%7+1;
            }while((ki==4&&kj==4)||(key[kk][0]==0&&ki==7&&kj==4));
            key[i][1]=ki;
            key[i][2]=kj;
        }
         
        for(k=0;k<level;k++)
            map[key[k][0]][key[k][1]][key[k][2]]='K';
        
        for(k=0;k<6;k++)                            //monster initialize
        for(i=0;i<6;i++)
            mon[k][i][0]=mon[k][i][1]=10;
        
        for(k=0;k<6;k++)
        for(i=0;i<6;i++)
        {
            do
            {
                mi=rand()%7+1;
                mj=rand()%7+1;
            }while(map[k][mi][mj]!=' '||(mi==7&&mj==4));
            mon[k][i][0]=mi;
            mon[k][i][1]=mj;
        }
        
        for(k=0;k<6;k++)
        for(i=0;i<level;i++)
        map[k][mon[k][i][0]][mon[k][i][1]]='M';
        
    
        while(allget==0)
        {                          //level starts
            system("cls"); 
            
            if(blood==0)
            {
                system("cls");
                printf("Too bad... You died... Try again next time~");
                sleep(2000);
                return;
            }



            for(k=0;k<6;k++)
            {
                for(i=0;i<9;i++)
                    map[k][i][0]=map[k][i][8]='X';
                for(j=0;j<9;j++)
                    map[k][0][j]=map[k][8][j]='X';
            }
    
    
            map[posk][posi][posj]='P';
            printf("Difficulty: Lv %d\n",diff);
            printf("Level: %d\nYour health: %d\n\n",level,blood);
            

    
            for(i=0;i<9;i++)
            {
                for(j=0;j<9;j++)    
                    printf("%2c",map[posk][i][j]);
                printf("\n");
            }
            printf("\n");
            
         //   for(i=0;i<6;i++)                                                //show key coordinates
         //       printf("%d %d %d | %d %d\n",key[i][0],key[i][1],key[i][2],mon[posk][i][0],mon[posk][i][1]);
            
            
    
            for(k=0;k<level;k++)
            {
                if(key[k][0]!=7)
                    printf("There is a key in map %d\n",key[k][0]+1);
            }
            
            map[posk][posi][posj]=' ';
           
            
            for(k=0;k<6;k++)
            for(i=0;i<level;i++)
            map[k][mon[k][i][0]][mon[k][i][1]]=' ';
                                   
            for(k=0;k<6;k++)                            //monsters move
            for(i=0;i<level;i++)
            {
                do
                {
                    movex=mon[k][i][0];
                    movey=mon[k][i][1];
                    if((map[k][movex+1][movey]!=' ')&&(map[k][movex-1][movey]!=' ')&&(map[k][movex][movey+1]!=' ')&&(map[k][movex][movey-1]!=' '))
                    break;
                    randnum=rand()%4;
                    
                    //printf("%d  ",randnum);
                    
                    if(randnum==0)
                        movex++;
                    else if(randnum==1)
                        movex--;
                    else if(randnum==2)
                        movey++;
                    else if(randnum==3)
                        movey--;
                        
                /*    printf("%d  ",i);
                    printf("%d %d ",movex,movey);
                    if(map[k][movex][movey]=='X')
                        printf("case1 ");
                    if(map[k][movex][movey]=='K')
                        printf("case2 ");
                    if((movex==4&&movey==4))
                    printf("case3 ");
                        if(map[k][mon[k][i][movex]][mon[k][i][movey]]=='M')
                    printf("case4 ");
                    printf("\n");
                    sleep(1);         */                                                        //check cases
                    
                }while(map[k][movex][movey]=='X'||map[k][movex][movey]=='K'||(movex==4&&movey==4)||map[k][movex][movey]=='M');
                mon[k][i][0]=movex;
                mon[k][i][1]=movey;
                map[k][mon[k][i][0]][mon[k][i][1]]='M';
            }
    

            if((ch=get_code())!= esc)                  //use arrow keys
            {
                switch(ch) 
                {
                case up:
                    if(posi==1)
                    {
                        if(posk==0)
                        {
                            posk=4;
                            posi=7;
                        }
                        else if(posk==1)
                        {
                            posk=4;
                            posi=8-posj;
                            posj=7;
                        }
                        else if(posk==2)
                        {
                            posk=4;
                            posj=8-posj;
                        }
                        else if(posk==3)
                        {
                            posk=4;
                            posi=posj;
                            posj=1;
                        }
                        else if(posk==4)
                        {
                            posk=2;
                            posj=8-posj;
                            posi=1;
                        }
                        else if(posk==5)
                        {
                            posk=0;
                            posi=7;
                        }
                   }
                   else posi--;
                   break;
                    
                 case down:
                    if (posi==7)
                    {
                        if(posk==0)
                        {
                            posk=5;
                            posi=1;
                        }
                        else if(posk==1)
                        {
                            posk=5;
                            posi=posj;
                            posj=7;
                        }
                        else if(posk==2)
                        {
                            posk=5;
                            posj=8-posj;
                        }
                        else if(posk==3)
                        {
                            posk=5;
                            posi=8-posj;
                            posj=1;
                        }
                        else if(posk==4)
                        {
                            posk=0;
                            posi=1;
                        }
                        else if(posk==5)
                        {
                            posk=2;
                            posj=8-posj;
                            posi=7;
                        }
                    }       
                    else posi++;
                    break;
                 
                 case left:
                    if(posj==1)
                    {
                        if(posk==0)
                        {
                            posk=3;
                            posj=7;
                        }
                        else if(posk>0&&posk<4)
                        {
                            posk--;
                            posj=7;
                        }
                        else if(posk==4)
                        {
                            posk=3;
                            posj=posi;
                            posi=1;
                        }
                        else if(posk==5)
                        {
                            posk=3;
                            posj=8-posi;
                            posi=7;
                        }
                    }    
                    else posj--;
                    break;
                 
                case right:
                    if(posj==7)
                    {
                        if(posk<3)
                        {
                            posk++;
                            posj=1;
                        }
                        else if(posk==3)
                        {
                            posk=0;
                            posj=1;
                        }
                        else if(posk==4)
                        {
                            posk=1;
                            posj=8-posi;
                            posi=1;
                        }
                        else if(posk==5)
                        {
                            posk=1;
                            posj=posi;
                            posi=7;
                        }
                    }
                    else posj++;
                    break;
                }                                    //end of arrow
            }    
            else
            {
                system("cls");
                printf("Game ended.");
                sleep(1000);
                return;
            } 

            for(k=0;k<6;k++)
            map[k][4][4]=k+49;
            
            for(k=0;k<6;k++)
            for(i=0;i<level;i++)
            if(posk==k&&posi==mon[k][i][0]&&posj==mon[k][i][1])
            blood--;
            
            allget=1;
            for(k=0;k<level;k++)
            {
                if(posk==key[k][0]&&posi==key[k][1]&&posj==key[k][2])
                key[k][0]=7;
                if(key[k][0]!=7)
                allget=0;
            }
        }
        
         allget=0;                                   //reset key
         posk=0;                                     //reset player position
         posi=7;
         posj=4;
         if(level<6)
         {
            system("cls");
            printf("Level passed.");
            sleep(1000);
        }
    }
    system("cls");   
    printf("Congratulations! You have passed all 6 levels and completed the mission!");
    sleep(500);
}

void help()
{
    printf("Help\n\nThis is just an ordinary game where you have to find all the keys to complete \nthe level...\n\nBut IN 3D!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\nYou are the player(P), find all the keys(K) to complete each level.\nAs you walk across the boundaries, you will be directed to the other side(n) of\nthe cube. You may want to avoid touching monsters(M) as well.\n\n");
    printf("X X X X X X X X X\nX               X\nX           M   X\nX               X\nX       n       X\nX   K           X\nX               X\nX       P       X\nX X X X X X X X X\n\nP.S. Imagination highly required.\nOr you can simply make yourself a 3D paper cube mapped 1-6 on it.\n");
    printf("\nx x x\nx 5 x\nx x x x x x x x x\nx 1 x 2 x 3 x 4 x\nx x x x x x x x x\nx 6 x\nx x x\n\n");
    printf("P.P.S. There's a message hidden somewhere in this game~\nFind it to claim your reward~\n\n");
    system("pause");
}

int main()
{
    srand(time(NULL));
    char input;
    while(1)
    {
        system("cls");
        printf("Welcome to 3D MAP.\n\nStart(S)     Help(H)     Exit(E)");
        input=getch();
        system("cls");
        if(input=='S'||input=='s')
            game();
        else if(input=='H'||input=='h')
            help();
        else if(input=='E'||input=='e')
        {
            printf("Bye~");
            sleep(1000);
            break;
        }
        else if(input=='D'||input=='d')
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nYay you found me, here's the reward: 659891 :)");
        }
        else
        {
            printf("Invalid input.");
            sleep(1000);
        }
    }
        
    return 0;
}
