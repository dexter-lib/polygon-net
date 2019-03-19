/*
 * Connection.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: root
 */

#include "connection.h"

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
 m_out_buffer(NULL)
{

}

Connection::~Connection()
{
}

