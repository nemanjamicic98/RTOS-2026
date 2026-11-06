#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t cs_mutex;

static int na_redu=3;

void* print (void *pParam)
{
	int id = *(int*)pParam;
	int i = 0;

	while (i < 100)
    {
        pthread_mutex_lock(&cs_mutex);

        if (na_redu == id)
        {
            printf("%d", id);
            fflush(stdout);

            na_redu = (id == 1) ? 3 : id - 1;
            i++;
        }
		
		pthread_mutex_unlock(&cs_mutex);
    }

    return 0;
}

int main (void)
{
    pthread_t hPrint1;
    pthread_t hPrint2;
    pthread_t hPrint3;

    int id1=1;
	int id2=2;
	int id3=3; 
	
	pthread_mutex_init(&cs_mutex, NULL);
	
    pthread_create(&hPrint1, NULL, print, (void*)&id1);
    pthread_create(&hPrint2, NULL, print, (void*)&id2);
    pthread_create(&hPrint3, NULL, print, (void*)&id3);

    getchar();
	
	pthread_mutex_destroy(&cs_mutex);

    return 0;
}
