/*************************************************************************
	> File Name: comm.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 23 May 2017 08:09:01 PM CST
 ************************************************************************/

#include "comm.h"

static int CommShm(int flags)
{
    key_t _k = ftok(PATHNAME, PROJID);
    if(_k == -1)
    {
        perror("ftok");
        return -1;
    }

    int shmid = shmget(_k, SIZE, flags);
    if(shmid == -1)
    {
        perror("shmget");
        return -1;
    }
    return shmid;
}

int CreateShm()
{
    int flags = IPC_CREAT|IPC_EXCL|0666;
    return CommShm(flags);
}

int GetShm()
{
    return CommShm(0);      //默认会调用IPC_CREATE
}

void* ShmAt(int shmid)
{
    void* ret = shmat(shmid, NULL, 0);
    if(ret == (void*)-1)
    {
        perror("shmat");
    }
    return (void*)ret;
}

int ShmDt(void* addr)
{
    if(ShmDt(addr) < 0)
    {
        perror("shmat");
        return -1;
    }
    return 0;
}

int DestoryShm(int shmid)
{
    if(shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        perror("shmctl");
        return -1;
    }
    return 0;
}
