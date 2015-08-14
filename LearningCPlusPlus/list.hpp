#pragma once

namespace TemplatePractice {

	/*
		convert a value into a type
		Int<1> is a type, Int<2> is another type
	*/
	template<int N> struct Int {
		enum { result = N};
	};

	struct NIL {
		typedef NIL Head;
		typedef NIL Tail;
	};

	/*
		similar with Haskell
		List: [Head, Tail],
			Head is the first element,
			Tail is a NIL or another List
				Tail = NIL | List
	*/
	template<typename H, typename T = NIL> struct List {
		typedef H Head;
		typedef T Tail;
	};

	typedef List<Int<1>, List<Int<2>, List<Int<3> > > > oneTwoThree;

	template <typename LIST> struct Length {
		typedef typename LIST::Tail Tail;
		static const unsigned int result = 1 + Length<Tail>::result;
	};

	template<> struct Length<NIL> {
		static const unsigned int result = 0;
	};

	template<typename LIST, int N> struct Nth {
		typedef typename LIST::Tail Tail;
		typedef typename Nth<Tail, N - 1>::result result;
	};

	template<typename LIST> struct Nth<LIST, 0>{
		typedef typename LIST::Head result;
	};

	template<typename X, typename Y> struct Eq {
		static const bool result = false;
	};

	template<typename X> struct Eq<X, X> {
		static const bool result = true;
	};

	template<typename Ele, typename LIST> struct Include {
		static const bool result = Eq<Ele, typename LIST::Head>::result ||
			Include<Ele, typename LIST::Tail>::result;
	};
	template<typename Ele> struct Include<Ele, NIL> {
		static const bool result = false;
	};

	template<typename Ele, typename LIST = NIL> struct Prepend {
		typedef List<Ele, LIST> result;
	};

	template<typename Ele, typename LIST> struct Append {
	private:
		typedef typename Append<Ele, typename LIST::Tail>::result Next;
	public:
		typedef List<typename LIST::Head, Next> result;
	};

	template<typename Ele> struct Append<Ele, NIL> {
		typedef List<Ele> result;
	};

	template<typename Ele, typename LIST> struct Position {
		static const bool found = Eq<Ele, typename LIST::Head>::result;
		static const int result = (found) ? 1 : 1 + Position<Ele, typename LIST::Tail>::result;
	};

	template<typename Ele> struct Position<Ele, NIL> {
		static const int result = 0;
	};
}