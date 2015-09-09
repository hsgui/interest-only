#pragma once

#include<typeinfo>
#include<cassert>

namespace ModernDesign
{
	class TypeInfo
	{
	public:
		TypeInfo();
		TypeInfo(const std::type_info&);

		const std::type_info& Get() const;

		bool before(const TypeInfo& rhs) const;
		const char* name() const;

	private:
		const std::type_info* m_typeInfo;
	};

	inline TypeInfo::TypeInfo()
	{
		class Nil {};
		m_typeInfo = &typeid(Nil);
		assert(m_typeInfo);
	}

	inline TypeInfo::TypeInfo(const std::type_info& rhs)
		: m_typeInfo(&rhs)
	{
		assert(m_typeInfo);
	}

	inline bool TypeInfo::before(const TypeInfo& p_rhs) const
	{
		assert(m_typeInfo);
		return m_typeInfo->before(*p_rhs.m_typeInfo) != 0;
	}

	inline const std::type_info& TypeInfo::Get() const
	{
		assert(m_typeInfo);
		return *m_typeInfo;
	}

	inline const char* TypeInfo::name() const
	{
		assert(m_typeInfo);
		return m_typeInfo->name();
	}

	inline bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return (lhs.Get() == rhs.Get()) != 0;
	}

	inline bool operator<(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs.before(rhs);
	}

	inline bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator>(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return rhs < lhs;
	}

	inline bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return !(lhs > rhs);
	}

	inline bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return !(lhs < rhs);
	}

}
