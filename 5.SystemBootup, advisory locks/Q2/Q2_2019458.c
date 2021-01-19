#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/file.h>

FILE *ptr = NULL;
int file_desc;
char name_file[100];
char writeData[2000],readData[2000];

void printer(){
    printf("-------closed-----, Come back again----\n");
    printf("-------text editor terminated----------\n");
}
void Write1(){

        printf("New file : %s created\n", name_file);
        ptr = fopen(name_file, "w");
        file_desc = fileno(ptr);
        if(file_desc==-1)
        {
            perror("error!!");                            // error handling
        }
        if (flock(file_desc, LOCK_EX | LOCK_NB) == -1)
        {
            printf("----warning---file is being used somewhere else----\n");
             printf("----RACE CONDITIONS POSSIBLE----\n");                        // warning 
        }
        printf("write your data: ");
        scanf(" %[^\n]*c", writeData);
        fputs(writeData, ptr);
        fclose(ptr);
        printf("----file saved---\n-");
}

void Write()
{
        int choice;
        printf("%s\n","choose 1 to append, 2 for overwrite, 3 for Exit");
        scanf("%d", &choice);
       if(choice==1){
        ptr = fopen(name_file, "a");
        file_desc = fileno(ptr);

        if(file_desc==-1)
        {
            perror("error!!");
        }

        if (flock(file_desc, LOCK_EX | LOCK_NB) == -1)
        {
             
             // if(errno==EWOULDBLOCK)
             // {
             //    printf("----warning---file is being used somewhere else----\n");
             //    printf("----RACE CONDITIONS POSSIBLE----\n");
             // }
             printf("----warning---file is being used somewhere else----\n");
             printf("----RACE CONDITIONS POSSIBLE----\n");
        }
            printf("Data to be appended: ");
            scanf(" %[^\n]*c", writeData);
            fputs(writeData, ptr);
            printf("------appended-------\n");
            fclose(ptr);
    }
    else if(choice==2){
        ptr = fopen(name_file, "w");
        file_desc = fileno(ptr);
        if(file_desc==-1)
        {
            perror("error!!");
        }

        if (flock(file_desc, LOCK_EX | LOCK_NB) == -1)
        {
             // if(errno==EWOULDBLOCK)
             // {
             //    printf("----warning---file is being used somewhere else----\n");
             //    printf("----RACE CONDITIONS POSSIBLE----\n");
             // // }
             
        }
            printf("type in your data: ");
            scanf(" %[^\n]*c", writeData);
            fputs(writeData, ptr);
            printf("------added-------\n");
            fclose(ptr);
    }

    else
    {
        printf("-----exited-------");
        return;
    }
    
}


int main(void)
{
    int option;
    printf("INPUT YOUR CHOICE:   \n");
    printf("choose 1 to Edit a text file\n");
    printf("choose 2 Exit\n");
    scanf("%d", &option);
    int a=0;
    if (option == 2)
        {
           printer();
           return -1;
        }
    else if (option == 1)
        {
      printf("INPUT FILE NAME: \n");
      scanf(" %[^\n]*c", name_file);
      ptr = fopen(name_file, "r");
      if (ptr == NULL)
    {
        a=1;
        printf("FILE IS NOT AVAILABLE!\n");
    }
    else
    {
        char ch = fgetc(ptr);
        printf("Data in file: ");
        while(ch!=EOF){
            printf("%c",ch);
            ch= fgetc(ptr);
        }
        printf("\n");
        printf("\n");
        fclose(ptr);
    }
    if(a==1){
        Write1();
    }
    else{
    Write(); 
    }
        }
    else 
        {
            printf("----------bad input---------");
            printer();
        }
    return 0;
}