/* Name: Ananya Kansal
   Roll_Number: 2019458 */


#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/types.h>
#include<sys/wait.h> 
#include <sysexits.h>
int a=10;
int main()
{
	
	pid_t f=fork();

	if(f<0)
	{
		printf("child process couldn't be created");
	}
	else if(f==0)				// child process created
	{
		while(a>-90)
		{
			printf("%d \n",a);
			a=a-1;
		}
		printf("%d \n",a);
		exit(0);
	}
	else
	{
		waitpid(-1,NULL,0);       //parent process waiting 
		while(a<100)
		{
			printf("%d \n",a);
			a=a+1;
		}
		printf("%d \n",a);
	}
	//printf("%d \n",a);
	return 0;
}
