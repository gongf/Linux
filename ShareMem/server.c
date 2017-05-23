/*************************************************************************
	> File Name: server.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 23 May 2017 08:30:46 PM CST
 ************************************************************************/

#include "comm.h"

int main()
{
    int shmid = CreateShm();
    char* addr = (char*)ShmAt(shmid);
    while(1)
    {
        printf("%s\n", addr);
    }
    ShmDt(addr);
    DestoryShm(shmid);
    return 0;
}
