// Dinning philosophers assignment
// Philosophers = current processes; chopsticks = shared resources

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * thread_function(void * arg);

int num_threads;	// numbers of philosopher
int times_to_eat;  	// total time the philosopher eat, then exit
pthread_mutex_t chop_sticks[32];	
char start = 0;

int main(int argc, char * argv[]){
   if (argc != 3){
      printf("invalid args\n");
      exit(1);
   }
   
   times_to_eat = atoi(argv[1]);	// atoi() convert string to integer
   num_threads = atoi(argv[2]);
   int philo_id[32];
   
   pthread_t thread_id[num_threads];
   int times_eaten[num_threads];	// keep track of times the 						philosophers has eaten
   int i, j;
   printf("About to init mutex\n");
   for(i=0; i < num_threads; i++){
      //chop_stick[i] = PTHREAD_MUTEX_INITIALIZER;
      pthread_mutex_init(&chop_sticks[i], NULL);
      continue;
   }
   
   for(i=0; i < num_threads; i++){
      philo_id[i] = i;
      pthread_create(&thread_id[i], NULL, &thread_function, &philo_id[i]);
   }
   
   start = 1;
   
   for(j=0; j < num_threads; j++){
      pthread_join(thread_id[j], NULL);
   }
}

void * thread_function(void * arg){
   while(start==0){
       ;
   }
   
   int philo_id = *((int *) arg);
   printf("Thread %d starting...\n", philo_id);
   int times = 0;
} 
   
        
