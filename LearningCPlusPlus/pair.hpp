#pragma once

namespace TemplatePractice
{
	/*
		default a type/non-type parameter on a previously arrived template paramter.
		But the dependent template parameter must be on the right of which it is dependent upon
		T2 is default to be T1

		Pair<int> and Pair<int, int> are the same
		Pair<> and Pair<int> are the same too
	*/
	template<typename T1 = int, typename T2 = T1>
	class Pair
	{
		/*
			T1 and T2 must have default constructor!
		*/
		Pair() : first(T1()), second(T2())
		{}

		/*
			copy constructor of T1 and T2 must have definition
		*/
		Pair(const Pair<T1, T2>& p_other):
			first(p_other.first),
			second(p_other.second)
		{}

		/*
			comparison operators of T1 and T2 must have definition
		*/
		bool operator== (const Pair<T1, T2>& p_other) const
		{
			return first == p_other.first &&
				second == p_other.second;
		}

		T1 first;
		T2 second;
	};
}