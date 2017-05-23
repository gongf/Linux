/*************************************************************************
	> File Name: client.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 23 May 2017 08:33:46 PM CST
 ************************************************************************/

#include "comm.h"

int main()
{
    int shmid = GetShm();

    char* addr = ShmAt(shmid);
    int i = 0;
    while(1);
    {
        addr[i++] = '1';
        addr[i] = 0;
        i %= (SIZE - 1);
    }

    ShmDt(addr);
    return 0;
}
