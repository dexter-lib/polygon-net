/*
 * test.h
 *
 *  Created on: Mar 4, 2019
 *      Author: root
 */

#ifndef SRC_TEST_TEST_H_
#define SRC_TEST_TEST_H_

namespace Test
{

class Test
{
public:
    Test(){};
    virtual ~Test(){};
public:
    virtual bool TestCase() = 0;
};

} /* namespace Test */

#endif /* SRC_TEST_TEST_H_ */
