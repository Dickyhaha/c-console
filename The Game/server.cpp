#include "server.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage: Server <port>\n");
        return -1;
    }

    printf("Starting\n");

    while(1)
    {
        {
            Server server(atoi(argv[1]));

            printf("Joining\n");
            server.join();

            printf("Game start\n");
            server.loop();

            printf("Ended\n");
        }
    }
    return 0;
}

