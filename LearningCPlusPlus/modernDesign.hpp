#pragma once

namespace ModernDesign {

	/*
		mapping integral constants to types

		generates a distinct type for each distinct constant integer value
		This is because, different template instantiations are different types,
		In addition, the value that generates the type is "saved" in the enume member value

		Int2Type<0> type is different from Int2Type<1> type

		typically, when following both conditions are satisfied, Int2Type will be used:
		1. need to call one of several different functions, depending on a compile-time constant
		2. need to do this dispatch at a compile time

		Int2Type makes the function to be overloaded
	*/
	template<int v>
	struct Int2Type {
		enum {value = v};
	};

	/*
		type-to-type mapping
	*/
	template<typename U>
	struct Type2Type {
		typedef U OriginialType;
	};

	/*
		type selection
	*/
	template<bool flag, typename T, typename F>
	struct Select {
		typedef T Result;
	};

	template<typename T, typename F>
	struct Select<false, T, F> {
		typedef F Result;
	};

	/*
		NullType is a class that serves as a null maker for types
	*/
	class NullType {};

	struct EmptyType {};

	template<typename T>
	class TypeTraits{
	private:
		/*
			whether U is a pointer type
		*/
		template<typename U> struct PointerTraits {
			enum{result = false};
			typedef NullType PointeeType;
		};

		template<typename U> struct PointerTraits<U*> {
			enum{result = true};
			typedef U PointeeType;
		};

		/*
			stripping the qualifiers
		*/
		template<typename T> struct UnConst {
			typedef T Result;
		};
		template<typename T> struct UnConst<const T> {
			typedef T Result;
		};

	public:
		enum {isPointer = PointerTraits<T>::result};
		typedef typename PointerTraits<T>::PointeeType PointeeType;

		// stripping the qualifiers
		typedef typename UnConst<T>::Result NonConstType;
	};

	template<typename T, typename U> class Conversion;

	/*
		very nifty!!

		sizeof: return the expression's size without actually evaluating that expression at runtime
			that means sizeof is aware of overloading, template initialization, conversion rules.
		in fact, sizeof conceals a complete facility for deducing the type of an expression.
		eventually, sizeof throws away the expression, and returns only the size of its result.

		two overload functions are provided: Test
		1. one accepts the type that could convert to U,
			Small Test(U);
		2. the other accepts just about anything else
			Big Test(...);

		although the two overloaded functions and MakeT are not implemented, it doesn't matter
		because, sizeof does not evaluate its argument.

		We call the overloaded function :Test" with a temporary of type T, T is the type whose
			convertibility to U we want to determine.
		If the function that accepts a U (Small Test(U)) gets called, we know that T is convertible to U;
		If the fallback function (Big Test(...)) gets called, then T is not convertible to U.
		To detect which function gets called, we arrange the two overloadded functions to 
			return types of different sizes, and then we discriminate with sizeof.
	*/
	template<typename T, typename U>
	class Conversion {
	private:
		typedef char Small;
		class Big { char dummy[2]; };
		static Small Test(U);
		static Big Test(...);
		static T MakeT();
	public:
		enum { sameType = false, 
			exists = sizeof(Test(MakeT())) == sizeof(Small) };
	};
	template<typename T>
	class Conversion<T, T> {
	public:
		enum { sameType = true, exists = true };
	};
}

#define SUPERSUBCLASS(T, U) \
	(ModernDesign::Conversion<const U*, const T*>::exists && \
	!ModernDesign::Conversion<const T*, const void*>::sameType)