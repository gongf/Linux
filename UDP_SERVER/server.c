/*************************************************************************
	> File Name: server.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 04 Jul 2017 11:22:34 PM CST
 ************************************************************************/

#include "apue.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage:[local_ip] [local_port]", argv[0]);
        exit(3);
    }
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[2]));
    local.sin_addr.s_addr = inet_addr(argv[1]);

    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        perror("bind");
        return 2;
    }

    char buf[1024];

    while(1)
    {
        struct sockaddr_in remote;
        socklen_t len = sizeof(remote);
        memset(&remote, 0, len);

        ssize_t s = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&remote, &len);
        if(s > 0)
        {
            buf[s] = 0;
            printf("client: %s\n", buf);
        }
        else if(s == 0)
        {
            printf("send quit");
            close(sock);
            break;
        }
        else
        {
            perror("recvfrom");
            break;
        }
    }
    return 0;
}
