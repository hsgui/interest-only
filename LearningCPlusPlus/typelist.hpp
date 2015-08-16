#pragma once

#include "modernDesign.hpp"

struct NullListType {
	typedef NullListType Head;
	typedef NullListType Tail;
};

/*
similar with Haskell
List: [Head, Tail],
Head is the first element,
Tail is a NullListType or another List
Tail = NIL | List
*/
template<typename H, typename T = NullListType>
struct TypeList {
	typedef H Head;
	typedef T Tail;
};

#define TYPELIST_1(T1) TypeList<T1>
#define TYPELIST_2(T1, T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) TypeList<T1, TYPELIST_2(T1, T2)>
#define TYPELIST_4(T1, T2, T3, T4) TypeList<T1, TYPELIST_3(T1, T2, T3)>

typedef TYPELIST_4(signed char, short int, int, long int) SignedIntegrals;

/*
	tools for compile-time programming in C++ are:
		1. templates
		2. compile-time integer calculations
		3. type defintions (typedef)
	templates - more specifically, template specialization 
		- provide the equivalent of if statement at compile time
	integer calculations, all compile-time values are immutable, they are constants
	type definitions, can be seen as introducing named type constants

	these compile-time calculations' peculiarities make it fundamentally 
		incompatible with iteration. Iteration contains iterator that 
		keeps changing until some condition is met
	So compile-time calculations are recursive, no iterative
*/
namespace TL {

	template <typename TList> 
	struct Length {
		typedef typename TList::Tail Tail;
		static const unsigned int result = 1 + Length<Tail>::result;
	};

	template<> struct Length<NullListType> {
		static const unsigned int result = 0;
	};

	template<typename TList, int N> struct Nth {
		typedef typename TList::Tail Tail;
		typedef typename Nth<Tail, N - 1>::result result;
	};

	template<typename TList> struct Nth<TList, 0>{
		typedef typename TList::Head result;
	};

	template<typename X, typename Y> struct Eq {
		static const bool result = false;
	};

	template<typename X> struct Eq<X, X> {
		static const bool result = true;
	};

	template<typename Ele, typename TList> struct Include {
		static const bool result = Eq<Ele, typename TList::Head>::result ||
			Include<Ele, typename TList::Tail>::result;
	};
	template<typename Ele> struct Include<Ele, NullListType> {
		static const bool result = false;
	};

	template<typename Ele, typename TList = NullListType> struct Prepend {
		typedef TypeList<Ele, TList> result;
	};

	/*
		these are very similar with the Haskell function definitions!
	*/
	template<typename Ele, typename TList> struct Append;
	template<typename Ele, typename H, typename T> 
	struct Append<Ele, TypeList<H, T>> {
		typedef TypeList<H, typename Append<Ele, T>::result> result;
	};

	template<typename Ele> struct Append<Ele, NullListType> {
		typedef TypeList<Ele> result;
	};

	/*
		Position need pay attention to
	*/
	template<typename Ele, typename TList> struct Position;

	// in the head overload
	template<typename Ele, typename T>
	struct Position<Ele, TypeList<Ele, T>>
	{
		enum { result = 0 };
	};

	// continue to find the tail
	template<typename Ele, typename H, typename T> 
	struct Position<Ele, TypeList<H, T>> {
	private:
		enum{pos = Position<Ele, T>::result};
	public:
		enum { result = (pos == -1) ? -1 : (1 + pos) };
	};

	// not exist overload
	template<typename Ele> struct Position<Ele, NullListType> {
		enum { result = -1 };
	};

	/*
		erase the only first type occurrence from typelist
	*/
	template<typename Ele, typename TList> struct Erase;

	template<typename Ele>
	struct Erase<Ele, NullListType>{
		typedef NullListType result;
	};
	template<typename Ele, typename T>
	struct Erase<Ele, TypeList<Ele, T>> {
		typedef T result;
	};
	template<typename Ele, typename H, typename T>
	struct Erase < Ele, TypeList<H, T>>{
		typedef TypeList<Ele, typename Erase<Ele, T>::result> result;
	};

	/*
		erase all type occurrence of a given type from typelist
	*/
	template<typename Ele, typename TList> struct EraseAll;

	template<typename Ele>
	struct EraseAll<Ele, NullListType> {
		typedef NullListType result;
	};
	template<typename Ele, typename T>
	struct EraseAll<Ele, TypeList<Ele, T>> {
		typedef typename EraseAll<Ele, T>::result result;
	};
	template<typename Ele, typename H, typename T>
	struct EraseAll<Ele, TypeList<H, T>> {
		typedef TypeList < Ele, typename EraseAll<Ele, T>::result > result;
	};

	template<typename TList> struct NoDuplicates;

	template<>
	struct NoDuplicates<NullListType> {
		typedef NullListType result;
	};
	template<typename H, typename T>
	struct NoDuplicates<TypeList<H, T>> {
	private:
		typedef typename NoDuplicates<T>::result NoDuplicatesTail;
		// Erase is enough, because NoDuplicates is called before Erase
		// when Erase is applied, NoDuplicatesTail has already no duplicates
		typedef typename Erase<H, NoDuplicatesTail>::result EraseHead;
	public:
		typedef TypeList<H, EraseHead> result;
	};

	/*
		replace type T with type R for the first occurrence of T
	*/
	template<typename TList, typename T, typename R> struct Replace;
	
	template<typename T, typename R>
	struct Replace<NullListType, T, R> {
		typedef NullListType result;
	};
	template<typename H, typename T, typename R>
	struct Replace < TypeList<H, T>, H, R > {
		typedef TypeList<R, T> result;
	};
	template<typename H, typename T, typename U, typename R>
	struct Replace<TypeList<H, T>, U, R> {
		typedef TypeList<H, typename Replace<T, U, R>::result> result;
	};

	template<typename TList, typename T, typename R> struct ReplaceAll;

	template<typename T, typename R>
	struct ReplaceAll<NullListType, T, R> {
		typedef NullListType result;
	};
	template<typename H, typename T, typename R>
	struct ReplaceAll<TypeList<H, T>, H, R> {
		typedef TypeList<R, typename ReplaceAll<T, H, R>::result> result;
	};
	template<typename H, typename Tail, typename U, typename R>
	struct ReplaceAll<TypeList<H, Tail>, U, R> {
		typedef TypeList<H, typename ReplaceAll<Tail, U, R>::result> result;
	};

	/*
		get the most derived type from Base in the typelist
	*/
	template<typename TList, typename Base> struct MostDerived;

	template<typename Base>
	struct MostDerived<NullListType, Base> {
		typedef Base result;
	};
	template<typename H, typename T, typename Base>
	struct MostDerived<TypeList<H, T>, Base> {
	private:
		typedef typename MostDerived<T, Base>::result MDT;
	public:
		typedef typename ModernDesign::Select<
			SUPERSUBCLASS(MDT, H), H, MDT>::result result;
	};

	/*
		bring the most derived type into the front, push the head base type to tail,
			let other types remain in the same relative positions.
	*/
	template<typename TList> struct DerivedToFront;

	template<> 
	struct DerivedToFront<NullListType>{
		typedef NullListType result;
	};

	template<typename H, typename T>
	struct DerivedToFront<TypeList<H, T>> {
	private:
		typedef typename MostDerived<T, H>::result TMD;
		typedef typename Replace<T, TMD, H>::result L;
	public:
		typedef TypeList<TMD, L> result;
	};
}

typedef TL::Append<SignedIntegrals,
	TYPELIST_3(float, double, long double)>::result SignedTypes;