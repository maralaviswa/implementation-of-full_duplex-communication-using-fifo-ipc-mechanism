#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
int main()
{
        int fd,fd1,i=0,pid;
        char arr[20],ch;
        if(mkfifo("file1",0666)==-1 && errno!=EEXIST)
        {
                perror("mkfifo");
                exit(0);
        }
        if(mkfifo("file2",0666)==-1 && errno!=EEXIST)
        {
                perror("mkfifo1");
                exit(0);
        }
        printf("file created successfully\n");
        pid=fork();
        if(pid==-1)
        {
                perror("fork");
                exit(0);
        }
        if(pid==0)
        {
          fd=open("file1",O_RDONLY);
            if(fd==-1)
            {
                    perror("open");
                    exit(0);
            }
            printf("file opened succcessfully\n");
            do
            {
                    i=0;
                    while(read(fd,&ch,1)==1)
                    {
                            arr[i++]=ch;
                            if(ch=='\0')
                                    break;
                    }
                    printf("read string %s\n",arr);
            }while(strcmp(arr,"quit")!=0);
          }
        else
        {
            fd1=open("file2",O_WRONLY);
             if(fd1==-1)
             {
                perror("open1");
                exit(0);
             }
             do
             {
                printf("enter the string\n");
                fgets(arr,20,stdin);
                arr[strlen(arr)-1]=0;
                write(fd1,arr,strlen(arr)+1);
             }while(strcmp(arr,"quit")!=0);
            unlink("file1");
            unlink("file2");
         }
}