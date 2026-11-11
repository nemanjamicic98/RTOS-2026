#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_ITERATIONS 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int current_turn = 3;

void* thread_func(void *pParam)
{
    int id = *((int *)pParam);
    int i;

    for (i = 0; i < MAX_ITERATIONS; i++)
    {
        pthread_mutex_lock(&mutex);

    
        while (current_turn != id) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("%d", id);
        fflush(stdout);

        if (id == 3) {
            current_turn = 2;
        } else if (id == 2) {
            current_turn = 1;
        } else if (id == 1) {
            current_turn = 3;
        }

        pthread_cond_broadcast(&cond);
        
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(void)
{
    pthread_t hPrint1, hPrint2, hPrint3;
    
    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    pthread_create(&hPrint3, NULL, thread_func, &id3);
    pthread_create(&hPrint2, NULL, thread_func, &id2);
    pthread_create(&hPrint1, NULL, thread_func, &id1);

    pthread_join(hPrint3, NULL);
    pthread_join(hPrint2, NULL);
    pthread_join(hPrint1, NULL);

    printf("\nZavrseno 100 ispisa.\n");

    return 0;
}
