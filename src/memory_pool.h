// Copyright 2022. All Rights Reserved.
// Author: Bruce-Lee-LY
// Date: 23:23:26 on Sun, May 22, 2022
//
// Description: memory pool

#ifndef __MEMORY_POOL_MEMORY_POOL_H__
#define __MEMORY_POOL_MEMORY_POOL_H__

#include <vector>

#include "memory_block.h"

class MemoryPool {
public:
    MemoryPool(size_t block_size = 21);
    ~MemoryPool();

    void *Alloc(size_t bytes);
    void Free(void *ptr);

private:
    MemoryPool(const MemoryPool &) = delete;
    const MemoryPool &operator=(const MemoryPool &) = delete;

    size_t get_block_idx(size_t bytes);
    size_t round_up(size_t bytes);
    size_t floor_log2(size_t n);

    size_t m_block_size;
    std::vector<MemoryBlock *> m_blocks;  // memory block is increased from 256B (idx = 0) to 512MB (idx = 20)

    const size_t m_min_bits = 8;
    const size_t m_min_size = 1 << m_min_bits;
};

#endif  // __MEMORY_POOL_MEMORY_POOL_H__
