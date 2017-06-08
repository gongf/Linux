/*************************************************************************
	> File Name: Kill_Signal.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Wed 07 Jun 2017 07:24:59 PM CST
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

static void usage(const char *proc)
{
    printf("Usage:%s sig pid\n", proc);     //使用手册
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }
    int pid = atoi(argv[2]);
    int sig = atoi(argv[1]);
    kill(pid, sig);
    return 0;
}
