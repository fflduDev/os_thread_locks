#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static int s = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *CountUp(void *id){
    for (int i=0; i<20000; i++){
        pthread_mutex_lock(&lock);
        int temp = s;
        usleep(1);
        s = temp + 1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t thread0, thread1;
    pthread_create(&thread0, NULL, CountUp, (void*)0);
    pthread_create(&thread1, NULL, CountUp, (void*)1);
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    printf("final result: %d\n", s);
    return 0;
}