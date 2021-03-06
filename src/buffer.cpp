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
	uint32_t buffer_left_len    = buffer_len - current_len;

    char * pbuffer = m_pcur_block->buffer->m_pbuffer;

	if(len <= buffer_left_len)
	{
		memcpy(pbuffer + current_len, data, len);
		m_pcur_block->buffer->m_current_len + len;
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
			m_block_size += 1;

			pbuffer         = m_pcur_block->buffer->m_pbuffer;
			buffer_left_len = m_pcur_block->buffer->m_buffer_len;

			if(left_len <= buffer_left_len)
			{
				memcpy(pbuffer, data, left_len);
				m_pcur_block->buffer->m_current_len += left_len;
                left_len = 0;
			}
			else
			{
				memcpy(pbuffer, data, buffer_left_len);
				m_pcur_block->buffer->m_current_len += buffer_left_len;
				left_len -= buffer_left_len;
				data += buffer_left_len;
			}

		}
	}

	m_total_cache_len += len;
	return m_total_cache_len;
}

int32_t BlockPool::dump_all(char * data, uint32_t len)
{
    if(len < m_total_cache_len) return 0;

    uint32_t tmp_len = m_total_cache_len;
    Block *p = m_pblock_pool;

    while(tmp_len && p)
    {
        memcpy(data, p->buffer->m_pbuffer, p->buffer->m_current_len);
        data += p->buffer->m_current_len;
        tmp_len -= p->buffer->m_current_len;
        p = p->next;
    }

    return tmp_len;
}

int32_t BlockPool::dump_section(char * data, uint32_t len)
{
    //if(len > m_total_cache_len) return -1;

    if(0 == m_total_cache_len) return 0;

    uint32_t tmp_len = len;
    Block *p = m_pblock_pool;

    while(tmp_len && p)
    {
        if(tmp_len >= p->buffer->m_current_len)
        {
            memcpy(data, p->buffer->m_pbuffer, p->buffer->m_current_len);
            data += p->buffer->m_current_len;
            tmp_len -= p->buffer->m_current_len;
            p = p->next;
        }
        else
        {
            memcpy(data, p->buffer->m_pbuffer, tmp_len);
            tmp_len = 0;
        }
    }

    return tmp_len;
}

int32_t BlockPool::peek_out(char * data, uint32_t len)
{
    //if(len > m_total_cache_len) return -1;

    if(0 == m_total_cache_len) return 0;

    uint32_t tmp_len = len;
    Block *p = m_pblock_pool;

    int32_t total_len = 0;

    while(tmp_len && p && m_total_cache_len)
    {
        if(tmp_len >= p->buffer->m_current_len)
        {
            memcpy(data, p->buffer->m_pbuffer, p->buffer->m_current_len);
            data += p->buffer->m_current_len;
            total_len += p->buffer->m_current_len;
            tmp_len -= p->buffer->m_current_len;
            m_total_cache_len -= p->buffer->m_current_len;
            Block *tmp_block = p;
            p = p->next;
            m_pblock_pool = p;
            m_block_size -= 1;
            delete tmp_block;
        }
        else
        {
            memcpy(data, p->buffer->m_pbuffer, tmp_len);
            m_total_cache_len -= tmp_len;
            p->buffer->m_current_len -= tmp_len;
            total_len += tmp_len;
            memmove(p->buffer->m_pbuffer, p->buffer->m_pbuffer + tmp_len, p->buffer->m_current_len);
            tmp_len = 0;
        }
    }

    if(!p)
    {
        init();
    }

    return total_len;
}

void BlockPool::init()
{
    m_pblock_pool = m_pcur_block = new Block;
    m_total_cache_len = 0;
    m_block_size = 1;
}


BlockPool::BlockPool() {
    init();
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

