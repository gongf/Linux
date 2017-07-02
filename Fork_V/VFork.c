/*************************************************************************
	> File Name: Vfork.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Fri 30 Jun 2017 05:52:25 PM CST
 ************************************************************************/

#include <stdio.h>
#include "apue.h"

//int gg = 6;
//
//int main(int argc, char *argv[])
//{
//    int var = 88;
//    pid_t pid;
//    printf("before vfork\n");
//    if((pid = vfork()) < 0)
//    {
//        error("vfork error");
//    }
//    else if(pid == 0)
//    {
//        gg++;
//        var++;
//        exit(0);
//    }
//    printf("pid = %d, gg = %d, var = %d\n", getpid(), gg, var);
//    exit(0);
//}

int main(void)
{
    int count = 0;
    int child;

    printf("Before create son, the father's count is:%d\n", count);

    if((child = vfork()) < 0)
    {
        perror("fork error:");
    }
    else if(child == 0)
    {
        printf("This is son, his count is: %d (%p). and his pid is: %d\n", ++count, &count, getpid());
        exit(0);
    }
    else
    {
        printf("After son, This is father, his count is: %d (%p), his pid is: %d\n", ++count, &count, getpid());
        exit(0);
    }
    return EXIT_SUCCESS;
}
