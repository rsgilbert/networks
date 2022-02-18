#include "../lib/unp.h"
#include "../lib/error.c"

/**
 * @brief 
 * 
 * @param argc IP of the daytime server. To see list of available time servers, visit: https://tf.nist.gov/tf-cgi/servers.cgi
 *          An example with working IP is: ./a.out 129.6.15.28
 * @param argv 
 * @return int 
 */

int 
main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if(argc != 2)
        err_quit("usage: a.out <IPaddress>");

    // Create TCP socket
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 1)) < 0)
        err_sys("socket error");
    
    // Specify server's IP address and port

    // set entire structure to 0
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); /* daytime server */
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) 
        err_quit("inet_pton error for %s", argv[1]);

    if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) 
        err_sys("connect error");

    while( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0; /* null terminate */
        if(fputs(recvline, stdout) == EOF) 
            err_sys("fputs error");
    }

    if(n < 0)
        err_sys("read error");

    exit(0);
}