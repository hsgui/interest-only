#pragma once

#include "typelist.hpp"
#include "typemanip.hpp"
#include "typetraits.hpp"

namespace HierarchyGenerator {
	using namespace TL;
	using namespace ModernDesign;

	namespace Private {

		/*
			nifty!!

			without this template struct, 
			there is a flaw:
			If the input type list of GenerateScatterHierarchy contains more than one element of the same type
				(e.g. LIPELIST_2(int, int, int))
			GenerateScatterHierarchy will contain multiple bases of the same type and some of them will not be reachable
				(e.g. the first element of Tuple<TYPELIST_3(int, int, int)>
		*/
		template<typename, typename>
		struct ScatterHierarchyTag;
	}

	/*
		template template parameters

		an instantiation of GenerateScatterHierarchy ends up inheriting Unit instantiated with
		every type in the typelist.
	*/
	template<typename TList, template<typename> class Unit> 
	class GenerateScatterHierarchy;

	/*
		Pass an atomic type (non-typelist) to Unit
	*/
	template<typename AtomicType, template<typename> class Unit>
	class GenerateScatterHierarchy : public Unit<AtomicType>
	{
		typedef Unit<AtomicType> LeftBase;

		template<typename T>
		struct Rebind {
			typedef Unit<T> result;
		};
	};

	/*
		Do nothing for NullType
	*/
	template<template<typename> class Unit>
	class GenerateScatterHierarchy<NullListType, Unit>
	{
		template<typename T>
		struct Rebind {
			typedef Unit<T> result;
		};
	};

	/*
		GenerateScatterHierarchy sepcialization, typelist to Unit
	*/
	template<typename Head, typename Tail, template<typename> class Unit>
	class GenerateScatterHierarchy<TypeList<Head, Tail>, Unit>
		: public GenerateScatterHierarchy<Private::ScatterHierarchyTag<Head, Tail>, Unit>
		, public GenerateScatterHierarchy<Tail, Unit>
	{
	public:
		typedef TypeList<Head, Tail> TList;
		// every LeftBase of each GenerateScatterHierarchy is unique
		// typedef GenerateScatterHierarchy<Head, Unit> LeftBase -- will cause problem if there are same types in the input typelist
		typedef GenerateScatterHierarchy<Private::ScatterHierarchyTag<Head, Tail>, Unit> LeftBase;
		typedef GenerateScatterHierarchy<Tail, Unit> RightBase;

		template<typename T> 
		struct Rebind {
			typedef Unit<T> result;
		};
	};

	template<typename Head, typename Tail, template<typename> class Unit>
	class GenerateScatterHierarchy<Private::ScatterHierarchyTag<Head, Tail>, Unit>
		: public GenerateScatterHierarchy<Head, Unit>
	{
	};

	/*
		typename H::template Rebind<T>::result ?
		Accesses a field in an object of a type generated with GenerateScatterHierarchy
		Invocation (obj is an object of a type H generated with GenerateScatterHierarchy
					T is a type in the typelist used to generate H)
			Field<T>(obj);
		returns a reference to Unit<T>, where Unit is the template used to generate H
	*/
	template<typename T, typename H>
	typename H::template Rebind<T>::result&
		Field(H& obj)
	{
		return obj;
	}

	template<typename T>
	struct TupleUnit {
		T value;
		/*
			TupleUnit<T> to T conversion
		*/
		operator T&() { return value; }
		operator const T&() const { return value; }
	};

	template<typename TList>
	struct Tuple: public GenerateScatterHierarchy<TList, TupleUnit>
	{};

	template<typename H, unsigned int I> struct FieldHelper;
	
	template<typename H>
	struct FieldHelper<H, 0>
	{
		typedef typename H::TList::Head ElementType;
		typedef typename H::template Rebind<ElementType>::result UnitType;

		enum
		{
			isTuple = Conversion<UnitType, TupleUnit<ElementType>>::sameType,
			isConst = TypeTraits<H>::isConst
		};

		typedef const typename H::LeftBase ConstLeftBase;
		typedef typename Select<isConst, ConstLeftBase, typename H::LeftBase>::Result LeftBase;

		typedef typename Select<isTuple, ElementType, UnitType>::Result UnqualifiedResultType;
		typedef typename Select<isConst, const UnqualifiedResultType, UnqualifiedResultType>::Result ResultType;

		static ResultType& Do(H& obj) {
			LeftBase& leftBase = obj;
			return leftBase;
		}
	};

	template<typename H, unsigned int I>
	struct FieldHelper {
		typedef typename Nth<typename H::TList, I>::result ElementType;
		typedef typename H::template Rebind<ElementType>::result UnitType;

		enum
		{
			isTuple = Conversion<UnitType, TupleUnit<ElementType>>::sameType,
			isConst = TypeTraits<H>::isConst
		};

		typedef const typename H::RightBase ConstRightBase;
		typedef typename Select<isConst, ConstRightBase, typename H::RightBase>::Result RightBase;

		typedef typename Select<isTuple, ElementType, UnitType>::Result UnqualifiedResultType;
		typedef typename Select<isConst, const UnqualifiedResultType, UnqualifiedResultType>::Result ResultType;

		static ResultType& Do(H& obj) {
			RightBase& rightBase = obj;
			return FieldHelper<RightBase, I - 1>::Do(rightBase);
		}
	};

	/*
		accesses a field in an object of a type generated with GenerateScatterHierarchy
		Invocation (obj is an object of a type H generated with GenerateScatterHierarchy,
					I is the index of a type in the typelist used to generate H):
			Field<I>(obj);
		returns a reference to Unit<T> if H is not Tuple, 
			where Unit is the template used to generate H, and T is the i-th type in the typelist
		returns a reference to T if H is a Tuple
	*/
	template<int I, typename H>
	typename FieldHelper<H, I>::ResultType&
		Field(H& obj)
	{
		return FieldHelper<H, I>::Do(obj);
	}

	/*
		template<AtomicType, typename Base>
		class Unit : public Base
		{
		public: 
			virtual void fun(AtomicType&);
		}
	*/
	template<typename TList, template<typename AtomicType, typename Base> class Unit, typename Root = EmptyType>
	class GenerateLinearHierarchy;

	template<typename Head, typename Tail, template<typename, typename> class Unit, typename Root>
	class GenerateLinearHierarchy<TypeList<Head, Tail>, Unit, Root>
		: public Unit< Head, GenerateLinearHierarchy<Tail, Unit, Root>>
	{
	};

	template<typename AtomicType, template<typename, typename> class Unit, typename Root>
	class GenerateLinearHierarchy<TypeList<AtomicType>, Unit, Root>
		: public Unit < AtomicType, Root>
	{
	};

	template<template<typename, typename> class Unit, typename Root>
	class GenerateLinearHierarchy<NullListType, Unit, Root>
		: public Root
	{
	};

};