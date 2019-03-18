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
	void close();
public:
	inline SOCKET get_socket();
	inline CONN_STATUS get_status();
	inline uint64_t get_connection_id();
public:
	Connection();
	virtual ~Connection();
private:
	CONN_STATUS m_status;
	uint64_t    m_connect_id;
	SOCKET      m_socket;
	BlockPool  *m_in_buffer;
	BlockPool  *m_out_buffer;
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



#endif /* SRC_CONNECTION_H_ */
