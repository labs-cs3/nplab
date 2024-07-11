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
 
int main() {
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    char buf[MAXLINE];
    ssize_t n;
 
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) err_sys("socket error");
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
 
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("bind error");
 
    if (listen(listenfd, 10) < 0) err_sys("listen error");
 
    clilen = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
    if (connfd < 0) err_sys("accept error");
 
    FILE *fp = fopen("received_file", "wb");
    if (fp == NULL) err_sys("fopen error");
 
    while ((n = read(connfd, buf, MAXLINE)) > 0) {
        if (fwrite(buf, sizeof(char), n, fp) != n) err_sys("fwrite error");
    }
 
    if (n < 0) err_sys("read error");
 
    fclose(fp);
    close(connfd);
    close(listenfd);
 
    return 0;
}


