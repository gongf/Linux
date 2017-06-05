/*************************************************************************
	> File Name: comm.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Sun 04 Jun 2017 10:54:44 PM CST
 ************************************************************************/

#ifndef _COMM_H
#define _COMM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PATHNAME "."
#define PROJ_ID 64

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *_buf;
};

int creatSemSet(int nums);
int initSemSet(int semid, int num, int initVal);
int getSemSet();
int destroySemSet(int semid);
int P(int semid, int num);
int V(int semid, int num);

#endif
