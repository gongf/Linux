/*************************************************************************
> File Name: Block_Sig.c
> Author: hosts
> Mail: hosts@gsxio.com
> Created Time: Thu 08 Jun 2017 03:54:33 PM CST
************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void printf_signal(sigset_t *set)
{
    int i = 1;  //信号集编码从 1 开始
    for(; i < 32; ++i)
    {
        if(sigismember(set, i))     //判断指定信号是否在目标集中
        {
            printf("1 ");
        }
        else
        {
            printf("0 ");
        }
    }
    printf("\n");
}

int main()
{
    sigset_t s, p;
    sigemptyset(&s);    //位操作清空信号集
    sigaddset(&s, SIGINT);  //向信号集s中添加SIGINT 2号信号
    sigprocmask(SIG_BLOCK, &s, NULL);   //设置阻塞信号集，阻塞SIGINT
    while(1)
    {
        sigpending(&p);     //获取当前进程的未决信号集
        printf_signal(&p);
        sleep(1);
    }
    return 0;
}
