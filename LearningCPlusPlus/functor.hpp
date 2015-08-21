#pragma once

#include "typelist.hpp"

namespace ModernDesign
{

	using namespace TL;
	/*
		Command Pattern:
			encapsulate a request in an object. 
			A command object is a piece of work that is stored away from its actual executor
		two important aspects of the command pattern:
		1. Interface separation. The invoker is isolated from the receiver
		2. Time separation. Command stores a ready-to-go processing request that's to be started later

		From an implementation standpoint, two kinds of concrete Command classes can be identified.
		1. forwarding commands
			Simply delegate the work to the receiver. All the Command do is call a member function for a Receiver object.
		2. active commands
			Might call member functions of other objects, but they also embed logic that's beyond simple forwarding.

		Forwarding commands act much like pointers to functions and their C++ colleagues - functors, call them:
			generalized functors

		entities that support the function-call operator:
		1. c-like functions
		2. c-like pointers to functions
		3. References to functions (which essentially act like const pointers to functions)
		4. functors, that is, objects that define an operator()
		5. the result of applying operator.* or operator->* 
			having a pointer to a member function in the right-hand side of the expression

		the objects that support operator() are known as callable entities
	*/

	/*
		FunctorImpl defines a polymorphic interface that abstracts a function call.
		For each number of paramters, a FunctorImpl explicit specialization is defined.
		Each specialization defines a pure virtual operator() for the appropriate number and types of parameters
	*/
	template<typename R, typename TList> class FunctorImpl;

	template<typename R>
	class FunctorImpl<R, NullListType>
	{
	public:
		virtual R operator() () = 0;
		virtual FunctorImpl* Clone() const = 0;
		virtual ~FunctorImpl() {}
	};

	template<typename R, typename P1>
	class FunctorImpl<R, TYPELIST_1(P1)>
	{
	public:
		virtual R operator() (P1) = 0;
		virtual FunctorImpl* Clone() const = 0;
		virtual ~FunctorImpl() {}
	};

	template<typename R, typename P1, typename P2>
	class FunctorImpl<R, TYPELIST_2(P1, P2)>
	{
	public:
		virtual R operator() (P1, P2) = 0;
		virtual FunctorImpl* Clone() const = 0;
		virtual ~FunctorImpl() {}
	};

	/*
		FunctorHandler looks much like Functor itself.
		The main difference is that the functor is stored by value, not by pointer.

		To avoid defining too many template parameters for FunctorHandler, 
		make the Functor instantiation itself a template parameter
		the inner typedefs in the Functor instantiation are used by FunctorHandler

		implicit conversion for arugments and for the return type are also supported in FunctorHandler
	*/
	template<typename ParentFunctor, typename Fun>
	class FunctorHandler 
		: public FunctorImpl<
			typename ParentFunctor::ResultType, 
			typename ParentFunctor::ParamList>
	{
	public:
		typedef typename ParentFunctor::ResultType ResultType;

		/*
			if Fun is type of Functor, it will call Functor constructor!
		*/
		FunctorHandler(const Fun& p_fun) : m_fun(p_fun) {}

		FunctorHandler* Clone() const
		{
			return new FunctorHandler(*this);
		}

		ResultType operator() ()
		{
			return m_fun();
		}

		ResultType operator() (typename ParentFunctor::Param1 p1)
		{
			return m_fun(p1);
		}

		ResultType operator() (typename ParentFunctor::Param1 p1, 
			typename ParentFunctor::Param2 p2)
		{
			return m_fun(p1, p2);
		}

	private:
		Fun m_fun;
	};

	template<typename ParentFunctor, 
		typename PointerToObj,
		typename PointerToMemFn>
	class MemFunHandler
		:public FunctorImpl<
		typename ParentFunctor::ResultType,
		typename ParentFunctor::ParamList>
	{
	public:
		typedef typename ParentFunctor::ResultType ResultType;

		MemFunHandler(const PointerToObj& p_pObj, 
			PointerToMemFn p_pMemFn)
			: m_pObj(p_pObj)
			, m_pMemFn(p_pMemFn)
		{}

		MemFunHandler* Clone() const
		{
			return new MemFunHandler(*this);
		}

		ResultType operator() ()
		{
			return ((*m_pObj).*m_pMemFn)();
		}

		ResultType operator() (typename ParentFunctor::Param1 p1)
		{
			return ((*m_pObj).*m_pMemFn)(p1);
		}

		ResultType operator() (typename ParentFunctor::Param1 p1,
			typename ParentFunctor::Param2 p2)
		{
			return ((*m_pObj).*m_pMemFn)(p1, p2);
		}

	private:
		PointerToObj m_pObj;
		PointerToMemFn m_pMemFn;
	};

	/*
		functors are loosely defined as instances of classes that define operator()

		Functor can be thought of as a computation, and its arguments as the environment 
			necessary to perform that computation
		Functor delays the computation by storing pointers to functions and pointers to methods
		However, Functor stores only the computation, but nothing about the environment of that computation.
	*/
	template<typename R, typename TList = NullListType>
	class Functor
	{
	public:
		typedef FunctorImpl<R, TList> Impl;
		typedef R ResultType;
		typedef TList ParamList;

		template<typename R1, typename TList1>
		struct RebindParamList
		{
			typedef Functor<R1, TList1> Result;
		};

		typedef typename TypeAtNonStrict<ParamList, 0, EmptyType>::Result Param1;
		typedef typename TypeAtNonStrict<ParamList, 1, EmptyType>::Result Param2;
		typedef typename TypeAtNonStrict<ParamList, 2, EmptyType>::Result Param3;

		Functor()
			: m_spImpl(nullptr)
		{}

		/*
			functor or pointer to function is constructed

			note:
			m_spImpl can't be type of FunctorImpl
			If m_spImpl is the type of FunctorImpl, then
				1. we should define constructor Functor(const Functor&),
					otherwise, we could lead to stack overflow error
				2. the compile can't see the constructor Functor(const Functor&)
					when the template version exits!
			we need a help type.
		*/
		template<typename Fun>
		Functor ( const Fun& fun)
			: m_spImpl (new FunctorHandler<Functor, Fun>(fun))
		{}

		/*
			member function is constructed
		*/
		template<typename PtrObj, typename MemFn>
		Functor(const PtrObj& p_pObj, MemFn p_memFn)
			: m_spImpl(new MemFunHandler<Functor, PtrObj, MemFn>(p_pObj, p_memFn))
		{}

		Functor& operator=(const Functor& rhs)
		{
			Functor copy(rhs);
			// swap auto_ptrs by hand
			Impl* p = m_spImpl.m_spIml.release();
			m_spImpl.m_spIml.reset(copy.m_spIml.m_spImpl.release());
			copy.m_spImpl.m_spIml.reset(p);

			return *this;
		}

		Functor(std::auto_ptr<Impl> p_spImpl)
			: m_spImpl(p_spImpl)
		{}

		/*
			for a given Funtor instantiation, only one operator() is correct
			All others constitute compile-time errors
			This is because each FunctorImpl specialization defines only one operator(),
				not a bunch of them as Functor does.
			This trick relies on the fact that C++ does not instantiate member functions for templates
				until they are actually used.
			Until you call the wrong operator(), the compiler doesn't complain.
			If an overload of operator() that doesn't make sense is called, 
				the compiler tries to generate the body of operator() and discovers the mismatch.
		*/
		ResultType operator() ()
		{
			return (*m_spImpl)();
		}

		ResultType operator() (Param1 p1)
		{
			return (*m_spImpl)(p1);
		}

		ResultType operator() (Param1 p1, Param2 p2)
		{
			return (*m_spImpl)(p1, p2);
		}

	private:
		struct Helper
		{
			Helper()
				: m_spImpl(nullptr)
			{}

			/*
				coyy constructor
				the Clone should be called, 
				otherwise there are two pointers pointing the same memory
			*/
			Helper(const Helper& rhs)
				: m_spImpl(rhs.m_spImpl.get()->Clone())
			{}

			explicit Helper(std::auto_ptr<Impl> p_spImpl)
				: m_spImpl(p_spImpl)
			{}

			template<typename U>
			explicit Helper(U *ptr)
				: m_spImpl(ptr)
			{}

			Impl& operator*() const
			{
				return *m_spImpl;
			}
		public:
			std::auto_ptr<Impl> m_spImpl;
		};
		Helper m_spImpl;
	};

	/*
		Binding
		With binding, not only store callable entities, but also part (or all) of their arguments.
		Binding allows Functor to store part of the environment together with the computation
			and to reduce progressively the environment neccessary at invocation time.
	*/

	namespace Private
	{
		template<typename Fctor>
		struct BinderFirstTraits
		{
		private:
			typedef typename Fctor::ParamList TList;
		public:
			typedef typename Erase<typename Nth<TList, 0>::result, TList>::result ParamList;
			typedef typename Fctor::template RebindParamList<typename Fctor::ResultType, ParamList>::Result BoundFunctorType;

			typedef typename BoundFunctorType::Impl Impl;
		};
	}

	template<typename OriginalFunctor>
	class BinderFirst
		: public Private::BinderFirstTraits<OriginalFunctor>::Impl
	{
		typedef typename OriginalFunctor::ResultType ResultType;

		typedef typename OriginalFunctor::Param1 BoundType;

		typedef typename OriginalFunctor::Param2 Param1;
		typedef typename OriginalFunctor::Param3 Param2;

	public:
		BinderFirst(const OriginalFunctor& p_fun, BoundType p_boundValue)
			: m_fun(p_fun)
			, m_boundValue(p_boundValue)
		{}

		BinderFirst* Clone() const
		{
			return new BinderFirst(*this);
		}

		ResultType operator() ()
		{
			return m_fun(m_boundValue);
		}

		ResultType operator() (Param1 p1)
		{
			return m_fun(m_boundValue, p1);
		}

		ResultType operator() (Param1 p1, Param2 p2)
		{
			return m_fun(m_boundValue, p1, p2);
		}

	private:
		OriginalFunctor m_fun;
		BoundType m_boundValue;
	};

	template<typename Fctor>
	typename Private::BinderFirstTraits<Fctor>::BoundFunctorType
		BindFirst(
			const Fctor& p_fun, 
			typename Fctor::Param1 p_bound)
	{
		typedef typename Private::BinderFirstTraits<Fctor>::BoundFunctorType Outgoing;

		std::auto_ptr<typename Outgoing::Impl> apParam(new BinderFirst<Fctor>(p_fun, p_bound));

		return Outgoing(apParam);
	}


	/*
		Chain functors together
		each functor shares the same parameter type
	*/
	template<typename Fctor1, typename Fctor2>
	class Chainer : public Fctor2::Impl
	{
		typedef Fctor2 Base;
	public:
		typedef typename Base::ResultType ResultType;

		typedef typename Base::Param1 Param1;
		typedef typename Base::Param2 Param2;

		Chainer(const Fctor1& p_functor1, const Fctor2& p_functor2)
			: m_functor1(p_functor1)
			, m_functor2(p_functor2)
		{}

		Chainer* Clone() const
		{
			return new Chainer(*this);
		}

		ResultType operator() ()
		{
			m_functor1();
			return m_functor2();
		}

		ResultType operator() (Param1 p1)
		{
			m_functor1(p1);
			return m_functor2(p1);
		}

		ResultType operator() (Param1 p1, Param2 p2)
		{
			m_functor1(p1, p2);
			return m_functor2(p1, p2);
		}

	private:
		Fctor1 m_functor1;
		Fctor2 m_functor2;
	};

	template<typename Fctor1, typename Fctor2>
	Fctor2 Chain(
		const Fctor1& p_functor1,
		const Fctor2& p_functor2)
	{
		std::auto_ptr<typename Fctor2::Impl> apParam(new Chainer<Fctor1, Fctor2>(p_functor1, p_functor2));

		return Fctor2(apParam);
	}
}