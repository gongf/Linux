/*************************************************************************
	> File Name: Single_List.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Thu 01 Jun 2017 08:18:41 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;   //互斥锁
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;    //条件变量

typedef struct node_list    //一个交易场所
{
    int _data;
    struct node_list *_next;
}node, *node_p, **node_pp;

node_p head;

static node_p alloc_node(int data)
{
    node_p newNode = (node_p)malloc(sizeof(node));
    if(newNode == NULL)
    {
        perror("malloc");
        exit(1);
    }
    newNode->_next = NULL;
    newNode->_data = data;
    return newNode;
}

static void free_node(node_p del)
{
    if(del)
    {
        free(del);
        del = NULL;
    }
}

void initList(node_pp h)
{
    *h = alloc_node(0);
}

void pushHead(node_p h, int data)
{
    node_p newNode = alloc_node(data);
    newNode->_next = h->_next;
    h->_next = newNode;
}

int IsEmpty(node_p h)
{
    return h->_next == NULL ? 1 : 0;
}

void popHead(node_p h, int *data)
{
    if(!IsEmpty(h))
    {
        node_p del = h->_next;
        h->_next = del->_next;
        *data = del->_data;
        free_node(del);
    }
}

void showList(node_p h)
{
    node_p cur = h->_next;
    while(cur)
    {
        printf("%d ", cur->_data);
        cur = cur->_next;
    }
    printf("\n");
}

void DestoryList(node_p h)
{
    int data = 0;
    if(IsEmpty(h))
    {
        popHead(h, &data);
    }
    free_node(h);
}

void *product_run(void *arg)    //生产者往链表的头插数据
{
    int data = 0;
    node_p h = (node_p)arg;
    while(1)
    {
        usleep(1000000);
        data = rand()%1000;
        pthread_mutex_lock(&lock);  //加锁
        pushHead(h, data);
        pthread_mutex_unlock(&lock);    //解锁
        pthread_cond_signal(&cond);     //唤醒等待的线程
        printf("product is done ..\n");
    }
}

void *consumer_run(void *arg)   //消费者从链表的头删数据
{
    int data = 0;
    node_p h = (node_p)arg;
    while(1)
    {
        pthread_mutex_lock(&lock);  //加锁
        if(IsEmpty(h))
        {
            pthread_cond_wait(&cond, &lock);
        }
        popHead(h, &data);
        pthread_mutex_unlock(&lock);
        printf("consumer is done, data is %d\n", data);
    }
}

int main()
{
    initList(&head);

    pthread_t product;
    pthread_t consumer;

    pthread_create(&product, NULL, product_run, (void*)head);
    pthread_create(&consumer, NULL, consumer_run, (void*)head);

    pthread_join(product, NULL);
    pthread_join(consumer, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
