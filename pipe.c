#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(void)
{
 int pid,n,fd[2];
 char buff[200];
 pipe(fd);
 pid=fork();
 if(pid == 0)
 {
 close(fd[1]);
 n=read(fd[0],buff,sizeof(buff));
 buff[n]='\0';
 printf("%s",buff);
 }
 else if(pid>0)
 {
 close(fd[0]);
 write(fd[1],"hello",5);
 }
 return(0);
}