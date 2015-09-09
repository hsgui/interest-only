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