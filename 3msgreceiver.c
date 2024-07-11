#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#define SIZE 40
void main()
{
        int mfd,mfd2,mfd3;
        struct
        {
                long mtype;
                char mtext[6];
        }
        s1,s2,s3;
        if((mfd=msgget(1000,0))==-1)
        {
                perror("msgget");
                exit(1);
        }
        if(msgrcv(mfd,&s1,SIZE,0,IPC_NOWAIT|MSG_NOERROR)==-1)
        {
                perror("msgrcv");
                exit(1);
        }
        printf("Message from client is :%s\n",s1.mtext);
        if((mfd2=msgget(1000,0))==-1)
        {
                perror("msgget");
                exit(1);
        }
        if(msgrcv(mfd2,&s2,SIZE,0,IPC_NOWAIT|MSG_NOERROR)==-1)
        {
                perror("msgrcv");
                exit(1);
        }
        printf("Message from client is :%s\n",s2.mtext);
        if((mfd3=msgget(1000,0))==-1)
        {
                perror("msgget");
                exit(1);
        }
        if(msgrcv(mfd3,&s3,SIZE,0,IPC_NOWAIT|MSG_NOERROR)==-1)
        {
                perror("msgrcv");
                exit(1);
        }
        printf("Message from sender is :%s\n",s3.mtext);
}
