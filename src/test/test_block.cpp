/*
 * test_block.cpp
 *
 *  Created on: Mar 4, 2019
 *      Author: root
 */

#include "test_block.h"

#include <string.h>

namespace Test
{

TestBlock::TestBlock()
{

}

TestBlock::~TestBlock()
{
}

bool TestBlock::TestCase()
{
    BlockPool * pool = new BlockPool();

    int data_len = 1024 * 1001 + 1;
    char * data = (char *)malloc(data_len);

    memset(data, '1', data_len);

    pool->put(data, (size_t)data_len);
    printf("pool->size %u, current_len %u, pool->buffer->len %u\n", pool->m_total_cache_len, pool->m_pcur_block->buffer->m_current_len, pool->m_pcur_block->buffer->m_buffer_len);
    pool->put(data, (size_t)data_len);
    printf("pool->size %u, current_len %u, pool->buffer->len %u\n", pool->m_total_cache_len, pool->m_pcur_block->buffer->m_current_len, pool->m_pcur_block->buffer->m_buffer_len);

    char * data2 = (char *)malloc(pool->m_total_cache_len + 1);

    memset(data2, 0, pool->m_total_cache_len + 1);

    pool->dump_all(data2, pool->m_total_cache_len);

    printf("data:%d\n", strlen(data2));

    char * data3 = (char *)malloc(pool->m_total_cache_len + 1);

    memset(data, '1', data_len);

    printf("data:%d\n", pool->m_total_cache_len);

    pool->peek_out(data3, 2059500);

    printf("data:%d, strlen(data3)=%d\n", pool->m_total_cache_len, strlen(data3));

    int i = pool->peek_out(data3, 1000);

    AutomaticID<int> a;

    printf("++++++++++++++++%ld+++++++++++++\n", a++);

    printf("%d, %d, %d, %d, %p", pool->m_total_cache_len, strlen(data3), pool->m_block_size, i, pool->m_pblock_pool);

    delete pool;
    free(data);
    free(data2);



    return true;
}

} /* namespace Test */
