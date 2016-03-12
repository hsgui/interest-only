#pragma once

#include <Windows.h>
#include "noncopyable.h"

namespace algorithm
{
    // https://msdn.microsoft.com/en-us/library/windows/desktop/aa904937(v=vs.85).aspx
    // https://github.com/mongodb/mongo/tree/master/src/mongo/util/concurrency
    // https://github.com/mongodb/mongo/blob/master/src/mongo/util/concurrency/rwlockimpl.cpp
    class SRWLock : noncopyable
    {
    public:
        SRWLock()
            : m_lock()
        {
            InitializeSRWLock(&m_lock);
        }

        void wl()
        {
            ::AcquireSRWLockExclusive(&m_lock);
        }

        void wu()
        {
            ::ReleaseSRWLockExclusive(&m_lock);
        }

        void rl()
        {
            ::AcquireSRWLockShared(&m_lock);
        }

        void ru()
        {
            ::ReleaseSRWLockShared(&m_lock);
        }

    private:
        SRWLOCK m_lock;
    };

    class AutoReadLock : noncopyable
    {
    public:
        AutoReadLock(SRWLock& p_lock)
            : m_lock(p_lock)
        {
            m_lock.rl();
        }

        ~AutoReadLock()
        {
            m_lock.ru();
        }
    private:
        SRWLock& m_lock;
    };

    class AutoWriteLock : noncopyable
    {
    public:
        AutoWriteLock(SRWLock& p_lock)
            : m_lock(p_lock)
        {
            m_lock.wl();
        }

        ~AutoWriteLock()
        {
            m_lock.wu();
        }

    private:
        SRWLock& m_lock;
    };
}