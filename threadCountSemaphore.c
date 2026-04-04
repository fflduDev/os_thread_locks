#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
static int s = 0;
sem_t count_semaphore;
void *CountUp(void *id){
	for (int i=0;i< 20000;i=i+1){
		sem_wait(&count_semaphore);
		s= s+1;
		sem_post(&count_semaphore);
	}
}

int main(){
//	sem_init(&count_semaphore, 0,3);
	sem_init(&count_semaphore, 0,1);

	pthread_t thread0, thread1;
	pthread_create(&thread0, NULL, CountUp, (void*) 0);
	pthread_create(&thread1, NULL, CountUp, (void*) 1);
	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);
	printf("%d\n",s);
	return 0;
}

