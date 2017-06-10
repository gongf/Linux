/*************************************************************************
	> File Name: Pend_Sig.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Fri 09 Jun 2017 01:55:33 PM CST
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void print_pending(sigset_t *pending)
{
    int i = 1;
    for(; i < 32; ++i)
    {
        if(sigismember(pending, i))
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

void handler(int sig)
{
    printf("sig: %d\n", sig);
    return;
}

int main()
{
    sigset_t sigset, osigset;   //创建信号集
    sigemptyset(&sigset);   //初始化信号集
    sigemptyset(&osigset);  // ^
    sigaddset(&sigset, 2); //将信号集的2号位置 置为 1
    sigprocmask(SIG_SETMASK, &sigset, &osigset);    //备份功能
                                                    //即将sigset备份到osigset以便后面恢复

    signal(2, handler); //执行捕捉2号信号操作

    int count = 0;
    sigset_t pending;

    while(1)
    {
        sigpending(&pending);   //读取未决信号集
        print_pending(&pending);//打印当前进程未决表
        sleep(1);
        if(count++ > 5)
        {
            sigprocmask(SIG_SETMASK, &osigset, &sigset);
            count = 0;
        }
    }
}
