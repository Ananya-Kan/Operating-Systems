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

my_semaphore forks[2000];
my_semaphore sauce[2];

int sem_init(my_semaphore *s, int pshared, int input) {
  s->resources=false;
  int check1=1; int check2=1;
  if (pshared==0) {
  check1=pthread_mutex_init(&s->mutex, NULL);
  check2=pthread_cond_init(&s->cond_t, NULL);
 // printf("%d\n",check1);
 // printf("%d\n",check2);
    s->cnt = input;
  return 0;
  }
  else{
  	return-1;
  	perror("initialisation");
  }
}


int signal_post(my_semaphore *s) 
{
  int a =0; int b=0;
  a=pthread_mutex_trylock(&s->mutex);
  if(a==0){
  	//printf("%s\n","success lock" );
  }
  s->cnt++;
  b= pthread_cond_signal(&s->cond_t);
  if(b==0){
  	//printf("%s\n","success signal" );
  }
  pthread_mutex_unlock(&s->mutex);
  return 0;
}
void print(my_semaphore *semaphore)
{
	printf("%ld\n",semaphore->cnt);
}

 int wait(my_semaphore *s) {
  if(s->cnt >= 1){
  	pthread_mutex_trylock(&s->mutex);
  	s->cnt--;
  	pthread_mutex_unlock(&s->mutex);
  	return 0;	
  }	
  else if(s->cnt == 0){
  	return 1;
  }
  else
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

int k=0;

void * philosopher(void * num)
{
	int phil_number=*(int *)num;
	int res=0;
	int var;
	while((wait(&sauce[0])==1 && wait(&sauce[1])==1 && wait(&forks[phil_number])==1 && (wait(&forks[(phil_number+1)%k])==1))){
		var=wait_for_resource(res);
		printf("%s\n","bowls picked");
		printf("%s\n","forks picked");
		sauce->resources=true;
	}
	sauce->resources=true;
	printf("\nPhilosopher %d is eating, with forks %d and %d",phil_number+1,phil_number+1,((phil_number+1)%k)+1);
	sleep(2);
	signal_post(&sauce[0]);
	signal_post(&sauce[1]);
	signal_post(&forks[phil_number]);
	signal_post(&forks[(phil_number+1)%k]+1);
	sauce->resources=false;
	pthread_exit(NULL);
}

int main()
{
	int loop=0;
	bool a=true;
	bool start=false;
	printf("enter no of philosophers: ");
	int num=0;
	scanf("%d",&k);
	int phil[k];
	int in=0;
	sem_init(&sauce[0],0,1);
	sem_init(&sauce[1],0,1);
	while(num<k)
	{
		sem_init(&forks[num],0,1);
		num++;
	}

	while(in<k)
	{
		phil[in]=in;
		in++;
	}

	while(loop==0)
	{	
		if(a){ 
		for(int x=0;x<k;x++){
			int a1=0;
			a1=pthread_create(&thread_id[x],NULL,philosopher,&phil[x]);
			if(a1!=0){
				printf("%s\n","error1");
			}
		}

		for(int y=0;y<k;y++)
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
