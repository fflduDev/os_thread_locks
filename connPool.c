#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 8
#define NUM_CONNECTIONS 3

sem_t pool;

void *handleRequest(void *id){
    printf("Thread %d waiting for connection...\n", (int)id);
    sem_wait(&pool);
    printf("Thread %d got connection, working...\n", (int)id);
    sleep(1);  // simulate db work
    printf("Thread %d releasing connection\n", (int)id);
    sem_post(&pool);
    return NULL;
}

int main(){
    sem_init(&pool, 0, NUM_CONNECTIONS);

    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, handleRequest, (void*)i);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&pool);
    return 0;
}