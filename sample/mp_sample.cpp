// Copyright 2022. All Rights Reserved.
// Author: Bruce-Lee-LY
// Date: 23:23:26 on Sun, May 22, 2022
//
// Description: test memory pool

#include <iostream>
#include <vector>

#include "memory_pool.h"

#define MP_TEST_ALLOC_NUM 30
#define MP_TEST_CYCLE_SIZE 10

int main() {
    MemoryPool mp;
    std::vector<void *> ptrs(MP_TEST_ALLOC_NUM, nullptr);
    size_t bytes = 536870912;  // 512M

    for (int i = 0; i < MP_TEST_CYCLE_SIZE; ++i) {
        bytes = 536870912;  // 512M
        for (int j = 0; j < MP_TEST_ALLOC_NUM; ++j) {
            ptrs[j] = mp.Alloc(bytes);
            std::cout << "ptrs[" << i << "][" << j << "]: " << ptrs[j] << " (" << bytes << ")" << std::endl;
            mp.Free(ptrs[j]);
            bytes /= 2;
        }
    }

    return 0;
}
