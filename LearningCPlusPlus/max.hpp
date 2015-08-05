#pragma once

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
*/
template<typename T>
inline T const& max(T const& a, T const& b)
{
	return a < b ? b : a;
}
