#ifndef _SERVER_
#define _SERVER_

#include <winsock2.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

#define LENGTH 10
#define PLAYERS 3

using namespace std;

enum dir
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

int init_pos[4][3] = 
{
    {0          , 0         ,   RIGHT}, 
    {LENGTH -1  , LENGTH -1 ,   LEFT},
    {LENGTH -1  , 0         ,   UP},
    {0          , LENGTH -1 ,   DOWN}
};

struct Player
{
    int sock;
    int i;
    int j;
    int dir;
    int hp;
};

struct Bullet
{
    int owner;
    int i;
    int j;
    int dir;
};

class Server
{
    public:

        int sock, port;
        bool running;
        timeval start;

        std::vector<Player> player;
        std::vector<Bullet> bullet;

        std::thread update_thread;
        std::mutex mutex;

        int map[LENGTH][LENGTH];


    public:

        Server(int port): sock(-1), port(0), map(), update_thread(), running(false), mutex()
    {
        int i = 1;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&i, sizeof(int));

        sockaddr_in local, client_addr;
        local.sin_family = AF_INET;
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_port = htons(port);

        if(bind(sock, (sockaddr*)&local, sizeof(sockaddr)) == -1)
            exit(-1);

        listen(sock, 3);
    }

        ~Server()
        {
        }

        void chat(int pos)
        {
            char msg[100];
            while(running)
            {
                memset(msg, 0, sizeof(msg));
                if(read(player[pos].sock, msg, sizeof(msg)) <= 0)
                {
                    close(sock);
                    exit(-1);
                }
                else if(running)
                {
                    cout << "Player " << pos + 1 << ": " << msg;
                    for(int i=0;i<player.size();i++)
                    {
                        if(i != pos && write(player[i].sock, msg, strlen(msg)) < 0)
                            exit(-1);                  
                    }

                    if(strcmp(msg, "GO\n") == 0)
                        running = false;
                }
            }
        }

        bool join()
        {
            sockaddr_in addr;

            char msg[100][792] = {{0}};

            //std::vector<std::thread> chat_thread;

            fd_set rfds;
            timeval timeout;
            int retval;

            running = true;

            Player new_player;
            while(running && player.size() < PLAYERS)
            {
                memset(&new_player, 0, sizeof(new_player));

                FD_ZERO(&rfds);
                FD_SET(sock, &rfds);
                timeout.tv_sec = 1;
                timeout.tv_usec = 0;

                retval = select(sock + 1, &rfds, NULL, NULL, &timeout);
                if(retval == -1)
                    exit(-1);
                else if(retval == 0)
                    continue;

				int c = sizeof(sockaddr);
                new_player.sock = accept(sock, (sockaddr*)&addr, &c);

                if(new_player.sock == -1)
                    continue;

                if(!running)
                {
                    close(new_player.sock);
                    break;
                }

                cout << "Client accepted" << endl;

                player.push_back(new_player);
                //chat_thread.push_back(std::thread(&Server::chat, this, player.size() - 1));

                cout << "Client registered" << endl;
            }

            memset(msg, 0, sizeof(msg));
            for(int i=0;i<player.size();i++)
            {
                if(i < 4)
                {
                    player[i].i     = init_pos[i][0];
                    player[i].j     = init_pos[i][1];
                    player[i].dir   = init_pos[i][2];
                    player[i].hp    = 100;
                }
                else
                {
                    while(1)
                    {
                        player[i].i = rand()%LENGTH;
                        player[i].j = rand()%LENGTH;
                        int j;
                        for(j=0;j<player.size();j++)
                            if(i != j && player[i].i == player[j].i && player[i].j == player[j].j)
                                break;
                        if(j == player.size())
                            break;
                    }
                    player[i].dir = rand()%4;
                    player[i].hp = 100;
                }

                sprintf(msg[i], "%d:%d:%d:%d:", player[i].i, player[i].j, player[i].hp, player[i].dir);
                for(int j=0;j<player.size();j++)
                    if(i != j)
                        sprintf(msg[i], "%s%d:%d:%d:%d:", msg[i], player[j].i, player[j].j, player[j].hp, player[j].dir);
                sprintf(msg[i], "%s-1:", msg[i]);
            }

            for(int i=0;i<player.size();i++)
            {
                cout << msg[i] << endl;
                if(write(player[i].sock, msg[i], strlen(msg[i])) <= 0)
                {
                    close(sock);
                    return false;
                }
            }

            //for(int i=0;i<chat_thread.size();i++)
                //chat_thread[i].join();

            return true;
        }

        bool update_bullet()
        {
            timeval current;
            while(running)
            {
                gettimeofday(&current, NULL);
                if((current.tv_sec - start.tv_sec)*1000 + (current.tv_usec - start.tv_usec)/1000 > 100)
                {
                    gettimeofday(&start, NULL);
                    for(std::vector<Bullet>::iterator it = bullet.begin(); it != bullet.end();)
                    {
                        if(it->dir == UP && it->i > 0)
                            it->i--;
                        else if(it->dir == DOWN && it->i < LENGTH - 1)
                            it->i++;
                        else if(it->dir == LEFT && it->j > 0)
                            it->j--;
                        else if(it->dir == RIGHT && it->j < LENGTH - 1)
                            it->j++;
                        else
                        {
                            bullet.erase(it);
                            continue;
                        }
                        it++;
                    }
                    update();
                }
            }
        }

        void update()
        {
            mutex.lock();

            int i;
            for(std::vector<Bullet>::iterator it = bullet.begin(); it != bullet.end();)
            {
                for(i=0;i<player.size();i++)
                    if(it->i == player[i].i && it->j == player[i].j && it->owner != i)
                    {
                        player[i].hp -= 10;
                        if(player[i].hp <= 0)
                        {
                            close(sock);
                            exit(0);
                        }
                        bullet.erase(it);
                        break;
                    }
                if(i == player.size())
                    it++;
            }

            char msg[100][402] = {0};

            for(int i=0;i<player.size();i++)
            {
                sprintf(msg[i], "%d:", player[i].hp);

                for(int j=0;j<player.size();j++)
                    if(i != j)
                        sprintf(msg[i], "%s%d:%d:%d:%d:", msg[i], player[j].i, player[j].j, player[j].hp, player[j].dir);

                for(int j=0;j<bullet.size();j++)
                    sprintf(msg[i], "%s%d:%d:", msg[i], bullet[j].i, bullet[j].j);

                strcat(msg[i], "-1");
            }

            mutex.unlock();

            for(int i=0;i<player.size();i++)
            {
                if(write(player[i].sock, msg[i], strlen(msg[i])) <= 0)
                {
                    close(sock);
                    exit(-1);
                }
            }

            return;
        }

        void loop()
        {
            gettimeofday(&start, NULL);
            running = true;
            update_thread = std::thread(&Server::update_bullet, this);

select();
            pollfd* list = new pollfd[player.size()];
            memset(list, 0, sizeof(list));
            for(int i=0;i<player.size();i++)
            {
                list[i].fd = player[i].sock;
                list[i].events = POLLIN;
            }

            int num;
            char msg[8];
            while(1)
            {
                num = poll(list, player.size(), 100);
                if(num < 0)
                    break;
                else if(num > 0)
                {
                    for(int i=0;i<player.size();i++)
                    {
                        if(list[i].revents & POLLIN)
                        {
                            list[i].revents = 0;
                            memset(msg, 0, sizeof(msg));
                            if(recv(list[i].fd, msg, sizeof(msg), 0) <= 0)
                            {
                                close(sock);
                                delete[] list;
                                exit(-1);
                                return;
                            }

                            cout << msg << endl;
                            mutex.lock();

                            player[i].i = atoi(strtok(msg, ":"));
                            player[i].j = atoi(strtok(NULL, ":"));
                            player[i].dir = atoi(strtok(NULL, ":"));
                            if(atoi(strtok(NULL, ":")))
                            {
                                Bullet new_bullet;
                                new_bullet.owner = i;
                                new_bullet.dir = player[i].dir;
                                switch(player[i].dir)
                                {
                                    case UP:
                                        new_bullet.i = player[i].i - 1;
                                        new_bullet.j = player[i].j;
                                        break;
                                    case DOWN:
                                        new_bullet.i = player[i].i + 1;
                                        new_bullet.j = player[i].j;
                                        break;
                                    case LEFT:
                                        new_bullet.i = player[i].i;
                                        new_bullet.j = player[i].j - 1;
                                        break;
                                    case RIGHT:
                                        new_bullet.i = player[i].i;
                                        new_bullet.j = player[i].j + 1;
                                        break;
                                }

                                int j;
                                for(j=0;j<bullet.size();j++)
                                    if(new_bullet.i == bullet[j].i && new_bullet.j == bullet[j].j)
                                        break;

                                if(j == bullet.size())
                                    bullet.push_back(new_bullet);
                            }

                            mutex.unlock();
                        }
                    }
                    update();
                }
            }

            running = false;
            if(update_thread.joinable())
                update_thread.join();
            return;
        }

};

#endif
