/*************************************************************************
	> File Name: Pthread.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Sun 28 May 2017 10:28:03 PM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int g_val = 0;

void *thread_run(void *arg)
{
    int i = 0;
    while(i < 5000)
    {
        int tmp = g_val;
        printf("pthread_id = %ul, g_val = %d\n", pthread_self(), g_val);
        g_val = tmp + 1;
        i++;
    }
}

int main()
{
    pthread_t tid_1, tid_2;
    pthread_create(&tid_1, NULL, thread_run, NULL);
    pthread_create(&tid_2, NULL, thread_run, NULL);
    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    printf("g_val = %d\n", g_val);
    return 0;
}
