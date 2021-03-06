#pragma once

#include <utility>
#include <map>
#include "typelist.hpp"
#include "typeinfowrapper.hpp"
#include "functor.hpp"

namespace ModernDesign
{
    namespace Private
    {
        template<
            typename SomeLhs,
            typename SomeRhs,
            typename Executor,
            typename ResultType>
        struct InvocationTraits
        {
            static ResultType
                DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, Int2Type<false>)
            {
                return exec.Fire(lhs, rhs);
            }

            static ResultType
                DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, Int2Type<true>)
            {
                return exec.Fire(rhs, lhs);
            }
        };
    }

    template<
        typename Executor,
        typename BaseLhs,
        typename TypesLhs,
        bool symmetric = true,
        typename BaseRhs = BaseLhs,
        typename TypesRhs = TypesLhs,
        typename ResultType = void>
    class StaticDispatcher
    {
        template<typename SomeLhs>
        static ResultType
            DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor& exec, NullListType)
        {
            return exec.OnError(lhs, rhs);
        }

        template<typename Head, typename Tail, typename SomeLhs>
        static ResultType
            DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor& exec, TypeList<Head, Tail>)
        {
            if (Head* pr = dynamic_cast<Head*>(&rhs))
            {
                enum {
                    swapArgs = symmetric &&
                    TL::Position<Head, TypesRhs>::result < TL::Position<SomeLhs, TypesLhs>::result
                };
                Int2Type<swapArgs> int2Type;

                typedef Private::InvocationTraits<SomeLhs, Head, Executor, ResultType> CallTraits;
                return CallTraits::DoDispatch(lhs, *pr, exec, int2Type);
            }
            return DispatchRhs(lhs, rhs, exec, Tail());
        }

        static ResultType
            DispatchLhs(BaseLhs& lhs, BaseRhs& rhs, Executor& exec, NullListType)
        {
            return exec.OnError(lhs, rhs);
        }

        template<typename Head, typename Tail>
        static ResultType
            DispatchLhs(BaseLhs& lhs, BaseRhs& rhs, Executor& exec, TypeList<Head, Tail>)
        {
            if (Head* pl = dynamic_cast<Head*>(&lhs))
            {
                return DispatchRhs(*pl, rhs, exec, TypesRhs());
            }
            return DispatchLhs(lhs, rhs, exec, Tail());
        }

    public:
        static ResultType Go(BaseLhs& lhs, BaseRhs& rhs, Executor exec)
        {
            return DispatchLhs(lhs, rhs, exec, TypesLhs());
        }
    };

    template<
        typename BaseLhs,
        typename BaseRhs = BaseLhs,
        typename ResultType = void,
        typename CallbackType = ResultType (*) (BaseLhs&, BaseRhs&)>
    class BasicDispatcher
    {
        typedef std::pair<TypeInfo, TypeInfo> KeyType;
        typedef CallbackType MappedType;
        typedef std::map<KeyType, MappedType> MapType;
        MapType m_callbackMap;

        void DoAdd(TypeInfo lhs, TypeInfo rhs, CallbackType func);
        bool DoRemove(TypeInfo lhs, TypeInfo rhs);

    public:
        template<typename SomeLhs, typename SomeRhs>
        void Add(CallbackType func)
        {
            DoAdd(typeid(SomeLhs), typeid(SomeRhs), func);
        }

        template<typename SomeLhs, typename SomeRhs>
        bool Remove()
        {
            return DoRemoe(typeid(SomeLhs), typeid(SomeRhs));
        }

        ResultType Go(BaseLhs& lhs, BaseRhs& rhs);
    };

    template<typename BaseLhs, typename BaseRhs, typename ResultType, typename CallbackType>
    void BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>
        ::DoAdd(TypeInfo lhs, TypeInfo rhs, CallbackType func)
    {
        m_callbackMap[KeyType(lhs, rhs)] = func;
    }

    template<typename BaseLhs, typename BaseRhs, typename ResultType, typename CallbackType>
    bool BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>
        ::DoRemove(TypeInfo lhs, TypeInfo rhs)
    {
        return m_callbackMap.erase(KeyType(lhs, rhs)) == 1;
    }

    template<typename BaseLhs, typename BaseRhs, typename ResultType, typename CallbackType>
    ResultType BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>
        ::Go(BaseLhs& lhs, BaseRhs& rhs)
    {
        typename MapType::key_type key(typeid(lhs), typeid(rhs));
        typename MapType::iterator it = m_callbackMap.find(key);
        if (it == m_callbackMap.end())
        {
            throw std::runtime_error("Function not found!");
        }

        return (it->second)(lhs, rhs);
    }

    template<typename To, typename From>
    struct StaticCaster
    {
        static To& Cast(From& obj)
        {
            return static_cast<To&>(obj);
        }
    };

    template<typename To, typename From>
    struct DynamicCaster
    {
        static To& Cast(From& obj)
        {
            return dynamic_cast<To&>(obj);
        }
    };

    template<typename BaseLhs, typename BaseRhs = BaseLhs, typename ResultType = void,
        template<typename, typename> class CastingPolicy = DynamicCaster,
        template<typename, typename, typename, typename> class DispatcherBackend = BasicDispatcher>
    class FnDispatcher
    {
        DispatcherBackend<BaseLhs, BaseRhs, ResultType,
            ResultType(*)(BaseLhs&, BaseRhs&)> m_backend;
    public:
        template<typename ConcreteLhs, typename ConcreteRhs,
            ResultType (*callback)(ConcreteLhs&, ConcreteRhs&)>
            void Add()
        {
            struct Local
            {
                static ResultType Trampoline(BaseLhs& lhs, BaseRhs& rhs)
                {
                    return callback(CastingPolicy<ConcreteLhs, BaseLhs>(lhs),
                        CastingPolicy<ConcreteRhs, BaseRhs>(rhs));
                }
            };

            m_backend.Add<ConcreteLhs, ConcreteRhs>(&Local::Trampoline);
        }

        template<typename ConcreteLhs, typename ConcreteRhs,
            ResultType (*callback)(ConcreteLhs&, ConcreteRhs&),
            bool symmetric>
            void Add()
        {
            struct Local
            {
                static ResultType Trampoline(BaseLhs& lhs, BaseRhs& rhs)
                {
                    return callback(CastingPolicy<ConcreteLhs, BaseLhs>(lhs),
                        CastingPolicy<ConcreteRhs, BaseRhs>(rhs));
                }

                static ResultType TrampolineR(BaseLhs& lhs, BaseRhs& rhs)
                {
                    return callback(CastingPolicy<ConcreteRhs, BaseRhs>(rhs),
                        CastingPolicy<ConcreteLhs, BaseLhs>(lhs));
                }
            };
            m_backend.Add<ConcreteLhs, ConcreteRhs>(&Local::Trampoline);
            if (symmetric)
            {
                m_backend.Add<ConcreteRhs, ConcreteLhs>(&Local::TrampolineR);
            }
        }
    };

    template<typename BaseLhs, typename BaseRhs = BaseLhs, typename ResultType = void,
        template<typename, typename> class CastingPolicy = DynamicCaster,
        template<typename, typename, typename, typename> class DispatcherBackend = BasicDispatcher>
    class FunctorDispatcher
    {
        typedef TYPELIST_2(BaseLhs&, BaseRhs&) ArgsList;
        typedef Functor<ResultType, ArgsList> FunctorType;
        typedef DispatcherBackend<BaseLhs, BaseRhs, ResultType, FunctorType> BackendType;

        BackendType m_backend;
    public:
        template<typename SomeLhs, typename SomeRhs, typename Fun>
        void Add(const Fun& fun)
        {
            typedef FunctorImpl<ResultType, ArgsList> FunctorImplType;
            class Adapter : public FunctorImplType
            {
                Fun m_fun;
                virtual ResultType operator() (BaseLhs& lhs, BaseRhs& rhs)
                {
                    return m_fun(CastingPolicy<SomeLhs, BaseLhs>(lhs), 
                        CastingPolicy<SomeRhs, BaseLhs>(rhs));
                }

                virtual FunctorImplType* Clone()
                {
                    return new Adapter();
                }
            public:
                Adapter(const Fun& fun) : m_fun(fun) {}
            };

            m_backend.Add<SomeLhs, SomeRhs>(FunctorType(Adapter(fun)));
        }
    };
}