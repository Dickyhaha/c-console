#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int a;
    printf("This is a simple passcode unlocker.\n\nInput your code here: ");
    scanf("%d",&a);
    while(a!=199685)
    {
        system("cls");
        printf("Wrong code, please try again later in 5s");
        sleep(5000);
        system("cls");
        printf("Input your code here: ");
        scanf("%d",&a);
    }
    system("cls");
    printf("Code recognized, here is the result: ykwti\n\n");
    system("PAUSE");	
    return 0;
}
