#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const totalmon=10;

void show(char word[],int time)
{
    printf("%s",word);
    sleep(time);
    system("cls");
}

void map()
{  
}

void teams()
{
    FILE *monster,*team;
    monster=fopen("monsters.txt","a+");
    team=fopen("teams.txt","a+");
    int i,j,k,index[3],st;
    char name1[12],name2[12],name3[12],desc1[160],desc2[160],desc3[160],buff[160],input;
    while(1)
    {
        st=0;
        for(i=0;i<12;i++)
            name1[i]=name2[i]=name3[i]=0;
        for(i=0;i<160;i++)
            desc1[i]=desc2[i]=desc3[i]=0;
        
        for(i=0;i<3;i++)
            fscanf(team,"%d",&index[i]);
        for(j=0;j<index[0]*4-1;j++)
            fgets(buff,160,monster);
        fgets(desc1,160,monster);
        buff[strlen(buff)-1]=0;
        desc1[strlen(desc1)-1]=0;
        for(i=0;i<13;i++)
            name1[i]=buff[i];
        rewind(monster);
        for(j=0;j<index[1]*4-1;j++)
            fgets(buff,160,monster);
        fgets(desc2,160,monster);
        buff[strlen(buff)-1]=0;
        desc2[strlen(desc2)-1]=0;
        for(i=0;i<13;i++)
            name2[i]=buff[i];
        rewind(monster);
        for(j=0;j<index[2]*4-1;j++)
            fgets(buff,160,monster);
        fgets(desc3,160,monster);
        buff[strlen(buff)-1]=0;
        desc3[strlen(desc3)-1]=0;
        for(i=0;i<13;i++)
            name3[i]=buff[i];
        rewind(monster);
    
        printf("Your Team:\n\n");
        printf("שÝשששÞשששששששששששששß    שÝשששÞשששששששששששששß    שÝשששÞשששששששששששששß\n");
        printf("שר%2dשר%-12sשר    שר%2dשר%-12sשר    שר%2dשר%-12sשר\n",index[0],name1,index[1],name2,index[2],name3);
        printf("שאשששהשששששששששששששג    שאשששהשששששששששששששג    שאשששהשששששששששששששג\n");
        for(i=0;i<8;i++)
        {
            printf("שר");
            for(j=st;j<16*i+16;j++)
                printf("%c",desc1[j]);
            printf("שר    שר");
            for(j=st;j<16*i+16;j++)
                printf("%c",desc2[j]);
            printf("שר    שר");
            for(j=st;j<16*i+16;j++)
                printf("%c",desc3[j]);
            printf("שר");
            printf("\n");
            st+=16;
        }
        printf("שדשששששששששששששששששו    שדשששששששששששששששששו    שדשששששששששששששששששו\n\n");
        printf("Go Back<B>   Edit Team<E>");
        while(kbhit())
                getch();
            input=getch();
        system("cls");
        if(input=='b')
            return;
        else if(input=='e')
        {
            while(1)
            {
                printf("Which slot do you want to edit?\n\n<1>   <2>   <3>");
                while(kbhit())
                    getch();
                input=getch();
                if(input<4&&input>0)
                {
                    input-=48;
                    printf("Which monster would you like to choose?");
                    
                }
                
            }
            //update file here
            printf("Team successfully modified.");
            
        }
    }
    fclose(monster);
    fclose(team);
}

void box()
{
}

void help()
{
    
}

int main()
{
    srand(time(NULL));
    char input;
    while(1)
    {
        system("cls");
        printf("The CUBE\n\nMap<M>   Team<T>   Box<B>   Help<H>   Exit<E>");
        while(kbhit())
            getch();
        input=getch();
        system("cls");
        if(input=='m')
            map();
        else if(input=='t')
            teams();
        else if(input=='b')
            box();
        else if(input=='h')
            help();
        else if(input=='e')
        {
            show("Bye~",1000);
            return 0;
        }
    }
}
