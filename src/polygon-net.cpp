//============================================================================
// Name        : polygon-net.cpp
// Author      : dexter
// Version     :
// Copyright   : polygon.cn
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>

#include "event_handle.h"
#include "utils/automatic.hpp"

#include "test/test_block.h"
#include "mepoll.h"
#include "connection.h"


lib_head  g_server_io;

uint64_t g_connection_id = 0ULL;

PlatformMutex g_conn_id_mutex;

Connection* AccepterNewFD(int sock);

Connection * new_conn(int sock, struct sockaddr_in addr);

void * lib_listen(void *p)
{
    while(1)
    {
        int main_kdpfd = g_server_io.main_fd;
        std::map<void*,int> fd_map;
        for(int i=0; i<g_server_io.listen_num; i++)
        {
            int listen_fd = g_server_io.listen_sock[i];
            struct epoll_event ev;
            void *listen_ptr = malloc(1);
		    fd_map[listen_ptr]=listen_fd;
		    epoll_set_event(main_kdpfd, listen_fd, EPOLL_ADD, 1, 0, listen_ptr);
        }

        epoll_event events[MAX_EVENTS];

        while(1)
        {
        	int nfds = epoll_wait(main_kdpfd, events, MAX_EVENTS, 1);

        	if(nfds < 0)
        	{
        		int err = errno;
        		if(EINTR == err)
        		{
        			continue;
        		}

        		fprintf(stderr, "epoll_wait error %s\n", strerror(err));
        		fflush(stderr);
        		exit(-1);
        	}

        	for(int i = 0; i < nfds; i++)
        	{
        		void * listen_ptr = events[i].data.ptr;
        		std::map<void *, int>::iterator iter = fd_map.find(listen_ptr);
        		int listen_fd = 0;
        		if(iter != fd_map.end()) listen_fd = iter->second;

        		if(listen_fd)
        		{
        		    AccepterNewFD(listen_fd);
        		}
        	}

        }

    }

	return (void *)NULL;
}


Connection* AccepterNewFD(int sock)
{
    SOCKET newsk;
    socklen_t addrlen;
    struct sockaddr_in addr;

    addrlen = sizeof(struct sockaddr_in);
RT1:
    newsk = accept(sock,(struct sockaddr*) &addr,&addrlen);

    if( newsk < 0 )
    {
        int err=errno;
        if(err == EMFILE)
            exit(1);

        if(err==EINTR)
            goto RT1;

        if(err==EAGAIN||err==EWOULDBLOCK)
            return NULL;

        return NULL;
    }

    if( AF_INET != addr.sin_family || addrlen != sizeof(struct sockaddr_in))
    {
        close(sock);
        return NULL;
    }

    return new_conn(sock, addr);

}


Connection * new_conn(int sock, struct sockaddr_in addr)
{
    if(setfd_nonblock(sock))
    {
        close(sock);
        return NULL;
        printf("set nonblock error %d\n", sock);
    }

    int flag=1;
    int r=setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(char *) &flag,sizeof(int));

    Connection * conn = new Connection();

    conn->set_socket(sock);
    conn->set_socket_addr(addr);

    char ip_port[256];

    snprintf(ip_port, 256, "%s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    conn->set_ip_port(ip_port);

    return conn;
}

int main() {
    Test::Test *pt = new Test::TestBlock();
    pt->TestCase();

    AutomaticID<int> a;
    a++;

    //printf("%u\n",a);

    delete pt;
	return 0;


}
