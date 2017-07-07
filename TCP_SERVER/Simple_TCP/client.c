/*************************************************************************
	> File Name: client.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Sun 02 Jul 2017 09:09:32 AM CST
 ************************************************************************/

#include <stdio.h>
#include "apue.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void usage(char *proc)
{
    printf("Usage:%s, [client_ip], [client_port]\n", proc);
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[2]));
    local.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        perror("connect");
        exit(2);
    }

    char buf[1024];
    while(1)
    {
        printf("send:");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf) - 1);
        buf[s - 1] = 0;
        write(sock, buf, s - 1);
        read(sock, buf, sizeof(buf) - 1);
        printf("server echo: %s\n", buf);
    }
    close(sock);
    return 0;
}
