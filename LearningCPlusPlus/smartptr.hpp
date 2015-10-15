#pragma once

#include <cassert>
#include <algorithm>

#include "typemanip.hpp"

namespace ModernDesign
{
	/*
		smart pointers have value semantics
			an object with value semantics is an object that you can copy and assign to.
		pointers to allocated objects do not have value semantics
			cannot copy and assign to them at will.
				if assign to them, the allocated objects are lost
				if copy to them,  then two or more pointers pointing to the same object
					must be carefully because of double deletions

		smart pointers offer ownership management (resource management) in addition to pointer-like behavior
		smart pointers can figure out how ownership evolves, and their destructors can 
			release the memory according to a well-defined strategy.

		template matching does not include conversions

		Pointers are two concepts in one:
			iterators and monikers
			The iterative nature of pointers allows to walk through an array of objects using a pointer;
			monikers: inexpensive object representatives that can travel quickly and access the objects in a snap
				the dereferencing operator * and -> support the moniker concept.

		mechanics of operator->:
			the compiler can apply operator-> multiple times to one -> expression, until it reaches a native pointer.

		policy-based class design:
			Each design aspect that doesn't have a unique solution migrates to a policy. 
				Each policy is considered as a separate template parameter.

		the variation points of SmartPtr, each variation point translates into a policy.
		1. Storage policy. By default, the stored type is T*, the pointer type is again T*, and the reference type is T&;
						   The means of destroying the pointee object is the delete operator.
		2. Ownership policy. Popular implementations are deep copy, reference counting, reference linking, and destructive copy.
							 Note that Ownership is not concerned with the mechanic of destruction itself, this is Storage's task.
							 Ownership controls the moment of destruction. and Storage controls how to destroy.
		3. Conversion policy. Some applications need automatic conversion to the underlying raw pointer type; others do not.
		4. Checking policy. The policy controls whether an initializer for SmartPtr is valid 
							and whether a SmartPtr is valid for dereferencing.

		Break the problem into small component classes, called policies. 
		Each policy class deals with exactly one issue.
		Each policy is also a template parameter, which means we can mix and match existing stock policy classes or build our own.
		A rule for all policies is that they must have value semantics, 
			that is, they must define a proper copy constructor and assignment operator.
	*/

	template<typename T>
	class DefaultSPStorage
	{
	protected:
		typedef T* StoredType;		// the type of the m_pointee object
		typedef T* PointerType;		// type returned by operator->
		typedef T& ReferenceType;	// type returned by operator*
	public:
		DefaultSPStorage() : m_pointee(Default())
		{}

		DefaultSPStorage(const StoredType& p) : m_pointee(p)
		{}

		PointerType operator->() const
		{
			return m_pointee;
		}
		ReferenceType operator*() const
		{
			return *m_pointee;
		}

		friend inline PointerType GetImpl(const DefaultSPStorage& sps)
		{
			return sps.m_pointee;
		}

		friend inline const StoredType& GetImplRef(const DefaultSPStorage& sps)
		{
			return sps.m_pointee;
		}

		friend inline StoredType& GetImplRef(DefaultSPStorage& sps)
		{
			return sps.m_pointee;
		}
	protected:
		void Destroy()
		{
			delete m_pointee;
		}
		static StoredType Default()
		{
			return nullptr;
		}
	private:
		StoredType m_pointee;
	};

	template<typename P>
	class RefCounted
	{
	protected:
		RefCounted()
		{
			m_pCount = new unsigned int(1);
			assert(m_pCount != nullptr);
			*m_pCount = 1;
		}

		RefCounted(const RefCounted& rhs)
			: m_pCount(rhs.m_pCount)
		{}

		template<typename P1>
		RefCounted(const RefCounted<P1>& rhs)
			: m_pCount(reinterpret_cast<const RefCounted&>(rhs).m_pCount)
		{}

		P Clone(const P& val)
		{
			++*m_pCount;
			return val;
		}

		bool Release(const P&, bool = false)
		{
			if (!--*m_pCount)
			{
				delete m_pCount;
				return true;
			}
			return false;
		}

		void Swap(RefCounted& rhs)
		{
			std::swap(m_pCount, rhs.m_pCount);
		}

		enum { destructiveCopy = false };
	private:
		unsigned int* m_pCount;
	};

	struct AllowConversion
	{
		enum { allow = true };

		void Swap(AllowConversion&)
		{}
	};

	struct DisallowConversion
	{
		enum { allow = false };

		DisallowConversion()
		{}

		DisallowConversion(const AllowConversion&)
		{}

		void Swap(DisallowConversion&)
		{}
	};

	template<typename S>
	class NoCheck
	{
		NoCheck()
		{}

		template<typename S1>
		NoCheck(const NoCheck<S1>&)
		{}

		static void OnDefault(const S&)
		{}

		static void OnInit(const S&)
		{}

		static void OnDereference(const S&)
		{}

		static void Swap(NoCheck&)
		{}
	};

	template<typename S>
	class AssertCheck
	{
		AssertCheck()
		{}

		template<typename S1>
		AssertCheck(const AssertCheck<S1>&)
		{}

		static void OnDefault(const S&)
		{}

		static void OnInit(const S&)
		{}

		static void OnDereference(S val)
		{
			assert(val);
			(void)val;
		}

		static void Swap(AssertCheck&)
		{}
	};

	template<template<typename> class C>
	struct WrapTemplate
	{
		template<typename T>
		struct In
		{
			typedef C<T> type;
		};

		template<typename T>
		struct PointerType : private C < T >
		{
			typedef typename C<T>::PointerType type;
		};

		template<typename T>
		struct StoredType : private C < T >
		{
			typedef typename C<T>::StoredType type;
		};
	};

	template<
		typename T,
		typename OwnershipPolicy = WrapTemplate<RefCounted>,
		typename ConversionPolicy = DisallowConversion,
		typename CheckingPolicy = WrapTemplate<AssertCheck>,
		typename StoragePolicy = WrapTemplate<DefaultSPStorage>>
	class SmartPtr;

	template<
		typename T,
		typename OwnershipPolicy,
		typename ConversionPolicy,
		typename CheckingPolicy,
		typename StoragePolicy>
	class SmartPtr
		: public StoragePolicy::In<T>::type
		, public OwnershipPolicy::In<typename StoragePolicy::template PointerType<T>::type>::type
		, public CheckingPolicy::In<typename StoragePolicy::template StoredType<T>::type>::type
		, public ConversionPolicy
	{
		typedef typename StoragePolicy::template In<T>::type SP;
		typedef typename OwnershipPolicy::template In<typename SP::PointerType>::type OP;
		typedef typename CheckingPolicy::template In<typename SP::StoredType>::type KP;
		typedef typename ConversionPolicy CP;

		enum {CP_destructiveCopy = OP::destructiveCopy};
		enum {CP_allow = CP::allow};

	public:
		typedef typename SP::PointerType PointerType;
		typedef typename SP::StoredType StoredType;
		typedef typename SP::ReferenceType ReferenceType;

		typedef typename Select<
			OP_destructiveCopy,
			SmartPtr,
			const SmartPtr>::Result CopyArg;

	private:
		void OnKPReject()
		{
			if (OP::Release(GetImpl(*static_cast<SP*>(this)), true)
			{
			}
		}

		class SmartPtrGuard
		{
		public:
			typedef void(SmartPtr::*action_t) ();

			SmartPtrGuard(SmartPtr& sptr, action_t action)
				: m_sptr(sptr)
				, m_action(action)
				, m_guard(true)
			{}

			void Dismiss()
			{
				m_guard = false;
			}

			~SmartPtrGuard()
			{
				if (m_guard)
				{
					(m_sptr.*m_action)();
				}
			}

		private:
			SmartPtrGuard(const SmartPtrGuard&);
			SmartPtrGuard& operator=(const SmartPtrGuard&);

		private:
			SmartPtr& m_sptr;
			action_t m_action;
			bool m_guard;
		};

	public:
		SmartPtr()
		{
			SmartPtrGuard kpGuard(*this, &SmartPtr::OnKPReject);
			KP::OnDefault(GetImpl(*this));
			kpGuard.Dismiss();
		}

		SmartPtr(const StoredType& p)
		{
			SmartPtrGuard kpGuard(*this, &SmartPtr::OnKPReject);
			KP::OnInit(GetImpl(*this));
			kpGuard.Dismiss();
		}

		SmartPtr(CopyArg& rhs)
		{
			GetImplRef(*this) = OP::Clone(GetImplRef(rhs));
		}

		SmartPtr& operator=(CopyArg& rhs)
		{
			SmartPtr temp(rhs);
			temp.Swap(*this);
			return *this;
		}

		void Swap(SmartPtr& rhs)
		{
			OP::Swap(rhs);
		}
	};
}