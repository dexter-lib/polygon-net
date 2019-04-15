/*
 * common.h
 *
 *  Created on: Feb 13, 2019
 *      Author: root
 */

#ifndef COMMON_H_
#define COMMON_H_


#include <string>
#include <list>
#include <map>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <syslog.h>
#include <pthread.h>
#include <syslog.h>
#include <errno.h>
#include <assert.h>
#include <sys/epoll.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <netdb.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netinet/tcp.h>

#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <ifaddrs.h>

#include <semaphore.h>

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

typedef int SOCKET;

const int MAX_LISTEN_NUM = 100;

#define EPOLL_ADD  1
#define EPOLL_DEL  2
#define EPOLL_MOD  3

typedef enum {
	SUCCESS = 0,
	NOT_CONNECTED,
	CONNECTING,
	FAILURE,
	CLOSED
} CONN_STATUS;

typedef struct st_transfer_head
{
    unsigned short id;
    unsigned short version;
    unsigned int   body_len;
} transfer_head;

static int setfd_nonblock(SOCKET socket)
{
    int f_old;
    f_old = fcntl(socket,F_GETFL,0);
    if( f_old < 0 ) return -1;
    f_old |= O_NONBLOCK;
    return (fcntl(socket,F_SETFL,f_old));
}

typedef struct st_lib_head
{
    int main_fd;
    int listen_num;
    int listen_sock[MAX_LISTEN_NUM];
} lib_head;


#endif /* COMMON_H_ */
