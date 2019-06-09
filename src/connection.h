/*
 * connection.h
 *
 *  Created on: Mar 18, 2019
 *      Author: root
 */

#ifndef SRC_CONNECTION_H_
#define SRC_CONNECTION_H_

#include "common.h"
#include "buffer.h"

class Connection {
public:
    int  check_packet(char * &buf, int & packet_len);
	void close();
public:
	inline SOCKET get_socket();
	inline CONN_STATUS get_status();
	inline uint64_t get_connection_id();
	inline void set_socket(SOCKET s);
	inline uint64_t get_connection_id() const;
	inline void set_socket_addr(sockaddr_in addr);
	inline void set_ip_port(const char * p);
public:
	Connection();
	virtual ~Connection();
private:
	CONN_STATUS m_status;
	uint64_t    m_connect_id;
	SOCKET      m_socket;
	BlockPool  *m_in_buffer;
	BlockPool  *m_out_buffer;
	sockaddr_in m_addr;
	std::string m_ip_port;
};

uint64_t Connection::get_connection_id()
{
	return m_connect_id;
}

SOCKET Connection::get_socket()
{
	return m_socket;
}

CONN_STATUS Connection::get_status()
{
	return m_status;
}

void Connection::set_socket(SOCKET s)
{
    m_socket = s;
}

uint64_t Connection::get_connection_id() const
{
    return m_connect_id;
}

void Connection::set_socket_addr(sockaddr_in addr){
    m_addr = addr;
}

void Connection::set_ip_port(const char * p)
{
    m_ip_port = p;
}



#endif /* SRC_CONNECTION_H_ */
