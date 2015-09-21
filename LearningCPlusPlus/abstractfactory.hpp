#pragma once

#include "typelist.hpp"
#include "typemanip.hpp"
#include "hierarchyGenerator.hpp"

#include <cassert>

namespace ModernDesign
{
	using namespace HierarchyGenerator;

	template<typename T>
	class AbstractFactoryUnit
	{
	public:
		virtual T* DoCreate(Type2Type<T>) = 0;
		virtual ~AbstractFactoryUnit() {}
	};

	/*
		AbstractFactry<TList> inherits from AbstractFactoryUnit<each type in TList>
	*/
	template<typename TList, 
			 template<typename> class Unit = AbstractFactoryUnit>
	class AbstractFactory : public GenerateScatterHierarchy<TList, Unit>
	{
	public:
		typedef TList ProductList;
		template<typename T> T* Create()
		{
			Unit<T>& unit = *this;
			return unit.DoCreate(Type2Type<T>());
		}
	};

	template <typename ConcreteProduct, typename Base>
	class OpNewFactoryUnit : public Base
	{
		typedef typename Base::ProductList BaseProductList;

	protected:
		typedef typename BaseProductList::Tail ProductList;
	public:
		// covariant return types
		// the return value is not AbstractProduct, 
		// instead, ConcreteProduct is used.
		typedef typename BaseProductList::Head AbstractProduct;
		ConcreteProduct* DoCreate(Type2Type<AbstractProduct>)
		{
			return new ConcreteProduct;
		}
	};

	template<typename AbstractFact,
			 template<typename, typename> class Creator = OpNewFactoryUnit,
			 typename TList = typename AbstractFact::ProductList>
	class ConcreteFactory
		: public GenerateLinearHierarchy<
			typename TL::Reverse<TList>::result, Creator, AbstractFact>
	{
	public:
		typedef typename AbstractFact::ProductList ProductList;
		typedef TList ConcreteProductList;
	};
}