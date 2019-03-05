/*
 * test_block.cpp
 *
 *  Created on: Mar 4, 2019
 *      Author: root
 */

#include "test_block.h"

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
    delete pool;
    return true;
}

} /* namespace Test */
