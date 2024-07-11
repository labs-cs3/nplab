#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define SERV_PORT 35000
#define MAXLINE 4096
 
int main(int argc, char **argv) {
    int sockfd;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    socklen_t servlen = sizeof(servaddr);
    ssize_t n;
 
    if (argc != 2) {
        fprintf(stderr, "usage: %s <IPaddress>\n", argv[0]);
        exit(1);
    }
 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
 
    while (fgets(sendline, MAXLINE, stdin) != NULL) {
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *) &servaddr, servlen);
 
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = '\0';
 
        fputs(recvline, stdout);
    }
 
    close(sockfd);
    return 0;
}
