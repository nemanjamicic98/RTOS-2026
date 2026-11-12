#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


pthread_mutex_t mutex;
int active_id = 3; 

void* thread_function(void *pParam)
{
    int id = *((int*)pParam);
    int i;

    for (i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&mutex);

        while (active_id != id)
        {
            pthread_mutex_unlock(&mutex);
            usleep(1); 
            pthread_mutex_lock(&mutex);
        }

        printf("%d", id);
        fflush(stdout);

        if (id == 3)
            active_id = 2;
        else if (id == 2)
            active_id = 1;
        else if (id == 1)
            active_id = 3;

        pthread_mutex_unlock(&mutex);
    }

    return 0;
}

int main(void)
{
    pthread_t hPrint1, hPrint2, hPrint3;
    
    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&hPrint1, NULL, thread_function, &id1);
    pthread_create(&hPrint2, NULL, thread_function, &id2);
    pthread_create(&hPrint3, NULL, thread_function, &id3);

    pthread_join(hPrint1, NULL);
    pthread_join(hPrint2, NULL);
    pthread_join(hPrint3, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
