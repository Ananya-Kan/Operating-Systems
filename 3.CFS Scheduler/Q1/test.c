/* Name: Ananya Kansal
   Roll_Number: 2019458 */
   
 #include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>



int main() {
	
	printf("enter value for rtnice: ");
	long input=0;
	scanf("%ld",&input);			// assuming input will always be a long int otherwise it takes a null value
		
	long pid = fork();         		 // creating a child process 
	
	clock_t time;
	struct timeval clock1,clock2;
	
	

	if(pid < 0) {
		perror("fork failed");			// negative value returned for fork system call if failed	
		return -1;
	}
	else if(pid == 0) {

		long ret = syscall(440, getpid(), input);			// executing syscall

		if(ret != 0) {
			perror("syscall failed");
			return -1;
		}
		 gettimeofday(&clock1, NULL);	//time=clock();

		for(long long int i=0; i<100000000; i++); 

		gettimeofday(&clock2, NULL); //time=clock()-time;	
		//time=time/CLOCKS_PER_SEC;
		printf("Child Process with soft time requirement : %lf\n", (double) (clock2.tv_usec-clock1.tv_usec)/1000 + (double) (clock2.tv_sec-clock1.tv_sec)*1000);
	 											// waiting for child process to end
	}
	else {	
			
	 	gettimeofday(&clock1, NULL);	//time=clock();						// determines processor time

		for(long long int i=0; i<1000000; i++); 		// busy wait

		gettimeofday(&clock2, NULL);			//time=clock()-time;											// difference between start and stop time
		printf("Process without rtnice value : %lf\n", (double) (clock2.tv_usec-clock1.tv_usec)/1000 + (double) (clock2.tv_sec-clock1.tv_sec)*1000);
		
	
		wait(NULL);
	}
	return 0;

}
