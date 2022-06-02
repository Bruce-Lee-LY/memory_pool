// Copyright 2022. All Rights Reserved.
// Author: Bruce-Lee-LY
// Date: 23:23:26 on Sun, May 22, 2022
//
// Description: memory pool

#include "memory_pool.h"

MemoryPool::MemoryPool(size_t block_size) : m_block_size(block_size) {
    for (size_t i = 0; i < m_block_size; ++i) {
        m_blocks.emplace_back(new MemoryBlock(i));
    }
}

MemoryPool::~MemoryPool() {
    for (auto iter = m_blocks.begin(); iter != m_blocks.end();) {
        delete *iter;
        iter = m_blocks.erase(iter);
    }
    std::vector<MemoryBlock *>().swap(m_blocks);
}

void *MemoryPool::Alloc(size_t bytes) {
    size_t idx = get_block_idx(bytes);
    return m_blocks[idx]->Alloc(bytes);
}

void MemoryPool::Free(void *ptr) {
    for (auto &block : m_blocks) {
        block->Free(ptr);
    }
}

size_t MemoryPool::get_block_idx(size_t bytes) {
    size_t round_bytes = round_up(bytes);
    size_t right_bytes = std::max<size_t>(round_bytes, m_min_size) >> m_min_bits;
    size_t idx = std::min(m_block_size - 1, floor_log2(right_bytes));
    return idx;
}

size_t MemoryPool::round_up(size_t bytes) {
    size_t round_bytes = (m_min_size * ((bytes + m_min_size - 1) / m_min_size));
    return round_bytes;
}

// floor(log2(n))
size_t MemoryPool::floor_log2(size_t n) {
    size_t r = 0;
    while (n > 0) {
        ++r;
        n >>= 1;
    }
    return r - 1;
}
