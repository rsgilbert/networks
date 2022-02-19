#include "../lib/unp.h"
#include "../lib/error.c"

int 
main()
{
    struct sockaddr_in servaddr;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        err_sys("socket error");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    // int r = htons(13);
    int r = servaddr.sin_port;
    printf("port is %d\n", r);
    printf("server addr is %s\n", &servaddr.sin_addr);

    int in = inet_pton(AF_INET, "0.2.3.4", &servaddr.sin_addr);
    printf("AF_INET is %d, sinaddr is %d, port is %d, in is %d\n", AF_INET, &servaddr.sin_addr, &servaddr.sin_port, in);

 printf("server addr is %s\n", &servaddr.sin_addr);

    printf("length %d\n", sizeof(servaddr));

}