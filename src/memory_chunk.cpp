// Copyright 2022. All Rights Reserved.
// Author: Bruce-Lee-LY
// Date: 23:22:39 on Sun, May 22, 2022
//
// Description: memory chunk

#include "memory_chunk.h"

#include <stdlib.h>

MemoryChunk::MemoryChunk(size_t bytes) : m_bytes(bytes), m_requested_bytes(bytes) {
    m_ptr = malloc(bytes);
}

MemoryChunk::~MemoryChunk() {
    if (m_ptr) {
        free(m_ptr);
        m_ptr = nullptr;
    }
    m_bytes = 0;
    m_requested_bytes = 0;
}

void MemoryChunk::Set(size_t requested_bytes) {
    m_requested_bytes = requested_bytes;
}

void *MemoryChunk::Get() {
    return m_ptr;
}
