#pragma once

namespace ModernDesign {
	template<typename T>
	class TypeTraits {
	private:
		/*
		whether U is a pointer type
		*/
		template<typename U> struct PointerTraits {
			enum { result = false };
			typedef NullType PointeeType;
		};

		template<typename U> struct PointerTraits<U*> {
			enum { result = true };
			typedef U PointeeType;
		};

		/*
		stripping the const qualifiers
		*/
		template<typename T> struct UnConst {
			typedef T Result;
			enum { isConst = 0 };
		};
		template<typename T> struct UnConst<const T> {
			typedef T Result;
			enum { isConst = 1 };
		};
		template<typename T> struct UnConst<const T&> {
			typedef T& Result;
			enum { isConst = 1 };
		};

	public:
		enum { isPointer = PointerTraits<T>::result };
		typedef typename PointerTraits<T>::PointeeType PointeeType;

		// stripping the qualifiers
		typedef typename UnConst<T>::Result NonConstType;

		enum { isConst = UnConst<T>::isConst };
	};
}