#pragma once

#include <cassert>

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
		}

		P Clone(const P& val)
		{
			++*m_pCount;
			return val;
		}

		bool Release(const P&)
		{
			if (!--*m_pCount)
			{
				delete m_pCount;
				return true;
			}
			return false;
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

	template<
		typename T,
		typename OwnershipPolicy = RefCounted,
		typename ConversionPolicy = DisallowConversion,
		typename CheckingPolicy = AssertCheck,
		typename StoragePolicy = DefaultSPStorage>
	class SmartPtr;

	template<typename T>
	class SmartPtr
	{
	public:
		explicit SmartPtr(T* p_pointee)
			: m_pointee(p_pointee)
		{}

		SmartPtr& operator=(const SmartPtr& p_other);

		~SmartPtr();

		T& opeator*() const
		{
			return *m_pointee;
		}

		T* operator->() const
		{
			return m_pointee;
		}

	private:
		T* m_pointee;
	};
}