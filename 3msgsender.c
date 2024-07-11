#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<stdlib.h>
#define SIZE 2000
void main( )
{
        int mfd,mfd2,mfd3;
        struct
        {
                double mtype;
                char mtext[2000];
        }
        s1,s2,s3;
        if((mfd=msgget(1000,IPC_CREAT|0666))==-1)
        {
                perror("msgget:");
                exit(1);
        }
        s1.mtype=1;
        sprintf(s1.mtext,"%s","Hi friends... My name is message1");
        if(msgsnd(mfd,&s1,1000,0)==-1)
        {
                perror("msgsnd");
                exit(1);
        }
        if((mfd2=msgget(1000,IPC_CREAT|0666))==-1)
        {
                perror("msgget:");
                exit(1);
        }
        s2.mtype=1;
        sprintf(s2.mtext,"%s","Hi friends... My name is message2");
        if(msgsnd(mfd2,&s2,1000,0)==-1)
        {
                perror("msgsnd");
                exit(1);
        }
        if((mfd3=msgget(1000,IPC_CREAT|0666))==-1)
        {
                perror("msgget:");
                exit(1);
        }
        s3.mtype=1;
        sprintf(s3.mtext,"%s","Hi friends... My name is message3");
        if(msgsnd(mfd3,&s3,1000,0)==-1)
        {
                perror("msgsnd");
                exit(1);
        }
        printf("Your message has been sent successfully...\n");
        printf("Please visit another (receiver's) terminal...\n");
        printf("Thank you.... For using LINUX");
}
