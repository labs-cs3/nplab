#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define SERV_PORT 35000
#define MAXLINE 4096
 
void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}
 
int main() {
    int sockfd;
    char buf[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    ssize_t n;
 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
 
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    for (;;) {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) &cliaddr, &len);
        buf[n] = '\0';
 
        reverse_string(buf);
 
        sendto(sockfd, buf, n, 0, (struct sockaddr *) &cliaddr, len);
    }
 
    return 0;
}

