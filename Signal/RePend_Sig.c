/*************************************************************************
	> File Name: RePend_Sig.c
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
    //重新捕捉，从递达到未决
    sigset_t sigset, osigset;
    sigemptyset(&sigset);
    sigemptyset(&osigset);
    sigaddset(&sigset, 2);
    sigprocmask(SIG_SETMASK, &sigset, &osigset);
}

void handler(int sig)
{
    printf("sig: %d\n", sig);
    return;
}

int main()
{
    sigset_t sigset, osigset;
    sigemptyset(&sigset);
    sigemptyset(&osigset);
    sigaddset(&sigset, 2);
    sigprocmask(SIG_SETMASK, &sigset, &osigset);

    signal(2, handler);

    int count = 0;
    sigset_t pending;

    while(1)
    {
        sigpending(&pending);
        print_pending(&pending);
        sleep(1);
        if(count++ > 5)
        {
            sigprocmask(SIG_SETMASK, &osigset, &sigset);
            count = 0;
        }
    }
}
