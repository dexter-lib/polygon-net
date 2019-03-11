/*
 * Buffer.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: root
 */

#include "buffer.h"

int32_t BlockPool::put(const char * data, uint32_t len)
{
	uint32_t current_len        = m_pcur_block->buffer->m_current_len;
	uint32_t buffer_len         = m_pcur_block->buffer->m_buffer_len;
	uint32_t buffer_left_len    = buffer_left_len - current_len;

	char * pbuffer = m_pcur_block->buffer->m_pbuffer;

	if(len <= buffer_left_len)
	{
		memcpy(pbuffer + current_len, data, len);
	}
	else
	{
		uint32_t left_len = len;
		memcpy(pbuffer + current_len, data, buffer_left_len);
		data += buffer_left_len;
		m_pcur_block->buffer->m_current_len += buffer_left_len;
		left_len -= buffer_left_len;

		while(left_len)
		{
			Block *p = new Block;
			m_pcur_block->next = p;
			m_pcur_block = m_pcur_block->next;

			pbuffer         = m_pcur_block->buffer->m_pbuffer;
			current_len     = 0;
			buffer_left_len = m_pblock_pool->buffer->m_buffer_len;

			if(left_len <= buffer_left_len)
			{
				memcpy(pbuffer, data, left_len);
				left_len = 0;
				m_pblock_pool->buffer->m_current_len -= left_len;
			}
			else
			{
				memcpy(pbuffer, data, left_len);
				m_pblock_pool->buffer->m_current_len += buffer_left_len;
				left_len -= buffer_left_len;
				data += buffer_left_len;
			}

		}
	}

	m_total_cache_len += len;
	return m_total_cache_len;
}


BlockPool::BlockPool() {
	m_pblock_pool = m_pcur_block = new Block;
	m_total_cache_len = 0;
}

BlockPool::~BlockPool() {
	release();
}

void BlockPool::release()
{
	Block *pblock = m_pblock_pool;
	while(pblock)
	{
		Block *ptmp = pblock;
		pblock = pblock->next;
		delete ptmp;
	}

	m_pcur_block = m_pblock_pool = NULL;
	m_total_cache_len = 0;
}

