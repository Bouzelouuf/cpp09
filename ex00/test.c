#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>

typedef struct t_clients
{
    int id;
    char msg[1024];
}   s_clients;

fd_set readfds, writefds, active;
int fdMax = 0;
int idNext = 0;
char bufferRead[12000];
char bufferWrite[12000];
t_clients clients[1024];

void ftError(char *str)
{
    if (str)
        write(2, str, strlen(str));
    else
        write(2, "Fatal error", 11);
    write(2, "\n", 1);
    exit(1);
}

void sendAll(int not)
{
    for (int i = 0; i <= fdMax; i++)
    {
        if (FD_ISSET(i, &readfds) && i != not)
            send(i, bufferWrite, strlen(bufferWrite), 0);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        ftError("Wrong number of arguments");
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        ftError(NULL);
    FD_ZERO(&active);
    bzero(&clients, sizeof(clients));
    fdMax = sockfd;
    FD_SET(sockfd, &active);
    struct sockaddr_in servaddr;
    socklen_t len;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.adrr = 0x0100007F;
    uint16_t port = atoi(av[1]);
    servaddr.sin_port = ((port &0xFF) << 8) | ((port >> 8) &0xFF);
    if (bind(sockfd, (const struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
        ftError(NULL);
    if (listen(sockfd, 10) < 0)
        ftError(NULL);
    while(1)
    {
        readfds = writefds = active;
        if (select(fdMax + 1, &readfds, &writefds, NULL, NULL) < 0)
            continue;
        for (int fdI = 0; fdI <= fdMax; fdI++)
        {
            if (FD_ISSET(fdI, &readfds) && fdI == sockfd)
            {
                len = sizeof(servaddr);
                int connfd = accept(sockfd, (struct sockaddr_in*)&servaddr, &len);
                if (connfd < 0)
                    continue;
                fdMax = connfd > fdMax ? connfd : fdMax;
                clients[connfd].id = idNext++;
                FD_SET(connfd, &active);
                sprintf("bla %d",clients[connfd].id);
                sendAll(connfd);
                break;
            }
            if (FD_ISSET(fdI, &readfds) && fdI != sockfd)
            {
                int res = recv(sockfd, bufferRead, 65536);
                if (res <= 0)
                {
                    sprintf(bufferRead, "clients %d: %s",clients[fdI].id, clients[fdI].msg);
                    sendAll(fdI);
                    FD_CLR(fdI, &active);
                    close(fdI);
                    break
                }
                else
                {
                    for (int i = 0; i < res; i++)
                    {
                        if (bufferRead[i] == '\n')
                        {
                            if (strlen(clients[fdI].msg) > 0)
                            {

                            }
                        }
                        else
                        {
                            int len = strlen(clients[fdI])
                            {
                                clients[fdI].msg[i] = bufferRead[i];
                                clients[fdI].msg[i + 1] = '\0';
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}


