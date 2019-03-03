/*
 * buffer.h
 *
 *  Created on: Feb 23, 2019
 *      Author: root
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include <assert.h>
#include <unistd.h>

#define DEFAULT_BLOCK_SIZE 100 * 1024

class Buffer{
public:
	Buffer()
	{
		m_pbuffer = (char *)malloc(DEFAULT_BLOCK_SIZE);
		assert(m_pbuffer);
		m_buffer_len = DEFAULT_BLOCK_SIZE;
		m_current_len = 0;
	}
	Buffer(uint32_t len)
	{
		m_pbuffer = (char *)malloc(len);
		assert(m_pbuffer);
		m_buffer_len = len;
		m_current_len = 0;
	}
	virtual ~Buffer()
	{
		if(m_pbuffer)
		{
			free( m_pbuffer );
			m_pbuffer = NULL;
		}

		m_buffer_len = m_current_len = 0;
	}
public:
	char *   m_pbuffer;
	uint32_t m_current_len;
	uint32_t m_buffer_len;
};

class Block {
public:
	Block()
	{
		buffer = new Buffer();
		next = NULL;
	}

	virtual ~Block()
	{
		if(buffer)
		{
			delete buffer;
			buffer = NULL;
		}
	}

	Buffer get_next()
	{
		return next;
	}

public:
	Block *next;
	Buffer *buffer;
};

class BlockPool {
public:
	void release();
public:
	uint32_t m_total_cache_len;
	Block *  m_pblock_poll;
	Block *  m_pcur_block;
public:
	BlockPool();
	virtual ~BlockPool();
};

#endif /* BUFFER_H_ */