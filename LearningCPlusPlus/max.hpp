#pragma once

namespace TemplatePractice {

	// function template
	// instantiation: the process of replacing template parameters by concrete types
	//		It results in an instance of a template
	/*
		templates are compiled twice:
			1. without instantiation, the template code itself is checked for correct syntax
			2. At the time of instantiation, the template code is checked to ensure that
				all calls in the template are valid

		function template has two kinds of parameters:
			1. template parameters
			2. call parameters

		template argument deduction on a function template
			the deduction process compares the types of an argument of a function call with
			the corresponding parameterized type of a function template and attempts to conclude
			the correct substitution for one or more of the deduced parameters.

			Each argument-parameter pair is analyzed independently, and if the conclusion differ in the end,
			the deduction process fails, but that doesn't mean "the program is invalid"

		example:
			::max("Apple", "Microsoft") -- compile fail!!
				because "Apple" is type of char const[6], and "microsoft" is type of char const[10]
				No array-to-pointer decay occurs, and therefore T would have to both char[6] and char[10] for deduction to succeed
	*/
	template<typename T>
	inline T const& max(T const& a, T const& b)
	{
		return a < b ? b : a;
	}

}