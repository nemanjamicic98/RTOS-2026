#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t mutex;

int turn = 3;   // prva na red dolazi nit 3 pa 2 pa 1

/* Tijelo niti */
void *print(void *pParam)
{

    int id = *(int *)pParam;
    int i;
    while (i < 100)
    {
        pthread_mutex_lock(&mutex);  //mutexom zakljucavamo promjenljivu turn jer 3 niti istovremeno pristupaju istoj promjenljivoj

        if (turn == id) // ako je dosao red na odgovarajucu nit
        {
            printf("%d", id);
            fflush(stdout);

            turn = id - 1;

            if (turn == 0) // poslije prve niti ponovo ide treca
                turn = 3;

            i++;
        }
        pthread_mutex_unlock(&mutex);
    }

    return 0;
}

int main(void)
{

    pthread_t hPrint1;
    pthread_t hPrint2;
    pthread_t hPrint3;

    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    pthread_mutex_init(&mutex, NULL);

    /* Formiranje niti. */
    pthread_create(&hPrint1, NULL, print, (void *)&id1);
    pthread_create(&hPrint2, NULL, print, (void *)&id2);
    pthread_create(&hPrint3, NULL, print, (void *)&id3);
    getchar();

    pthread_mutex_destroy(&mutex);

    return 0;
}
