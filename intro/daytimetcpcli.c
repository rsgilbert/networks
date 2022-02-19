#include "../lib/unp.h"
#include "../lib/error.c"

/**
 * @brief 
 * 
 * @param argc IP of the daytime server eg 132.163.97.2. To see list of available time servers, visit: https://tf.nist.gov/tf-cgi/servers.cgi
 *          An example with working IP is: ./a.out 129.6.15.28 . Or you can do: gcc daytimetcpcli.c && ./a.out 132.163.97.2 
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
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");
    
    // Specify server's IP address and port

    // set entire structure to 0
    bzero(&servaddr, sizeof(servaddr));

    // Set address family
    servaddr.sin_family = AF_INET;
    // 13 is the well known port of daytime server on any TCP/IP host that supports this service.
    // htons stands for host to network short
    servaddr.sin_port = htons(13); /* daytime server */
    
    
    // Set the IP address to the first value specified as the cli argument ( argv[1] ) 
    // The IP address and port must be in specific formats.
    // inet_pton stands for presentation to numeric. Converts string ip eg 1.2.3.4 into proper format
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) 
        err_quit("inet_pton error for %s", argv[1]);

    // Establish connection with server
    if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) 
        err_sys("connect error");

    // Read and display server's reply
    // if read returns 0 it means the other end closed the connection.
    // if read returns a value less than 0, it means an error occurred.
    // TCP itself provides no record markers so an application must determine what
    // constitutes the end of a record, in this case the end of the record is being 
    // denoted by the server closing the connection (when read returns 0).
    while( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0; /* null terminate */
        printf("n is %d , recvline is %s, MAXLINE is %d\n", n, recvline, MAXLINE);
        if(fputs(recvline, stdout) == EOF) 
            err_sys("fputs error");
    }

    if(n < 0)
        err_sys("read error");

    // Terminate program. Unix will close all open descriptors including our TCP socket.
    exit(0);
}