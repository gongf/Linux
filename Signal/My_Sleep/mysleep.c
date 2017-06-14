/*************************************************************************
	> File Name: mysleep.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Wed 14 Jun 2017 04:07:37 PM CST
 ************************************************************************/

#include <stdio.h>

#include <stdio.h>
#include <signal.h>
 
void my_handler(int sig)
{}

int mysleep(int timeout)
{
    struct sigaction act, oact;     //推荐用结构体取代signal函数
    act.sa_handler = my_handler;    //设置捕捉函数
    sigemptyset(&act.sa_mask);      //清空信号屏蔽集
    act.sa_flags = 0;               //默认0
    sigaction(SIGALRM, &act, &oact);//注册SIGALRM信号处理动作
    
    alarm(timeout);     //设置闹钟
    //pause();          //程序挂起，直到有信号递达
    sigsuspend(&mask);  //解除对SIGALRM屏蔽，程序挂起，直到信号递达
    int ret = alarm(0); //取消闹钟，返回上次闹钟剩余时间
    sigaction(SIGALRM, &oact, NULL);//恢复默认信号处理动作
    return ret;
}
 
int main()
{
    while(1)
    {
        mysleep(2);
        printf("use mysleep!\n");
    }
    return 0;
}
