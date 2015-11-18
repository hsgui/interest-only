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

    template<typename ConcreteProduct, typename Base>
    class PrototypeFactoryUnit : public Base
    {
        typedef typename Base::ProductList BaseProductList;
    protected:
        typedef typename BaseProductList::Tail ProductList;
    public:
        typedef typename BaseProductList::Head AbstractProduct;

        PrototypeFactoryUnit(AbstractProduct* p = nullptr)
            : m_prototype(p)
        {}

        friend void DoGetPrototype(const PrototypeFactoryUnit& me,
            AbstractProduct*& prototype)
        {
            prototype = me.m_prototype;
        }

        friend void DoSetPrototype(PrototypeFactoryUnit& me,
            AbstractProduct* prototype)
        {
            me.m_prototype = prototype;
        }

        template<typename U>
        void GetPrototype(U*& p)
        {
            return DoGetPrototype(*this, p);
        }

        template<typename U>
        void SetProtoype(U* p)
        {
            return DoSetPrototype(*this, p);
        }

        AbstractProduct* DoCreate(Type2Type<AbstractProduct>)
        {
            assert(m_prototype);
            return m_prototype->Clone();
        }

    private:
        AbstractProduct* m_prototype;
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