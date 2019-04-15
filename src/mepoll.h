/*
 * mepoll.h
 *
 *  Created on: Apr 15, 2019
 *      Author: root
 */

#ifndef SRC_MEPOLL_H_
#define SRC_MEPOLL_H_

#include <sys/epoll.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"
#include <assert.h>
#include <sys/types.h>

#include "common.h"

static const char * epolltype_atoi(int x)
{
	switch (x) {
		case EPOLL_CTL_ADD:
			return "EPOLL_CTL_ADD";

		case EPOLL_CTL_DEL:
			return "EPOLL_CTL_DEL";

		case EPOLL_CTL_MOD:
			return "EPOLL_CTL_MOD";

		default:
			return "UNKNOWN_EPOLLCTL_OP";
	}
}

static int epoll_set_event(int kdpfd,int fd, int action, int need_read, int need_write, void * ptr)
{
	int epoll_ctl_type = 0;
	struct epoll_event ev;

	ev.events = 0;

	assert(fd >= 0);

	if( action == EPOLL_ADD )
	{
	    epoll_ctl_type = EPOLL_CTL_ADD;
	    if(need_read)
	   	    ev.events |= EPOLLIN;
	    if(need_write)
	   	    ev.events |= EPOLLOUT;
	    ev.events |= EPOLLHUP | EPOLLERR;
	    ev.data.ptr = ptr;
	}
	else if( action == EPOLL_DEL )
	{
	    epoll_ctl_type = EPOLL_CTL_DEL;
	    ev.events = 0;
	}
	else if( action == EPOLL_MOD )
	{
        epoll_ctl_type = EPOLL_CTL_MOD;
	    if(need_read)
	   	    ev.events |= EPOLLIN;
	    if(need_write)
	   	    ev.events |= EPOLLOUT;
	    ev.events |= EPOLLHUP | EPOLLERR;
	    ev.data.ptr = ptr;

	}
	else
	{
        return -1;
	}

    if (epoll_ctl(kdpfd, epoll_ctl_type, fd, &ev) < 0)
    {
        return -1;
    }
	return 1;
}




#endif /* SRC_MEPOLL_H_ */
