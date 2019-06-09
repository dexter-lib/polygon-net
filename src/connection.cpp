/*
 * Connection.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: root
 */

#include "connection.h"

int Connection::check_packet(char * &buf, int & packet_len)
{
    transfer_head  protol_head;
    packet_len=0;

    uint32_t has_len = m_in_buffer->m_total_cache_len;
    if(has_len >= sizeof(transfer_head))
    {
        m_in_buffer->dump_section((char*)&protol_head, sizeof(transfer_head));

        uint32_t body_len = protol_head.body_len;

        packet_len = sizeof(transfer_head)+body_len;
        if(has_len<packet_len) return 1;
        //task_no = ntohl(protol_head.request_id);
        //task_no = protol_head.request_id;

        buf = new char[packet_len];
        m_in_buffer->peek_out(buf, packet_len);
        return 2;
    }
    else if(has_len <0)
    {
        return -1;
    }
    else
    {
        return 1;
    }

    return -1;
}

void Connection::close()
{
	m_status = CLOSED;
	m_connect_id = 0ULL;

	if(m_in_buffer)
	{
		delete m_in_buffer;
		m_in_buffer = NULL;
	}

	if(m_out_buffer)
	{
		delete m_out_buffer;
		m_out_buffer = NULL;
	}
}

Connection::Connection()
:m_status(NOT_CONNECTED),
 m_connect_id(0ULL),
 m_socket(-1),
 m_in_buffer(NULL),
 m_out_buffer(NULL),
 m_addr(),
 m_ip_port("")
{
    m_connect_id = get_connection_id();
}

Connection::~Connection()
{
}

