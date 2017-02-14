#include <stdio.h>
#include <stdlib.h>
#include <time.h>

     
void display(int i,int j,int k)
{
    system("cls");
    printf("Slot machine(Operating)");
    printf("\nשÝשששÞשששÞשששß\nשר%2dשר%2dשר%2dשר\nשר%2dשר%2dשר%2dשר¡צ\nשר%2dשר%2dשר%2dשר\nשדשששהשששהשששו\n\n",(i+1)%9+1,(j+1)%9+1,(k+1)%9+1,i%9+1,j%9+1,k%9+1,(i-1)%9+1,(j-1)%9+1,(k-1)%9+1);
    sleep(50);
    return;
}

void slot(void)
{
    int i,j,k,input=0,time,c1,c2,c3,real;
    printf("Slot machine\n");
    printf("שÝשששÞשששÞשששß\nשר Xשר Xשר Xשר\nשר Xשר Xשר Xשר¡צ\nשר Xשר Xשר Xשר\nשדשששהשששהשששו\n\n");
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
