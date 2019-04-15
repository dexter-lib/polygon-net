//============================================================================
// Name        : polygon-net.cpp
// Author      : dexter
// Version     :
// Copyright   : polygon.cn
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
//using namespace std;

#include "event_handle.h"
#include "utils/automatic.hpp"

#include "test/test_block.h"
#include "mepoll.h"


lib_head  g_server_io;

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
    }

	return (void *)NULL;
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
