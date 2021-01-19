// ANANYA KANSAL 2019458

#include<errno.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>

pthread_t thread_id[2000];
bool val;

typedef struct struct_semaphore {
  pthread_mutex_t mutex;
  pthread_cond_t cond_t;
  bool resources;
  ssize_t cnt;
} my_semaphore;

my_semaphore forks[2000];          // assuming no of philosphers are same as the forks and in the range 2 to 2000
my_semaphore sauce[2];

int sem_init(my_semaphore *s, int pshared, int input) {
  s->resources=false;
   s->cnt = input;
  int check1=1; int check2=1;
  if (pshared==0) {
  check1=pthread_mutex_init(&s->mutex, NULL);
  check2=pthread_cond_init(&s->cond_t, NULL);
 // printf("%d\n",check1);
 // printf("%d\n",check2);
  return 0;
  }
  else{
  	perror("initialisation");
  	  	return-1;
  }
}
void print(my_semaphore *semaphore)
{
	printf("%ld\n",semaphore->cnt);
}

int signal_post(my_semaphore *s) 
{
  int a =0; int b=0;
  a=pthread_mutex_lock(&s->mutex);
  if(a==0){
  	//printf("%s\n","success lock" );
  }
  s->cnt++;
  b= pthread_cond_signal(&s->cond_t);
  if(b==0){
  	//printf("%s\n","success signal" );
  }
    a=pthread_mutex_unlock(&s->mutex);
  return 0;
}


 int wait(my_semaphore *semaphore) {
 int check1=1;
 int check2=1;
 int check3=1;
  check1=pthread_mutex_lock(&semaphore->mutex);
  if(semaphore->cnt >= 1){
  	semaphore->cnt--;
  	check2=pthread_mutex_unlock(&semaphore->mutex);
 // printf("%d\n",check2);
  	return 0;	
  }	
 while(semaphore->cnt==0){
  		pthread_cond_wait(&semaphore->cond_t, &semaphore->mutex);
  		check2=-1;
  	}
  	semaphore->cnt=semaphore->cnt-1;
  	check3=pthread_mutex_unlock(&semaphore->mutex);
    //printf("%d\n",check3);
  	return 1;
  }

int wait_for_resource(int a){
	int i=0;
	while(i<10){
		a=a+i;
		i++;
	}
	return a;
}

int input=0;
my_semaphore dining;

void * philosopher(void * num)
{

	int phil_number=*(int *)num;
	wait(&dining);
	int res=0;
	int var;
	wait(&sauce[0]); wait(&sauce[1]);
	wait(&forks[phil_number]);
	wait(&forks[(phil_number+1)%input]);
	//printf("%s\n","bowls & forks picked");
	printf("\nPhilosopher %d is eating, with forks %d and %d",phil_number+1,phil_number+1,((phil_number+1)%input)+1);
    sauce->resources=true;
	sleep(2);
	signal_post(&forks[phil_number]);
	signal_post(&forks[(phil_number+1)%input]);
	signal_post(&sauce[0]);
	signal_post(&sauce[1]);
	sauce->resources=false;
	signal_post(&dining);
	pthread_exit(NULL);
}



int main()
{
	int loop=0;
	int strength;
	bool a=true;
	bool start=false;
	printf("enter no of philosophers: ");
	int num=0;
	scanf("%d",&input); //less than 2000;
	int phil[input];
	int in=0;
	strength=input-1;
	sem_init(&dining,0,strength);
	sem_init(&sauce[0],0,1);
	sem_init(&sauce[1],0,1);
	while(num<input)
	{
		sem_init(&forks[num],0,1);
		num++;
	}

	while(in<input)
	{
		phil[in]=in;
		in++;
	}

	while(loop==0)
	{	
		if(a){ 
		for(int x=0;x<input;x++){
			int a1=0;
			a1=pthread_create(&thread_id[x],NULL,philosopher,&phil[x]);
			if(a1!=0){
				printf("%s\n","error1");
			}
		}

		for(int y=0;y<input;y++)
		{
			int b1=0;
			b1=pthread_join(thread_id[y],NULL);
			if(b1!=0){
				printf("%s\n","error2");
			}
		}
	}
	else{
		printf("%s\n","error in infinite loop");
		break;
	}
	}
	printf("\n");
	return 0;
}
