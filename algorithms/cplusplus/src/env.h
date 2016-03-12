#pragma once

#include <cassert>
#include <cstddef>
#include <stdint.h>
#include "srwlock.h"
#include "noncopyable.h"

namespace algorithm
{
    class Env : noncopyable
    {
    public:
        Env() {}
        static void* Allocate(size_t p_size)
        {
            InterlockedAdd64(&s_allocSize, p_size);

            return HeapAlloc(GetHeap(), 0, p_size);
        }

        static void Free(void* p_mem)
        {
            if (p_mem == NULL) return;

            size_t size = HeapSize(GetHeap(), 0, p_mem);
            if (size > 0)
            {
                InterlockedAdd64(&s_freeSize, size);
            }

            HeapFree(GetHeap(), 0, p_mem);
        }

        static void GetHeapCounters(uint64_t& p_headUsingMemorySize)
        {
            p_headUsingMemorySize = s_allocSize - s_freeSize;
        }

        static HANDLE GetHeap()
        {
            static HANDLE s_heap = NULL;
            if (s_heap == NULL)
            {
                AutoWriteLock l(s_lock);
                if (s_heap == NULL)
                {
                    // see VirtualAlloc as the alternative.
                    // https://msdn.microsoft.com/en-us/library/windows/desktop/aa366887(v=vs.85).aspx
                    s_heap = HeapCreate(0, c_initialHeapSize, 0 /* heap can grow in size */);
                    assert(s_heap != NULL);
                }
            }

            return s_heap;
        }

    public:
        static const SIZE_T c_initialHeapSize = 1024 * 1024 * 1024;

    private:
        static volatile int64_t s_allocSize;
        static volatile int64_t s_freeSize;

        static SRWLock s_lock;
    };

    volatile int64_t Env::s_freeSize = 0;
    volatile int64_t Env::s_freeSize = 0;
}
