#ifndef _CLIENT_
#define _CLIENT_

#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

#else
#include <winsock2.h>
#include <conio.h>
#endif


#include <vector>
#include <thread>
#include <mutex>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#define LENGTH 10

enum dir
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

struct Player
{
    int i;
    int j;
    int dir;
    int hp;
};

class Client
{
    public:

#ifdef __linux__
        int sock;
#else
        SOCKET sock;
#endif

        Player me;
        std::vector<Player> enemy;

        char map[LENGTH][LENGTH];
        char name[100];

        bool running;
        std::thread thread;
        std::mutex mutex;

    public:

        Client(char* ip, int port, char* id): sock(-1), thread(), mutex(), running(true), map{{0}}
        {
            int i = 1;
            strcpy(name, id);

            sock = socket(AF_INET, SOCK_STREAM, 0);
#ifdef __linux__
            setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));
            setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &i, sizeof(int));
#else
            setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&i, sizeof(int));
#endif

            sockaddr_in local;
            local.sin_family = AF_INET;
            local.sin_addr.s_addr = inet_addr(ip);
            local.sin_port = htons(port);

            if(connect(sock, (sockaddr*)&local, sizeof(sockaddr)) < 0)
            {
                perror("Connect failed");
                exit(-1);
            }

            char msg[402];

            running = true;
            std::thread chat_thread(&Client::chat, this);
            while(running)
            {
                memset(msg, 0, sizeof(msg));
                if(recv(sock, msg, sizeof(msg), 0) <= 0)
                {
                    close(sock);
                    exit(1);
                }
                else if(strcmp(msg, "GO\n") == 0)
                    running = false;

                cout << "\b\b\b\b\b" << msg << endl;
                cout << "You: ";
                fflush(stdout);
            }

            chat_thread.join();
            cout << "Reading game data" << endl;


            memset(msg, 0, sizeof(msg));
            if(recv(sock, msg, sizeof(msg), 0) <= 0)
            {
                perror("Recv failed\n");
                exit(-1);
            }        

            cout << msg << endl;

            me.i = atoi(strtok(msg, ":"));
            me.j = atoi(strtok(NULL, ":"));
            me.hp = atoi(strtok(NULL, ":"));
            me.dir = atoi(strtok(NULL, ":"));

            Player new_enemy;
            while(1)
            {
                int val = atoi(strtok(NULL, ":"));
                if(val == -1)
                    break;

                new_enemy.i = val;
                new_enemy.j = atoi(strtok(NULL, ":"));
                new_enemy.hp = atoi(strtok(NULL, ":"));
                new_enemy.dir = atoi(strtok(NULL, ":"));
                enemy.push_back(new_enemy);
            }
        }

        void chat()
        {
            char input;
            char msg[100] = {0};
            char temp[100]= {0};
            cout << "Room joined\nYou: ";
            while(running)
            {                
                input = getchar();
                if(input != '\n')
                    sprintf(msg, "%s%c", msg, input);
                else
                {
                    strcat(msg, "\n");
                    if(strcmp(msg, "READY\n") == 0)
                    {
                        if(write(sock, msg, strlen(msg)) <= 0)
                        {
                            close(sock);
                            exit(-1);
                        }
                        cout << "READY!" << endl; 
                        return;
                    }
                    else              
                    {
                        sprintf(temp, "%s: %s", name, msg);
                        if(write(sock, temp, strlen(temp)) <= 0)
                        {
                            close(sock);
                            exit(-1);
                        }
                        cout << "\nYou: ";
                        fflush(stdout);
                    }


                    input = 0;
                    memset(msg, 0, sizeof(msg));
                    memset(temp, 0, sizeof(temp));
                }
            }
        }

        void update()
        {
            char msg[402];
            int pi,pj;
            while(running)
            {
                memset(msg, 0, sizeof(msg));
                if(recv(sock, msg, sizeof(msg), 0) <= 0)
                {
                    close(sock);
                    exit(-1);
                    return;
                }

                for(int i=0;i<LENGTH;i++)
                    for(int j=0;j<LENGTH;j++)
                        map[i][j] = ' ';

                me.hp = atoi(strtok(msg, ":"));
                if(me.i != -1 && me.j != -1)
                {
                    if(me.dir == UP)
                        map[me.i][me.j] = '^';
                    if(me.dir == DOWN)
                        map[me.i][me.j] = 'v';
                    if(me.dir == LEFT)
                        map[me.i][me.j] = '<';
                    if(me.dir == RIGHT)
                        map[me.i][me.j] = '>';
                }


                for(int i=0;i<enemy.size();i++)
                {
                    enemy[i].i = atoi(strtok(NULL, ":"));
                    enemy[i].j = atoi(strtok(NULL, ":"));
                    enemy[i].hp = atoi(strtok(NULL, ":"));
                    enemy[i].dir = atoi(strtok(NULL, ":"));

                    if(enemy[i].i != -1 && enemy[i].j != -1)
                    {
                        if(enemy[i].dir == UP)
                            map[enemy[i].i][enemy[i].j] = '^';
                        if(enemy[i].dir == DOWN)
                            map[enemy[i].i][enemy[i].j] = 'v';
                        if(enemy[i].dir == LEFT)
                            map[enemy[i].i][enemy[i].j] = '<';
                        if(enemy[i].dir == RIGHT)
                            map[enemy[i].i][enemy[i].j] = '>';
                    }
                }

                while(1)
                {              
                    pi = atoi(strtok(NULL, ":"));
                    if(pi == -1)
                        break;

                    pj = atoi(strtok(NULL, ":"));
                    if(pj == -1)
                        break;

                    if(pi >=0 && pi < LENGTH && pj >=0 && pj < LENGTH)
                        map[pi][pj] = '.';
                }

#ifdef __linux__
                system("clear");
#else
                system("cls");
#endif
                cout << "x x x x x x x x x x x x " << endl;
                for(int i=0;i<LENGTH;i++)
                {
                    cout << "x ";
                    for(int j=0;j<LENGTH;j++)
                        cout << map[i][j] << " ";
                    cout << "x " << endl;
                }
                cout << "x x x x x x x x x x x x " << endl;
                cout << "HP: " << me.hp << endl << endl;
                for(int i=0;i<enemy.size();i++)
                    cout << "Enemy " << i + 1 << " HP: " << enemy[i].hp << endl;
            }
        }

        bool check(int dir)
        {
            for(int i=0;i<enemy.size();i++)
            {
                if(dir == UP    && me.i - 1 == enemy[i].i && me.j == enemy[i].j || 
                        dir == DOWN  && me.i + 1 == enemy[i].i && me.j == enemy[i].j ||
                        dir == LEFT  && me.j - 1 == enemy[i].j && me.i == enemy[i].i ||
                        dir == RIGHT && me.j + 1 == enemy[i].j && me.i == enemy[i].i )
                    return false;
            }
            return true;
        }

        void loop()
        {
            running = true;
            thread = std::thread(&Client::update, this);
            char input;
            char msg[8];

            cout << "Game start" << endl;

            while(1)
            {
                input = getch();
                switch(input)
                {
                    case 'w':
                        if(me.dir != UP)
                            me.dir = UP;
                        else if(me.i > 0 && check(UP))
                            me.i--;
                        break;
                    case 's':
                        if(me.dir != DOWN)
                            me.dir = DOWN;
                        else if(me.i < LENGTH - 1 && check(DOWN))
                            me.i++;
                        break;
                    case 'a':
                        if(me.dir != LEFT)
                            me.dir = LEFT;
                        else if(me.j > 0 && check(LEFT))
                            me.j--;
                        break;
                    case 'd':
                        if(me.dir != RIGHT)
                            me.dir = RIGHT;
                        else if(me.j < LENGTH - 1 && check(RIGHT))
                            me.j++;
                        break;
                }
                sprintf(msg, "%d:%d:%d:%d:", me.i, me.j, me.dir, (int)(input==' '));
                if(send(sock, msg, strlen(msg),0) < 0)
                {
                    running = false;
                    thread.join();
                    return;
                }
            }

        }

#ifdef __linux__
        char getch()
        {
            char buf=0;
            struct termios old={0};
            fflush(stdout);
            if(tcgetattr(0, &old)<0)
                perror("tcsetattr()");
            old.c_lflag&=~ICANON;
            old.c_lflag&=~ECHO;
            old.c_cc[VMIN]=1;
            old.c_cc[VTIME]=0;
            if(tcsetattr(0, TCSANOW, &old)<0)
                perror("tcsetattr ICANON");
            if(read(0,&buf,1)<0)
                perror("read()");
            old.c_lflag|=ICANON;
            old.c_lflag|=ECHO;
            if(tcsetattr(0, TCSADRAIN, &old)<0)
                perror ("tcsetattr ~ICANON");
            return buf;
        }

#endif

};

#endif
