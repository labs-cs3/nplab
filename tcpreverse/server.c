#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<errno.h>

#define SERV_PORT 30000
#define MAXLINE 4096
 
void str_reverse(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}
 
void str_echo(int sockfd) {
    ssize_t n;
    char buf[MAXLINE];
    again:
    while ((n = read(sockfd, buf, MAXLINE)) > 0) {
        buf[n] = '\0';
        str_reverse(buf);
        write(sockfd, buf, n);
    }
    if (n < 0 && errno == EINTR);
    else if (n < 0)
        perror("str_echo: read error");
}
 
int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
 
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
 
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listenfd, 10);
 
    for (;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        str_echo(connfd);
        close(connfd);
    }
 
    return 0;
}
