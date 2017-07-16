/*************************************************************************
	> File Name: server.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Sun 02 Jul 2017 09:12:03 AM CST
 ************************************************************************/

#include "apue.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

static void usage(char *proc)
{
    printf("Usage:%s, [client_ip], [client_port]\n", proc);
}

int startup(char* _ip, int _port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(_port);
    local.sin_addr.s_addr = inet_addr(_ip);

    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        perror("bind");
        exit(2);
    }

    if(listen(sock, 5) < 0)
    {
        perror("listen");
        exit(3);
    }
    return sock;
}

void *thread_run(void *arg)
{
    int sock = *((int *) arg);
    char buf[1024];
    while(1)
    {
        ssize_t s = read(sock, buf, sizeof(buf) - 1);
        if(s < 0)
        {
            perror("read");
        }
        else if(s > 0)
        {
            buf[s] = 0;
            printf("client: %s\n", buf);
            write(sock, "汶洋草泥马\n", sizeof("汶洋草泥马\n") - 1);
        }
        else
        {
            printf("client is quiet\n");
            close(sock);
            break;
        }
    }
    close(sock);
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(argv[1], atoi(argv[2]));
    
    struct sockaddr_in remote;
    socklen_t len = sizeof(remote);

    while(1)
    {
        int newsock = accept(listen_sock, (struct sockaddr*)&remote, &len);
        if(newsock < 0)
        {
            perror("accept");
            continue;
        }
        pthread_t tid;
        int ret = printf("client: ip:%s, port:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
        pthread_create(&tid, NULL, thread_run, &newsock);
        if(ret < 0)
        {
            perror("pthread_create");
            exit(4);
        }
        pthread_detach(tid);
    }
    return 0;
}
