/*************************************************************************
	> File Name: client.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 04 Jul 2017 11:23:05 PM CST
 ************************************************************************/

#include <stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage:[server_ip] [server_port]\n", argv[0]);
        exit(1);
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }

    struct sockaddr_in remote;
    remote.sin_family = AF_INET;
    remote.sin_port = htons(atoi(argv[2]));
    remote.sin_addr.s_addr = inet_addr(argv[1]);
    socklen_t len = sizeof(remote);

    char buf[1024];
    while(1)
    {
        printf("Please Enter:");
        fflush(stdout);
        ssize_t _s = read(0, buf, sizeof(buf) - 1);
        buf[_s - 1] = 0;
        size_t s = sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&remote, len);
        if(s < 0)
        {
            perror("sendto");
            exit(3);
        }
    }
    close(sock);
    return 0;
}
