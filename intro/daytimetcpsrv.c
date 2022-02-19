// A simple daytime server.
// Works with the client defined in daytimetcpcli.c
// To run the server and client setup
// First start the server like this:
// gcc daytimetcpsrv.c && ./a.out
// Then send a request to server like this:
// curl http://localhost:13
// Now you can also test by running daytimetcpcli client like this:
// gcc daytimetcpcli.c && ./a.out 127.0.0.1

#include "../lib/unp.h"
#include "../lib/wrapsock.c"


int 
main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
   
    // Create a TCP socket
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    // Bind server's well known port (13) to socket
    // This is done by filling in an internet socket address structure and calling bind
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // Allows the server to accept a client connection on any interface
    // incase the server host has multiple interfaces
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13); /* daytime server uses port 13 by convention */
    printf("Listen, before bind fd is %d", listenfd);
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // Convert socket into a listening socket by calling listen. 
    // The kernel will now accept incoming connections from clients on the socket.
    // The server handles one client at a time, multiple client connections arriving at the same time
    // will be queued upto a limit specified by LISTENQ.
    // The steps socket, bind and listen what taken to prepare the listening descriptor (listenfd)
    Listen(listenfd, LISTENQ);

    // Accept client connection and send reply

    // The for loop creates an infinite loop. This means that after processing 
    // a request from a client go ahead to process another one.
    // The server is therefore called an iterative server because it iterates through each client one at a time.
    for( ; ; )
    {
        // Wait for a connection from a client
        // The server process is put to sleep while it waits.
        // Once a TCP connection is established, the accept function returns 
        // a connected descriptor (connfd) that is used to communicate with the new client.
        connfd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        // Fill the buffer with a human readable string of the current time
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        // Write a copy of the buffer content to stdout
        Write(STDOUT_FILENO, buff, strlen(buff));
        // Write the bytes in the buffer to the socket so they can be returned to the client.
        Write(connfd, buff, strlen(buff));

        // Terminate connection with the client.
        Close(connfd);
    }

}
