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
}