/*************************************************************************
	> File Name: sem_main.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Mon 05 Jun 2017 08:14:13 PM CST
 ************************************************************************/

#include "comm.h"

int main()
{
    int semid = creatSemSet(1);
    initSemSet(semid, 0, 1);
    pid_t pid = fork();
    if(pid == 0)
    {
        int semid = getSemSet();
        int i = 0;
        while(i < 50)
        {
            P(semid, 0);
            printf("A");
            fflush(stdout);
            usleep(100000);
            printf("A");
            fflush(stdout);
            usleep(100000);
            V(semid, 0);
            ++i;
        }
    }
    else
    {
        int i = 0;
        while(i < 50)
        {
            P(semid, 0);
            printf("B");
            fflush(stdout);
            usleep(100000);
            printf("B");
            fflush(stdout);
            usleep(100000);
            V(semid, 0);
            ++i;
        }
        waitpid(pid, 0, 0);
        destroySemSet(semid);
    }
    return 0;
}

