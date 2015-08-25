#pragma once

#include <new>
#include <algorithm>
#include <cassert>

namespace ModernDesign
{
	typedef void(__cdecl *atexit_pfn_t)();

	namespace Private
	{
		class LifetimeTracker
		{
		public:
			LifetimeTracker(unsigned int p_longevity)
				: m_longevity(p_longevity)
			{}

			virtual ~LifetimeTracker() = 0;

			static bool Compare(const LifetimeTracker* lhs,
				const LifetimeTracker* rhs)
			{
				return lhs->m_longevity > rhs->m_longevity;
			}

		private:
			unsigned int m_longevity;
		};

		inline LifetimeTracker::~LifetimeTracker() {}

		typedef LifetimeTracker** TrackerArray;

		extern TrackerArray m_trackerArray = nullptr;
		extern unsigned int m_elements = 0;

		// helper destroyer function
		template <typename T>
		struct Deleter
		{
			static void Delete(T* p_pObj)
			{
				delete p_pObj;
			}
		};

		// Concrete lifetime tracker for objects of type T
		template<typename T, typename Destroyer>
		class ConcreteLifetimeTracker : public LifetimeTracker
		{
		public:
			ConcreteLifetimeTracker(T* p_pTrackedObj,
				unsigned int p_longevity,
				Destroyer p_destroyer)
				: LifetimeTracker(p_longevity)
				, m_pTrackedObj(p_pTrackedObj)
				, m_destroyer(p_destroyer)
			{}

			~ConcreteLifetimeTracker()
			{
				m_destoryer(m_pTrackedObj);
			}

		private:
			T* m_pTrackedObj;
			Destroyer m_destroyer;
		};

		void AtExitFn();
	}

	template<typename T, typename Destroyer>
	void SetLongevity(T* p_pDynObject,
		unsigned int p_longevity,
		Destroyer p_destroy = Private::Deleter<T>::Delete)
	{
		using namespace Private;

		TrackerArray pNewArray = static_cast<TrackerArray>(
			std::realloc(m_trackerArray, sizeof(T)* (m_elements + 1)));

		if (!pNewArray)
		{
			throw std::bad_alloc();
		}

		m_trackerArray = pNewArray;

		LifetimeTracker* tracker = new ConcreteLifetimeTracker<T, Destroyer>(
			p_pDynObject, p_longevity, p_destroy);

		TrackerArray index = std::upper_bound(
			m_trackerArray, 
			m_trackerArray + m_elements, 
			p_longevity, 
			LifetimeTracker::Compare);

		std::copy_backward(
			index, 
			m_trackerArray + m_elements, 
			m_trackerArray + m_elements + 1);

		*index = tracker;
		m_elements++;
		std::atexit(AtExitFn);
	}

	static void __cdecl AtExitFn()
	{
		using namespace Private;

		assert(m_elements > 0 && m_trackerArray != nullptr);

		// Pick the element at the top of the stack
		LifetimeTracker* pTop = m_trackerArray[m_elements - 1];
		// Remove that object off the stack
		// Don't check errors-realloc with less memory
		// can't fall
		m_trackerArray = static_cast<TrackerArray>(
			std::realloc(m_trackerArray, sizeof(*m_trackerArray)*(--m_elements)));

		// must pop the stack before deleting the top object because destroying some object
		// may create another one, thus pushing another element onto the stack.
		delete pTop;
	}

	template<typename T,
		template<typename> class CreationPolicy,
		template<typename> class LifetimePolicy,
		template<typename> class ThreadingModel>
	class SingletonHolder
	{
		typedef typename ThreadingModel<T*>::VolatileType PtrInstanceType;
	public:
		static T& Instance()
		{
			if (!m_pInstance)
			{
				MakeInstance();
			}

			return *m_pInstance;
		}
	private:
		static void MakeInstance()
		{
			typename ThreadingModel<SingletonHolder>::Lock guard;
			(void)guard;
			if (!m_pInstance)
			{
				if (m_destroyed)
				{
					LifetimePolicy<T>::OnDeadReference();
					m_destroyed = false;
				}

				m_pInstance = CreationPolicy<T>::Create();
				LifetimePolicy<T>::ScheduleDestruction(m_pInstance, &DestroySingleton);
			}
		}

		static void DestroySingleton()
		{
			assert(!m_destroyed);
			CreationPolicy<T>::Destory(m_pInstance);
			m_pInstance = nullptr;
			m_destroyed = true;
		}
		// protection
		SingletonHolder();

		static bool m_destroyed;
		static PtrInstanceType m_pInstance;
	};
}