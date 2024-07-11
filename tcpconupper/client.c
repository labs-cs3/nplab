#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<stdio.h>
 
#define MAXLINE 4096
#define SERV_PORT 35000
 
void str_cli(FILE *fp, int sockfd) {
    char sendline[MAXLINE], recvline[MAXLINE];
 
    while (fgets(sendline, MAXLINE, fp) != NULL) {
        write(sockfd, sendline, strlen(sendline));
 
        if (read(sockfd, recvline, MAXLINE) == 0) {
            perror("str_cli: server terminated prematurely");
            exit(1);
        }
 
        fputs(recvline, stdout);
    }
}
 
int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;
 
    if (argc != 2) {
        fprintf(stderr, "usage: %s <IPaddress>\n", argv[0]);
        exit(1);
    }
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
 
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        perror("inet_pton error");
        exit(1);
    }
 
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        exit(1);
    }
 
    str_cli(stdin, sockfd);
 
    close(sockfd);
    
    return 0;
}
