#include "../lib/unp.h"
#include "../lib/error.c"

int 
main()
{
    struct sockaddr_in6 servaddr;
    printf("ipv6 size %d\n", sizeof(servaddr)); // 28

}