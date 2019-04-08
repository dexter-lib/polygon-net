//============================================================================
// Name        : polygon-net.cpp
// Author      : dexter
// Version     :
// Copyright   : polygon.cn
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//using namespace std;

#include "event_handle.h"
#include "utils/automatic.hpp"


#include "test/test_block.h"

int main() {
    Test::Test *pt = new Test::TestBlock();
    pt->TestCase();

    AutomaticID<int> a;
    a++;

    //printf("%u\n",a);

    delete pt;
	return 0;


}
