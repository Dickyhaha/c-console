#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE * stage;
    stage=fopen("ignoreme/one.txt","r+");
    rewind(stage);
    fprintf(stage,"000000000");
    fclose(stage);
    printf("Reset successful.");
    getch();
    return 0;
}
