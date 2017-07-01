/*************************************************************************
	> File Name: Fork.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Fri 30 Jun 2017 05:16:48 PM CST
 ************************************************************************/

#include "apue.h"

//int ff = 66;
//char buf[] = "a write to stdout\n";
//
//int main(int argc, char *argv[])
//{
//    int var = 88;
//    pid_t pid;
//
//    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
//    {
//        error("write error");
//        printf("fork failure\n");
//    }
//    else if(pid == 0)
//    {
//        ff++;
//        var++;
//        exit(0);
//    }
//    printf("pid = %d, gg = %d, var = %d\n", getpid(), ff, var);
//    exit(0);
//}

int main()
{
    int count = 1;
    int child;

    child = fork();

    if(child < 0)
    {
        perror("fork error:");
    }
    else if(child == 0)
    {
        printf("This is son, his count is: %d (%p). and his pid is: %d\n", ++count, &count, getpid()); 
    }
    else
    {
        printf("This is father, his count is: %d (%p), his pid is: %d\n", count, &count, getpid());
    }
    return EXIT_SUCCESS;
}
