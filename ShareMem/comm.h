/*************************************************************************
	> File Name: comm.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 23 May 2017 08:03:18 PM CST
 ************************************************************************/

#ifndef _COMM_H
#define _COMM_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define PATHNAME "."
#define PROJID 0x666
#define SIZE 4096*1

int CreateShm();    //创建
int GetShm();       //获得
void* ShmAt(int shmid);
int ShmDt(void* addr);
int DestoryShm(int shmid);

#endif
