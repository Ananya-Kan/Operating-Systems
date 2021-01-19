/* Name: Ananya Kansal
   Roll_Number: 2019458 */

#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
    long check;
    int input;
    scanf("%d",&input);
    check = syscall(440, input, "/home/ananya/Desktop/my_file");

    if(check >= 0)
    {
        printf("System call is functional. Run dmesg.\n");
    }

    else
    {
        perror(" System call failed.");
    }

    return 0;
}


