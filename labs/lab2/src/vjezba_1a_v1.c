#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


static pthread_mutex_t lock;
static pthread_cond_t cond;
static int turn = 3;

/* Tijelo niti 1. */

void* print(void *pParam)
{
    int i;
    int id = *(int*) pParam;

    for (i = 0; i < 100; i++)
    {
        while (1)
        {
            pthread_mutex_lock(&lock);

            if (id == turn)
            {
                printf("%d", id);
                fflush(stdout);

                turn = (turn - 1 >= 1) ? turn - 1 : 3;

                pthread_mutex_unlock(&lock);
                break;
            }

            pthread_mutex_unlock(&lock);
        }
    }

    return NULL;
}

// rjesenje iznad ima manu u smislu da imamo pojavu "busy waiting-a". To znaci da iako je recimo turn = 3, a tread1 moze da zakljuca
//muteks vise puta uzastopno sto trosi resurse i vrijeme. Bolja metoda sinhronizacije bi bila pomocu uslovnih promjenljivih/muteksa
//koje imaju i funkcije za wait stanje. No ovo nismo do sad jos radili, vec je ovo bio predmet samostalnog istrazivanja, te ostavljam
//ovo rjesenje u komentaru

// void* print(void *pParam)
// {
//     int i;
//     int id = *(int*) pParam;

//     for (i = 0; i < 100; i++)
//     {
//         pthread_mutex_lock(&lock);
//         while (id != turn) {
//             pthread_cond_wait(&cond, &lock);
//         }
//                 printf("%d", id);
//                 fflush(stdout);

//                 turn = (turn - 1 >= 1) ? turn - 1 : 3;

//                 pthread_cond_broadcast(&cond);
//                 pthread_mutex_unlock(&lock);

//         }

//     return NULL;
// }


int main (void)
{
    pthread_t t1, t2, t3;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    /* Formiranje niti. */
    pthread_create(&t1, NULL, print, &id1);
    pthread_create(&t2, NULL, print, &id2);
    pthread_create(&t3, NULL, print, &id3);

    getchar();

    return 0;
}

//ovo rjesenje ima manu u smislu da imamo pojavu "busy waiting-a". To znaci da iako je recimo turn = 3, a tread1 moze da zakljuca
//muteks vise puta uzastopno sto trosi resurse i vrijeme. Bolja metoda sinhronizacije bi bila pomocu uslovnih promjenljivih/muteksa
//koje imaju i funkcije za wait stanje. No ovo nismo do sad jos radili, vec je ovo bio predmet samostalnog istrazivanja, te nisam
//implementirao rjesenje na ovaj nacin.