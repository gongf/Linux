/*************************************************************************
	> File Name: Single_Ring.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Fri 02 Jun 2017 02:29:42 PM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define Blank 64
#define Data 0

//环形队列生产者消费者模型
int bank[Blank];
sem_t pro, con;

pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;

void* protucer_run(void *arg)
{
    int i = 0;
    while(1)
    {
        sem_wait(&pro);
        int producer_data = rand()%1000;
        i %= Blank;
        bank[i] = producer_data;
        printf("protucer make done ! Data:%d\n", producer_data);
        i++;
        sem_post(&con);
        sleep(1);
    }
}

void* consumer_run(void *arg)
{
    int c = 0;
    while(1)
    {
        sem_wait(&con);
        c %= Blank;
        int consumer_data = bank[c];
        printf("consumer using out ! Data:%d\n", consumer_data);
        c++;
        sem_post(&pro);
        sleep(1);
    }
}

int main()
{
    sem_init(&pro, 0, Blank);
    sem_init(&con, 0, Data);

    pthread_t producer, consumer;
    pthread_t producer_1, consumer_1;

    pthread_create(&producer, NULL, protucer_run, NULL);
    pthread_create(&producer_1, NULL, protucer_run, NULL);
    pthread_create(&consumer, NULL, consumer_run, NULL);
    pthread_create(&consumer_1, NULL, consumer_run, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&pro);
    sem_destroy(&con);

    return 0;
}
