#pragma once

#include <vector>
#include <stdint.h>
#include <assert.h>
#include <cstddef>
#include "env.h"

namespace algorithm{
    static const int c_blockSize = 4096;

    class Arena
    {
    public:
        Arena(size_t p_blockSize = 0);

        ~Arena();

        char* Allocate(size_t p_bytes);

        char* AllocateAligned(size_t p_bytes);

        size_t MemoryUsage() const
        {
            return m_blocksMemory + m_blocks.capacity() * sizeof(char*);
        }

    public:
        Arena(const Arena&) = delete;

        Arena& operator=(const Arena&) = delete;

    private:
        char* AllocateFallback(size_t p_bytes);
        char* AllocateNewBlock(size_t p_blockBytes);

    private:
        char* m_allocPtr;
        size_t m_allocBytesRemaining;

        std::vector<char*> m_blocks;
        size_t m_blocksMemory;

        size_t m_blockSize;
    };

    inline char* Arena::Allocate(size_t p_bytes)
    {
        assert(p_bytes > 0);

        if (p_bytes <= m_allocBytesRemaining)
        {
            char* result = m_allocPtr;
            m_allocPtr += p_bytes;
            m_allocBytesRemaining -= p_bytes;

            return result;
        }

        return AllocateFallback(p_bytes);
    }

    Arena::Arena(size_t p_blockSize)
    {
        m_blocksMemory = 0;
        m_allocPtr = 0;
        m_allocBytesRemaining = 0;
        m_blockSize = (p_blockSize > 0) ? p_blockSize : c_blockSize;
    }

    Arena::~Arena()
    {
        for (size_t i = 0; i < m_blocks.size(); ++i)
        {
            Env::Free(m_blocks[i]);
        }
    }

    char* Arena::AllocateNewBlock(size_t p_blockBytes)
    {
        char* result = reinterpret_cast<char*>(Env::Allocate(p_blockBytes));
        m_blocksMemory += p_blockBytes;
        m_blocks.push_back(result);

        return result;
    }

    char* Arena::AllocateFallback(size_t p_bytes)
    {
        if (p_bytes > m_blockSize / 4)
        {
            // Object is more than a quarter of our block size.  Allocate it separately
            // to avoid wasting too much space in leftover bytes.
            char* result = AllocateNewBlock(p_bytes);

            return result;
        }

        // We waste the remaining space in the current block.
        m_allocPtr = AllocateNewBlock(m_blockSize);
        m_allocBytesRemaining = m_blockSize;

        char* result = m_allocPtr;
        m_allocPtr += p_bytes;
        m_allocBytesRemaining -= p_bytes;

        return result;
    }

    char* Arena::AllocateAligned(size_t p_bytes)
    {
        const int align = sizeof(void*);    // We'll align to pointer size
        assert((align & (align - 1)) == 0); // Pointer size should be a power of 2

        size_t currentMod = reinterpret_cast<uintptr_t>(m_allocPtr) & (align - 1);
        size_t slop = (currentMod == 0 ? 0 : align - currentMod);
        size_t needed = p_bytes + slop;

        char* result;
        if (needed <= m_allocBytesRemaining)
        {
            result = m_allocPtr + slop;
            m_allocPtr += needed;
            m_allocBytesRemaining -= needed;
        }
        else
        {
            // AllocateFallback always returned aligned memory
            result = AllocateFallback(p_bytes);
        }

        assert((reinterpret_cast<uintptr_t>(result)& (align - 1)) == 0);
        return result;
    }
}