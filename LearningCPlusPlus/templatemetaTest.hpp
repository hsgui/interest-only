#pragma once

#include <iostream>
#include "factorial.hpp"
#include "fraction.hpp"
#include "list.hpp"

namespace TemplatePractice {
	void testFraction()
	{
		typedef Frak<2, 4> two_fourth;
		typedef ScalarMultiplication<3, two_fourth>::result fifth_fourth;
		std::cout << "ScalarMultiplication<3, two_fourth>::result "
			<< fifth_fourth::Num << "/" << fifth_fourth::Den << std::endl;

		typedef Simpl<two_fourth>::result one_two;
		std::cout << "Simpl<two_fourth>::result "
			<< one_two::Num << "/" << one_two::Den << std::endl;

		typedef Sum<two_fourth, one_two>::result one;
		std::cout << "Sum<two_fourth, one_two> "
			<< one::Num << "/" << one::Den << std::endl;

		typedef E<5>::result X;
		std::cout << "e = " << (1.0 * X::Num / X::Den) << std::endl;
		std::cout << "e = " << X::Num << "/" << X::Den << std::endl;

		std::cout << "Length(oneTwoThree): " << Length<oneTwoThree>::result << std::endl;

		std::cout << "Nth(oneTwoThree, 1): " << Nth<oneTwoThree, 1>::result::result << std::endl;

		std::cout << "Include(3, oneTwoThree): " << Include<Int<3>, oneTwoThree>::result << std::endl;
		std::cout << "Include(4, oneTwoThree): " << Include<Int<4>, oneTwoThree>::result << std::endl;

		typedef Append<Int<4>, oneTwoThree>::result T1234;
		std::cout << "Include(4, T1234): " << Include<Int<4>, T1234>::result << std::endl;

		int position = Position<Int<4>, T1234>::result;
		std::cout << "Position<Int<4>, T1234>::result "
			<< position << std::endl;
	}

	void testMetaTemplate()
	{
		testFraction();
	}
}