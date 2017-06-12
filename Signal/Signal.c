/*************************************************************************
	> File Name: Signal.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Wed 07 Jun 2017 03:59:28 PM CST
 ************************************************************************/

//成功捕获信号后，再恢复到默认处理状态

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//typedef void(*sighandler_t) (int); //函数指针
//sighandler_t _handler = NULL;

int count = 0;

void myhandle(int sig)
{
    printf("count:%d, sig:%d\n", count++, sig);
    //printf("handle\n");
    //signal(2, _handler); //恢复默认处理
}

int main( int argc, char *argv[] )
{
    signal(2, myhandle);
    //_handler = signal(2, myhandle);
    while(1)
    {
        raise(2);   //给当前进程自己发送信号，区别kill
        sleep(1);
    }
    return 0;
}
