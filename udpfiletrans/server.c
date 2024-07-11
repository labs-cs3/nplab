#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define SERV_PORT 30000
#define MAXLINE 4096
 
void err_sys(const char *x) {
    perror(x);
    exit(1);
}
 
int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buf[MAXLINE];
    socklen_t clilen;
    ssize_t n;
 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) err_sys("socket error");
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
 
    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("bind error");
 
    FILE *fp = fopen("received_file", "wb");
    if (fp == NULL) err_sys("fopen error");
 
    clilen = sizeof(cliaddr);
    printf("Server is running and waiting for data...\n");
 
    while ((n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) &cliaddr, &clilen)) > 0) {
        printf("Received %zd bytes\n", n);
        if (fwrite(buf, sizeof(char), n, fp) != n) {
            err_sys("fwrite error");
        }
        fflush(fp); // Ensure data is written to the file immediately
    }
 
    if (n < 0) err_sys("recvfrom error");
 
    fclose(fp);
    close(sockfd); 
    return 0;
}
