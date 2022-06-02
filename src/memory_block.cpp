// Copyright 2022. All Rights Reserved.
// Author: Bruce-Lee-LY
// Date: 23:23:00 on Sun, May 22, 2022
//
// Description: memory block

#include "memory_block.h"

#include <algorithm>

MemoryBlock::MemoryBlock(size_t idx) : m_idx(idx), m_chunk_bytes(256 << idx) {}

MemoryBlock::~MemoryBlock() {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto free_iter = m_free_chunks.begin(); free_iter != m_free_chunks.end();) {
        delete *free_iter;
        m_free_chunks.erase(free_iter++);
    }

    for (auto use_iter = m_use_chunks.begin(); use_iter != m_use_chunks.end();) {
        delete *use_iter;
        m_use_chunks.erase(use_iter++);
    }
}

void *MemoryBlock::Alloc(size_t bytes) {
    std::lock_guard<std::mutex> lock(m_mutex);
    MemoryChunk *chunk = nullptr;
    if (!m_free_chunks.empty()) {
        chunk = m_free_chunks.front();
        m_free_chunks.pop_front();
    } else {
        chunk = new MemoryChunk(m_chunk_bytes);
    }

    chunk->Set(bytes);
    m_use_chunks.push_back(chunk);
    return chunk->Get();
}

void MemoryBlock::Free(void *ptr) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto iter = m_use_chunks.begin(); iter != m_use_chunks.end(); ++iter) {
        if ((*iter)->Get() == ptr) {
            m_free_chunks.push_back(*iter);
            m_use_chunks.erase(iter);
            break;
        }
    }
}
