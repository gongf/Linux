/*************************************************************************
	> File Name: Alarm_Sig.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Wed 07 Jun 2017 08:06:23 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    static int count = 0;
    printf("count: %d\n", count);
    if(++count < 5)
    {
        alarm(1);
    }
    else
    {
        printf("Compele...\n");
        exit(0);
    }
}

int main()
{
    signal(SIGALRM, handler);
    alarm(1);
    while(1);
    return 0;
}
