#include <stdio.h>
#include <stdlib.h>

int main()
{
    int password;
    printf("Password: ");
    scanf("%d",&password);
    if(password==2356)
    {
        system("cls");
        printf("You did it! You get to the ending!");
        sleep(3000);
        system("cls");
        printf("The End...:)");
        sleep(3000);
    }	
    else
    {
        system("cls");
        printf("Wrong password, try different endings.");
        sleep(3000);
    }
    return 0;
}
