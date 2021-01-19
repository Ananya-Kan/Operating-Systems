/* Name: Ananya Kansal
   Roll_Number: 2019458 */
   
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <sysexits.h>
#include <pthread.h>
int a=10;
void *func(void *vargp)			// child thread function
{	while(a>-90)
	{
		printf("%d \n",a);
		a=a-1;
	}
	printf("The thread ends here and the value of a is");
	printf("%d \n",a);
	
}
void main()
{
	//int a=10;
	pthread_t f;
	pthread_create(&f,NULL,func,NULL);
	pthread_join(f,NULL);
	while(a<100)
	{
		printf("%d \n",a);
		a=a+1;
	}
	printf("%d \n",a);

	//printf("%d \n",a);
}
