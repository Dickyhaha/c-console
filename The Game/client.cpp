#include "client.h"

int main(int argc, char** argv)
{
    if(argc < 4)
    {
        printf("Usage: client <ip> <port> <your name>\n");
        return -1;
    }

    Client client(argv[1], atoi(argv[2]), argv[3]);

    client.loop();
    
    return 0;
}
