#ifndef TEST_H
#define TEST_H

#include <iostream>
using namespace std;

#define PASS(X) cout << "\033[1;32mTEST " << X << " PASSED!!\033[0m\n"
#define FAIL(X) cout << "\033[1;31mTEST " << X << " FAILED!!\033[0m\n"

void test(bool test, int test_num=0){
  if(test)
    PASS(test_num);
  else
    FAIL(test_num);
}

#endif
