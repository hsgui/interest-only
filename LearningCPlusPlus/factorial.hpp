#pragma once

namespace TemplatePractice {

	template<int N>
	class Factorial {
	public:
		enum { value = N * Factorial<N - 1>::value };
	};

	/*
		specialization of Factorial
	*/
	template<>
	class Factorial<1> {
	public:
		enum { value = 1 };
	};

}