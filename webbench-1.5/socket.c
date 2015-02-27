/* $Id: socket.c 1.1 1995/01/01 07:11:14 cthuang Exp $
 *
 * This module has been modified by Radim Kolar for OS/2 emx
 */

/***********************************************************************
  module:       socket.c
  program:      popclient
  SCCS ID:      @(#)socket.c    1.5  4/1/94
  programmer:   Virginia Tech Computing Center
  compiler:     DEC RISC C compiler (Ultrix 4.1)
  environment:  DEC Ultrix 4.3 
  description:  UNIX sockets code.
 ***********************************************************************/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int Socket(const char *host, int clientPort)
{
    int sock;
    unsigned long inaddr;
    struct sockaddr_in ad;
    struct hostent *hp;
    
//    printf("%s\n",host);
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    
    inaddr = inet_addr(host);
    if (inaddr != INADDR_NONE)
            /* 无符号长整型和负数比较
             * 上面这句话有问题， iner_addr 返回一个FFFFFFFF，即-1为错误，在ip地址翻译上 
             * 255.255.255.255，这个也就是 为什么不建议使用 inet_addr的原因*/
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
else
    {
         //   printf("test 4\n");
        hp = gethostbyname(host);
        //    printf("test 5\n");
        if (hp == NULL)
            return -1;
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
    ad.sin_port = htons(clientPort);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;
    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
        return -1;
    return sock;
}

