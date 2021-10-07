// Dinning philosophers assignment
// Philosophers = current processes; chopsticks = shared resources
// by Trinh Vo - csc 345

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * thread_function(void * arg);
int eat(int philo_id, int times);

int num_threads;	// numbers of philosopher
int times_to_eat;  	// total time the philosopher eat, then exit
pthread_mutex_t chop_sticks[32];	
char start = 0;

int chopsticks[32]; // an array to keep track of which chopstick is 	avalable to pick up

int main(int argc, char * argv[]){
   if (argc != 3){
      printf("invalid args\n");
      exit(1);
   }
   
   times_to_eat = atoi(argv[1]);	// atoi() convert string to integer
   num_threads = atoi(argv[2]);
   int philo_id[32];
   
   pthread_t thread_id[num_threads];
   int times_eaten[num_threads];	/* keep track of times the philosophers has eaten */
   
   int i, j;
   
   // if chopsticks[i] = -1, chopstick i is available to pick up
   for (i=0; i < num_threads; i++)
   	chopsticks[i] = -1;
   	
   	
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
   
   
   while (times < times_to_eat){
      // a thread will stop for a random amount of time, the other threads still in process.
      int a = rand() % 1;
      sleep(a);
      
      // lock the critical section (pick up the chopstick)
      pthread_mutex_lock(&chop_sticks[philo_id]);
          times = eat(philo_id, times);   
      pthread_mutex_unlock(&chop_sticks[philo_id]);
   }
}
/////////////////////////////////////////////////////////
// function for pick up chopsticks:
int eat(int philo_id, int times)
{

   // even philosophers (pick up the right chopstick first):
   if (philo_id % 2 == 0)
   {	
	// if the last philosopher is even
	if (philo_id == num_threads - 1)
	{	
	   // if the right chopstick is available, pick it up.
	   if (chopsticks[0] == -1)
		chopsticks[0] = philo_id;
	   // if he already picked up the right chopstick,
	   // check if the left chopstick is available.
	   else if (chopsticks[0] == philo_id)
	   {
		if (chopsticks[philo_id] == -1)
		{
		   chopsticks[philo_id] = philo_id;
		   printf("P%d is eating...\n", philo_id);
		   //put the chopsticks down
		   chopsticks[philo_id] = -1;
		   chopsticks[0] = -1;
		   times++;
		}
		else // if the left chopstick is not available
		   printf("P%d is thinking...\n", philo_id);
					
	   }
	   else // if the right chopstick is not available
		printf("P%d is thinking...\n", philo_id);
	}
	
	// For the rest of even philosophers (not last one):
	else
	{
	   // if the right chopstick is available, pick it up.
	   if (chopsticks[philo_id + 1] == -1)
	   	chopsticks[philo_id + 1] = philo_id;
	   // if he already picked up the right chopstick,
	   // check if the left chopstick is available.
	   else if (chopsticks[philo_id + 1] == philo_id)
	   {
	   	if (chopsticks[philo_id] == -1)
	   	{
		   chopsticks[philo_id] = philo_id;
		   printf("P%d is eating...\n", philo_id);
		   //put the chopsticks down
		   chopsticks[philo_id] = -1;
		   chopsticks[philo_id + 1] = -1;
		   times++;
	   	}
	   	else // if the left chopstick is not available
		   printf("P%d is thinking...\n", philo_id);		
	   }
	   else // if the right chopstick is not available
	   	printf("P%d is thinking...\n", philo_id);
	}
   }
   //////////////////////////////////////////////////////////////
   // odd philosophers (pick up the left chopstick first)
   else
   {
	//if the last philosopher is odd
	if (philo_id == num_threads - 1)
	{
	   // if the left chopstick is available, pick it up.
	   if (chopsticks[philo_id] == -1)
		chopsticks[philo_id] = philo_id;
	   // if he already picked up the left chopstick,
	   // check if the right chopstick is available.
	   else if (chopsticks[philo_id] == philo_id)
	   {
		if (chopsticks[0] == -1)
		{
		   chopsticks[0] = philo_id;
		   printf("P%d is eating...\n", philo_id);
		   //put the chopsticks down
		   chopsticks[philo_id] = -1;
		   chopsticks[0] = -1;
		   times++;
		}
		else // if the right chopstick is not available
		   printf("P%d is thinking...\n", philo_id);		
	   }
	   else // if the left chopstick is not available
		printf("P%d is thinking...\n", philo_id);
	}
	
	// For the rest of odd philosophers (not last one)
	else
	{
	   // if the left chopstick is available, pick it up.
	   if (chopsticks[philo_id] == -1)
		chopsticks[philo_id] = philo_id;
	   // if he already picked up the left chopstick,
	   // check if the right chopstick is available.
	   else if (chopsticks[philo_id] == philo_id)
	   {
	   	if (chopsticks[philo_id + 1] == -1)
	   	{
		   chopsticks[philo_id + 1] = philo_id;
		   printf("P%d is eating...\n", philo_id);
		   //put the chopsticks down
		   chopsticks[philo_id] = -1;
		   chopsticks[philo_id + 1] = -1;
		   times++;
	   	}
	  	else // if the right chopstick is not available
		   printf("P%d is thinking...\n", philo_id);		
	   }
	   else // if the left chopstick is not available
	   	printf("P%d is thinking...\n", philo_id);
	}
   }	
   return (times);
}