#pragma once

#include <map>
#include "typeinfowrapper.hpp"

namespace ModernDesign
{
	template<typename IdentifierType, typename ProductType>
	class DefaultFactoryError
	{
	public:
		class Exception : public std::exception
		{
		public:
			Exception(const IdentifierType& p_unknownId)
				: m_unknownId(p_unknownId)
			{}

			virtual const char* what()
			{
				return "Unknow object type passed to Factory.";
			}

			const IdentifierType& GetId()
			{
				return m_unknownId;
			}

		private:
			IdentifieType m_unknownId;
		};

	protected:
		ProductType* OnUnknownType(const IdentifierType& p_unknownId)
		{
			throw Exception(p_unknownId);
		}
	};

	/*
		IdentifierType is the type that represents a type in the hierarchy.
			It has to be an ordered type (able to be stored in a std::map).
			Commonly used identifier types are strings and integral types

		ProductCreator is the callable entity that creates objects. This type must support operator(),
			taking non parameters and returning a pointer to AbstractProduct.
	*/
	template<
		typename AbstractProduct,
		typename IdentifierType,
		typename ProductCreator = AbstractProduct* (*PointerToFunction/* omit this name is fine: 
																	  a pointer to a function taking no parameters and returning a pointer to AbstractProduct*/)(),
		template<typename, typename>
			class FactoryErrorPolicy = DefaultFactoryError
	>
	class Factory
		: public FactoryErrorPolicy<IdentifierType, AbstractProduct>
	{
	public:
		bool Register(const IdentifierType& p_id, ProductCreator p_creator)
		{
			return m_associations.insert(IdToProductMap::value_type(p_id, p_creator)).second;
		}

		bool Unregister(const IdentifierType& p_id)
		{
			return m_associations.erase(p_id) == 1;
		}

		AbstractProduct* CreateObject(const IdentifierType& p_id)
		{
			typename IdToProductMap::const_iterator it = m_associations.find(p_id);
			if (it != m_associations.end())
			{
				return (it->second)();
			}

			return OnUnknownType(p_id);
		}

	private:
		typedef std::map<IdentifierType, AbstractProduct> IdToProductMap;

		IdToProductMap m_associations;
	};

	template<
		typename AbstractProduct,
		typename ProductCreator = 
			AbstractProduct* (*)(AbstractProduct*),
		template<typename, typename>
			class FactoryErrorPolicy = DefaultFactoryError
	>
	class CloneFactory
		: public FactoryErrorPolicy<TypeInfo, AbstractProduct>
	{
	public:
		AbstractProdct* CreateObject(const AbstractProduct* p_model)
		{
			if (p_model == nullptr) return nullptr;

			typename IdToProductMap::iterator it = m_associations.find(typeid(*p_model));
			if (it != m_associations.end())
			{
				return (it->second)(p_model);
			}

			return OnUnknownType(typeid(*p_model));
		}

		bool Register(const TypeInfo& p_typeInfo, ProductCreator p_creator)
		{
			return m_associations.insert(IdToProductMap::value_type(p_typeInfo, p_creator)).second;
		}

		bool Unregister(const TypeInfo& p_typeInfo)
		{
			return m_associations.erase(p_typeInfo) == 1;
		}

	private:
		typedef std::map<TypeInfo, ProductCreator> IdToProductMap;
		IdToProductMap m_associations;
	};
}