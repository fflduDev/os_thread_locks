/*

This program demonstrates a spin lock — both threads repeatedly check (while (flag != id)) until it’s their turn to access the shared variable s.

It shows how busy waiting works: a thread “spins” in a loop instead of sleeping or blocking, wasting CPU cycles but enforcing mutual exclusion without explicit locking primitives.

*/



#include <pthread.h>
#include <stdio.h>
static int s = 0;
static int flag = 0;
void *CountUp(void *id){
	for (int i=0;i< 20000;i=i+1){
	
		while (flag != (int)id){
			printf("in while..\n");
		};
		s= s+1;
		printf("updating flag..");
		flag = (flag+1)%2;
		printf("flag value: %d\n", flag);
	}
}

int main(){
	pthread_t thread0, thread1;
	printf("creating thread 1");
	pthread_create(&thread0, NULL, CountUp, (void*) 0);
	printf("creating thread 2");
	pthread_create(&thread1, NULL, CountUp, (void*) 1);
	printf("joining thread 1");
	pthread_join(thread0, NULL);
	printf("joining thread 2\n");
	pthread_join(thread1, NULL);
	printf("final result: %d\n",s);
	return 0;
}
