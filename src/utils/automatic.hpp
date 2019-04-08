/*
 * automatic.hpp
 *
 *  Created on: Apr 4, 2019
 *      Author: root
 */

#ifndef SRC_UTILS_AUTOMATIC_HPP_
#define SRC_UTILS_AUTOMATIC_HPP_

#include "platform_mutex.h"

template <typename T>
class AutomaticID
{
public:
    AutomaticID(){};
    virtual ~AutomaticID(){};
public:
    T operator ++(T t)
    {
        PlatformMutex mutex;
        mutex.lock();
        ++t;
        mutex.unlock();
        return t;
    }

    T operator ++()
    {
        PlatformMutex mutex;
        mutex.lock();
        t++;
        mutex.unlock();
        return t;
    }
private:
    T t;
};


#endif /* SRC_UTILS_AUTOMATIC_HPP_ */
