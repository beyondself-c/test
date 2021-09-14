#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "ktest.h"
using namespace std;

int add(int a, int b) {
    return a + b;
}

TEST(test1, add){
    LOG("test1,add"); 
    EXPECT_EQ(add(3, 4), 7); // ==
    EXPECT_NE(add(3, 4), 6);  // !=
    EXPECT_LT(add(3, 4), 8); // <
    EXPECT_LE(add(3, 4), 7); // <=
    EXPECT_GT(add(3, 4), 6); // >
    EXPECT_GE(add(3, 4), 7); // >=
}

TEST(test2, add) {
    LOG("test2,add"); 
    EXPECT_EQ(add(3, 4), 7); // ==
    EXPECT_NE(add(3, 4), 7); // !=
    EXPECT_LT(add(3, 4), 8); // <
    EXPECT_LE(add(3, 4), 7); // <=
    EXPECT_GT(add(3, 4), 6); // >
    EXPECT_GE(add(3, 4), 7); // >=
}

int main() {
    return RUN_ALL_TESTS();
}

