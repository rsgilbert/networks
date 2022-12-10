#include "./unp.h"
#include "./error.c"
#include <string.h>

// Wrapper functions that perform the actual function call,
// tests the return value and terminates on an error.
// The convention is to capitalize the name of the function.

/** Wrapper around socket function */
int 
Socket(int family, int type, int protocol)
{
    int n;
    if( (n = socket(family, type, protocol)) < 0)
        err_sys("socket error");
    return n;
}

/* Wrapper around bind function */
void 
Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if(bind(fd, sa, salen) < 0)
        err_sys("bind error");
}

/** Wrapper around listen function */
void Listen(int fd, int n)
{
    if(listen(fd, n) < 0)
        err_sys("listen error");
}




/** Wrapper around pthread_mutex_lock function */
void 
Pthread_mutex_lock(pthread_mutex_t *mptr)
{
    int n;
    if ( (n = pthread_mutex_lock(mptr)) == 0)
        return;
    errno = n;
    err_sys("pthread_mutex_lock error");
}

/** Wrapper around accept function. Returns file descriptor for socket created, this is the new file descriptor for the connection. */
int
Accept(int fd, struct sockaddr *sa, socklen_t *salenptr) 
{
    int n;
again:
    if( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef EPROTO
        if(errno == EPROTO || errno == ECONNABORTED)
#else 
        if(errno == ECONNABORTED)
#endif
            // continue waiting for connection
            goto again;
        else 
            err_sys("accept error");
    }
    return n;
}


/** Wrapper around write function */
void 
Write(int fd, void *buf, size_t n)
{
    if(write(fd, buf, n) < 0) 
        err_sys("write error");
}

/** Wrapper around close function */
void 
Close(int fd)
{
    if(close(fd) < 0)
        err_sys("close error");
}

/** Wrapper around connect function */
void Connect(int fd, struct sockaddr *sa, socklen_t len) 
{
    if(connect(fd, sa, len) < 0) 
        err_sys("connect error");
    
}