#include <stdio.h>
#include <stdlib.h>
#include "setup.h"

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

int main()
{
     int input;
    printf("Welcome to TextPortal\nPlay <P>     Editor <E>     Exit <Esc>");
    input=get_code();
    while(input!=esc)
    {
        if(input=='p')
            game();
        else if(input=='e')
            edit();
    }
    return 0;
    return 0;
}
