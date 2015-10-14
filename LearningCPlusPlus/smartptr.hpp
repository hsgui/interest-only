#pragma once

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