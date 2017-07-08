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

//使用说明
static void usage(char *proc)
{
    printf("Usage:%s, [client_ip], [client_port]\n", proc);
}

//启动程序包括：
//1.创建
//2.绑定
//3.监听
int startup(char* _ip, int _port)
{
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    //填充套接字必要信息
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(_port);
    local.sin_addr.s_addr = inet_addr(_ip);

    //绑定
    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        perror("bind");
        exit(2);
    }

    //监听
    if(listen(sock, 5) < 0)
    {
        perror("listen");
        exit(3);
    }
    return sock;
}

int main(int argc, char* argv[])
{
    //判断命令行参数是否合法，调用使用方法函数
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    //创建监听套接字
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
        char buf[1024];     //创建接收缓冲区

        //打印客户端信息
        printf("client: ip:%s, port:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
        while(1)
        {
            //read接收数据
            ssize_t s = read(newsock, buf, sizeof(buf) - 1);
            //当前已连接的套接字中考虑是否存在数据的传输
            if(s < 0)
            {
                perror("read");
            }
            else if(s > 0)
            {
                buf[s] = 0;
                printf("client: %s\n", buf);
                //write回写到远端客户端
                write(newsock, "汶洋草泥马\n", sizeof("汶洋草泥马\n") - 1);
            }
            else
            {
                printf("client is quiet\n");
                //使用完毕关闭创建的套接字，节省资源
                close(newsock);
                break;
            }
        }
        close(newsock);
    }
    return 0;
}
