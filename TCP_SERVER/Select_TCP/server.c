/*************************************************************************
	> File Name: server.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Sat 08 Jul 2017 09:20:53 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE (sizeof(fd_set)*8)
int gfds[SIZE];

static void usage(char *proc)
{
    printf("Usage:%s, [client_ip], [client_port]\n", proc);
}

int startup(char *ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);

    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        perror("bind");
        exit(3);
    }

    if(listen(sock, 5) < 0)
    {
        perror("listen");
        exit(4);
    }

    return sock;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(argv[1], atoi(argv[2]));

    //初始化记录套接字的数组为-1
    int i = 0;
    for(; i < SIZE; ++i)
    {
        gfds[i] = -1;
    }

    while(1)
    {
        //监听套接字插入gfds
        gfds[0] = listen_sock;
        //定义max_fd为select的第一个参数
        int max_fd = -1;
        //创建文件描述符集
        fd_set rfds;
        //对文件描述符集进行初始化
        //每次进来都会清空文件描述符集
        FD_ZERO(&rfds);
        //将监听套接字设置在文件描述符集合当中
        FD_SET(listen_sock, &rfds);
        //扫描查找最大的文件描述符max_fd,填充select参数nfds
        int k = 0;
        for(; k < SIZE; ++k)
        {
            if(gfds[k] != -1)
            {
                if(gfds[k] > max_fd)
                {
                    max_fd = gfds[k];
                }
                //将所要关心的事件设置进文件描述符集
                FD_SET(gfds[k], &rfds);
            }
        }
        //设置timeout值
        struct timeval timeout = {2, 0};

        //进行select多路复用
        switch(select(max_fd + 1, &rfds, NULL, NULL, &timeout))
        {
            case -1:    //错误
            {
                perror("select");
                break;
            }
            case 0:     //超时
            {
                printf("time out\n");
                break;
            }
            default:
            {
                int j = 0;
                for(; j < SIZE; ++j)
                {
                    //未被使用的
                    if(gfds[j] == -1)
                    {
                        break;
                    }
                    //如果当前位被设置了，并且当前位被设置为了监听套接字(其实就是第一个位置)
                    else if(FD_ISSET(gfds[j], &rfds) && gfds[j] == listen_sock)
                    {
                        struct sockaddr_in remote;
                        socklen_t len = sizeof(remote);

                        int sock = accept(listen_sock, (struct sockaddr*)&remote, &len);
                        printf("client: ip:%s, port:%d\n",\
                               inet_ntoa(remote.sin_addr),\
                               ntohs(remote.sin_port));
                        printf("sock: %d\n", sock);
                        if(sock < 0)
                        {
                            perror("accept");
                            continue;
                        }
                        //向后轮训查找第一个未被使用的文件描述符，并进行设置使用
                        else
                        {
                            //0号位置已被listen_sock占用，故从1开始轮询
                            int m = 1;
                            for(; m < SIZE; ++m)
                            {
                                //如果当前位为-1，则跳出此循环进行使用此位
                                if(gfds[m] == -1)
                                {
                                    break;
                                }
                            }
                            //当前开辟的文件描述符集已被用完
                            if(m == SIZE)
                            {
                                close(sock);
                                printf("too many client\n");
                            }
                            //找到空位后进行使用
                            else
                            {
                                gfds[m] = sock;
                                FD_SET(gfds[m], &rfds);
                            }
                        }
                    }
                    //向后循环的过程中发现了有效的普通文件描述符，则进行读写操作
                    else if(FD_ISSET(gfds[j], &rfds))
                    {
                        char buf[SIZE];
                        ssize_t _r = read(gfds[j], buf, sizeof(buf) - 1);
                        if(_r > 0)
                        {
                            buf[_r] = 0;
                            printf("client echo: %s\n", buf);
                        }
                        else if(_r == 0)
                        {
                            printf("client is closed\n");
                            close(gfds[i]);
                            gfds[j] = -1;
                            break;
                            //continue;
                        }
                        else
                        {
                            perror("read");
                            return 5;
                        }
                    }
                }
                break;
            }
//            break;
        }
    }
    close(listen_sock);
    return 0;
}
