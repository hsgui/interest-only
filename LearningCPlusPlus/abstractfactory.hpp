#pragma once

#include "typelist.hpp"
#include "typemanip.hpp"

#include <cassert>

namespace ModernDesign
{
	template <typename ConcreteProduct, typename Base>
	class OpNewFactoryUnit : public Base
	{
		typedef typename Base::ProductList BaseProductList;

	protected:
		typedef typename BaseProductList::Tail ProductList;
	public:
		typedef typename BaseProductList::Head AbstractProduct;
		ConcreteProduct* DoCreate(Type2Type<AbstractProduct>)
		{
			return new ConcreteProduct;
		}
	};
}