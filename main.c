#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#if 0

void *rout (void *arg)
{
    for (;;)
    {
        printf ("I'am thread 1\n");
        sleep (1);
    }
}

//void test ()
//{
//    pthread_mutex_t mutex;
//    mutex = PTHREAD_MUTEX_INITIALIZER;
//    pthread_mutex_lock (mutex);// 阻塞
//    pthread_mutex_trylock (mutex); //非阻塞
//    pthread_mutex_unlock (mutex); //解锁
//    pthread_mutex_destroy (mutex);//销毁
//}

int main (void)
{
    pthread_t tid;
    int       ret;
    if ((ret = pthread_create (&tid, NULL, rout, NULL)) != 0)
    {
        fprintf (stderr, "pthread_create : %s\n", strerror (ret));
        exit (EXIT_FAILURE);
    }
    int i;
    for (;;)
    {
        printf ("I'am main thread\n");
        sleep (1);
    }
}

#endif

#if 0
int tickets = 100;

void *scalpers (void *arg)
{
    pthread_mutex_t *mutex = (pthread_mutex_t *) arg;
    pthread_t       tid    = pthread_self ();
    while (1)
    {
        pthread_mutex_lock (mutex);
        if (tickets > 0)
        {
            usleep (1);
            printf ("我抢到票了:%p-%d\n", tid, tickets);
            tickets--;
            pthread_mutex_unlock (mutex);
        }
        else
        {
            pthread_mutex_unlock (mutex);
            pthread_exit (NULL);
        }
    }
//    return NULL;
}

int main ()
{
    pthread_mutex_t mutex;
    pthread_t       tid[4];
    int             ret;
    pthread_mutex_init (&mutex, NULL);
    for (int i = 0; i < 4; ++i)
    {
        ret = pthread_create (&tid[i], NULL, scalpers, (void *) &mutex);
        if (ret != 0)
        {
            perror ("thread create error!线程创建错误！\n");
            return -1;
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        pthread_join (tid[i], NULL);
    }
    pthread_mutex_destroy (&mutex);
    return 0;
}

#endif

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

int             ticket = 100;
pthread_mutex_t mutex;

void *route (void *arg)
{
    char *id = (char *) arg;
    while (1)
    {
        pthread_mutex_lock (&mutex);
        if (ticket > 0)
        {
            usleep (10);
            printf ("%s sells ticket:%d\n", id, ticket);
            ticket--;
            pthread_mutex_unlock (&mutex);
            // sched_yield(); 放弃CPU
        }
        else
        {
            pthread_mutex_unlock (&mutex);
            break;
        }
    }
}

int main (void)
{
    pthread_t t1, t2, t3, t4;
    pthread_mutex_init (&mutex, NULL);
    pthread_create (&t1, NULL, route, "thread 1");
    pthread_create (&t2, NULL, route, "thread 2");
    pthread_create (&t3, NULL, route, "thread 3");
    pthread_create (&t4, NULL, route, "thread 4");
    pthread_join (t1, NULL);
    pthread_join (t2, NULL);
    pthread_join (t3, NULL);
    pthread_join (t4, NULL);
    pthread_mutex_destroy (&mutex);
}

#endif

#if 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int tickets = 100;

void *scalpers (void *arg)
{
    pthread_mutex_t *mutex = (pthread_mutex_t *) arg;
    pthread_t       tid    = pthread_self ();
    while (1)
    {
        pthread_mutex_lock (mutex);
        if (tickets > 0)
        {
            usleep (1);
            printf ("I got a ticket：%p-%d\n", tid, tickets);
            tickets--;
        }
        else
        {
            //加锁后，则任意有可能退出线程之前解锁
            pthread_mutex_unlock (mutex);
            pthread_exit (NULL);
        }
        pthread_mutex_unlock (mutex);
    }
}

int main (int argc, char *argv[])
{
    pthread_mutex_t mutex;
    pthread_t       tid[4];
    int             ret;
    pthread_mutex_init (&mutex, NULL);
    for (int i = 0; i < 4; i++)
    {
        ret = pthread_create (&tid[i], NULL, scalpers, (void *) &mutex);
        if (ret != 0)
        {
            printf ("thread create error\n");
            return -1;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_join (tid[i], NULL);
    }
    pthread_mutex_destroy (&mutex);
    return 0;
}

#endif