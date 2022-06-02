// Copyright 2022. All Rights Reserved.
// Author: Bruce-Lee-LY
// Date: 23:23:00 on Sun, May 22, 2022
//
// Description: memory block

#ifndef __MEMORY_POOL_MEMORY_BLOCK_H__
#define __MEMORY_POOL_MEMORY_BLOCK_H__

#include <list>
#include <mutex>

#include "memory_chunk.h"

class MemoryBlock {
public:
    MemoryBlock(size_t idx);
    ~MemoryBlock();

    void *Alloc(size_t bytes);
    void Free(void *ptr);

private:
    MemoryBlock(const MemoryBlock &) = delete;
    const MemoryBlock &operator=(const MemoryBlock &) = delete;

    size_t m_idx;
    size_t m_chunk_bytes;  // block bytes is 256 << m_idx, min bytes is 256B

    std::list<MemoryChunk *> m_free_chunks;
    std::list<MemoryChunk *> m_use_chunks;

    mutable std::mutex m_mutex;
};

#endif  // __MEMORY_POOL_MEMORY_BLOCK_H__
