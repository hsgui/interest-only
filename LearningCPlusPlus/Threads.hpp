#pragma once

#include <atomic>
#include <Windows.h>

namespace ModernDesign
{
	template<typename Host>
	class SingleThreaded
	{
	public:
		struct Lock
		{
			Lock(){}
			explicit Lock(const SingleThreaded&){}
		};

		typedef Host VolatileType;
		typedef int IntType;

		static IntType AtomicAdd(volatile IntType& p_lval, IntType p_val)
		{
			return p_lval += p_val;
		}

		static IntType AtomicSubtract(volatile IntType& p_lval, IntType p_val)
		{
			return p_lval -= p_val;
		}

		static IntType AtomicMultiply(volatile IntType& p_lval, IntType p_val)
		{
			return p_lval *= p_val;
		}
	};

	template<typename Host>
	class ObjectLevelLockable
	{
		mutable CRITICAL_SECTION m_mtx;
	public:
		ObjectLevelLockable()
		{
			::InitializeCriticalSection(m_mtx);
		}
		~ObjectLevelLockable()
		{
			::DeleteCriticalSection(m_mtx);
		}

		class Lock;
		friend class Lock;

		class Lock
		{
			ObjectLevelLockable const& m_host;

			Lock(const Lock&);
			Lock& operator=(const Lock&);

		public:
			explicit Lock(const ObjectLevelLockable& p_host)
				: m_host(p_host);
			{
				::EnterCriticalSection(&m_host.m_mtx);
			}
			~Lock()
			{
				::LeaveCriticalSection(&m_host.m_mtx);
			}
		};

		typedef volatile Host VolatileType;
		typedef LONG IntType;

		static IntType AtomicIncrement(volatile IntType& p_lval)
		{
			return InterlockedIncrement(&const_cast<IntType&>(p_lval));
		}
		static IntType AtomicDecrement(volatile IntType& p_lval)
		{
			return InterlockedDecrement(&const_cast<IntType&>(p_lval);
		}
		static void AtomicAssign(volatile IntType& p_lval, IntType p_val)
		{
			return InterlockedExchange(&const_cast<IntType&>(p_lval), p_val);
		}
		static void AtomicAssign(IntType& p_lval, volatile IntType& p_val)
		{
			InterlockedExchange(&p_lval, p_val);
		}
	};

	template<typename Host>
	class ClassLevelLockable
	{
		struct Initializer
		{
			CRITICAL_SECTION m_mtx;

			Initializer()
			{
				::InitializeCriticalSection(&m_mtx);
			}
			~Initializer()
			{
				::DeleteCriticalSection(&m_mtx);
			}
		};

		static Initializer m_initializer;

	public:
		class Lock;
		friend class Lock;

		class Lock
		{
			Lock(const Lock&);
			Lock& operator=(const Lock&);
		public:
			Lock()
			{
				::EnterCriticalSection(&m_initializer.m_mtx);
			}
			~Lock()
			{
				::LeaveCriticalSection(&m_initializer.m_mtx);
			}
		};

		typedef volatile Host ValatileType;
		typedef LONG IntType;

		static IntType AtomicIncrement(volatile IntType& p_lval)
		{
			return InterlockedIncrement(&const_cast<IntType&>(p_lval));
		}
		static IntType AtomicDecrement(volatile IntType& p_lval)
		{
			return InterlockedDecrement(&const_cast<IntType&>(p_lval);
		}
		static void AtomicAssign(volatile IntType& p_lval, IntType p_val)
		{
			return InterlockedExchange(&const_cast<IntType&>(p_lval), p_val);
		}
		static void AtomicAssign(IntType& p_lval, volatile IntType& p_val)
		{
			InterlockedExchange(&p_lval, p_val);
		}
	};

	template<typename Host>
	typename ClassLevelLockable<Host>::Iniitializer
		ClassLevelLockable<Host>::m_initializer;

}