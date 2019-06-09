/*
 * test_block.h
 *
 *  Created on: Mar 4, 2019
 *      Author: root
 */

#ifndef SRC_TEST_TEST_BLOCK_H_
#define SRC_TEST_TEST_BLOCK_H_

#include "../buffer.h"
#include "../utils/automatic.hpp"
#include "test.h"

namespace Test
{

class TestBlock :public Test
{
public:
    TestBlock();
    virtual ~TestBlock();
public:
    bool TestCase();
};

} /* namespace Test */

#endif /* SRC_TEST_TEST_BLOCK_H_ */
