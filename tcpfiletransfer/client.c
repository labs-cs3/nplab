#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
 
#define SERV_PORT 35000
#define MAXLINE 4096
 
void err_sys(const char *x) {
    perror(x);
    exit(1);
}
 
int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    ssize_t n;
 
    if (argc != 3) {
        fprintf(stderr, "usage: %s <IPaddress> <filename>\n", argv[0]);
        exit(1);
    }
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) err_sys("socket error");
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) err_sys("inet_pton error");
 
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");
 
    FILE *fp = fopen(argv[2], "rb");
    if (fp == NULL) err_sys("fopen error");
 
    while ((n = fread(buf, sizeof(char), MAXLINE, fp)) > 0) {
        if (write(sockfd, buf, n) != n) err_sys("write error");
    }
 
    if (ferror(fp)) err_sys("fread error");
 
    fclose(fp);


    close(sockfd);
 
   return 0;
   }
