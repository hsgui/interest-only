#pragma once

namespace ModernDesign
{
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