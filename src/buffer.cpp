/*
 * Buffer.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: root
 */

#include "buffer.h"

BlockPool::BlockPool() {
	m_pblock_poll = m_pcur_block = new Block;
	m_total_cache_len = 0;
}

BlockPool::~BlockPool() {
	release();
}

void BlockPool::release()
{
	Block *pblock = m_pblock_poll;
	while(pblock)
	{
		Block *ptmp = pblock;
		pblock = pblock->next;
		delete ptmp;
	}

	m_pcur_block = m_pblock_poll = NULL;
	m_total_cache_len = 0;
}
