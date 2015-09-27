#pragma once

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
		typedef typename TypeLhs::Head Head;
		typedef typename TypeLhs::Tail Tail;

	public:
		static ResultType Go(BaseLhs& lhs, BaseRhs& rhs, Executor exec)
		{
			if (Head* pl = dynamic_cast<Head*>(&lhs))
			{
				StaticDispatcher<Executor, BaseLhs, NullListType,
					BaseRhs, TypesRhs, ResultType>::DispatchRhs(*pl, rhs, exec);
			}
			else
			{
				return StaticDispatcher<Executor, BaseLhs, Tail, 
					BaseRhs, TypesRhs, ResultType>::Go(*pl, rhs, exec);
			}
		}

		template<typename SomeLhs>
		static ResultType DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor exec)
		{
			typedef typename TypesRhs::Head Head;
			typedef typename TypesRhs::Tail Tail;

			if (Head* pr = dynamic_cast<Head*>(&rhs))
			{
				enum {swapArgs = symmetric && 
					TL::Position<Head, TypesRhs>::result < TL::Position<SomeLhs, TypesLhs>::result};
				Int2Type<swapArgs> int2Type;

				typedef Private::InvocationTraits<SomeLhs, Head, Executor, ResultType> CallTraits;
				return CallTraits::DoDispatch(lhs, *pr, exec, int2Type);
			}
			else
			{
				return StaticDispatcher<Executor, SomeLhs, NullListType,
					BaseRhs, Tail, ResultType>::DispatchRhs(lhs, rhs, exec);
			}
		}
	};
}