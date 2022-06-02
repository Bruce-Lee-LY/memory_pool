// Copyright 2022. All Rights Reserved.
// Author: Bruce-Lee-LY
// Date: 23:22:39 on Sun, May 22, 2022
//
// Description: memory chunk

#ifndef __MEMORY_POOL_MEMORY_CHUNK_H__
#define __MEMORY_POOL_MEMORY_CHUNK_H__

#include <stddef.h>

class MemoryChunk {
public:
    MemoryChunk(size_t bytes);
    ~MemoryChunk();

    void Set(size_t requested_bytes);
    void *Get();

private:
    size_t m_bytes;            // full size of buffer
    size_t m_requested_bytes;  // what the client actually wanted
    void *m_ptr;
};

#endif  // __MEMORY_POOL_MEMORY_CHUNK_H__
