#pragma once

#include "lrvalue.hpp"
#include <string>
#include <iostream>

namespace C11Practice
{
	/*
		http://thbecker.net/articles/rvalue_references/section_05.html
		question:
			rvalue reference is a rvalue?

		p_src is a rvalue reference,
		but in the line "C11String temp = p_src", copy constructor will be called

		remember: if rvalue reference has a name, then it's a lvalue;
				  if rvalue reference doesn't have a name, then it's a rvalue

		Why is that?
		we could think as following:
			if the move constructor is called to construct temp object, then the data in p_src willn't be used!
				what will it cause? 
				then the following codes after the construction that use the p_src will lead to unexpected behavior
	*/
	void testRValueAndRValueReference(C11String&& p_src)
	{
		/* 
			http://kuring.me/post/cpp11_right_reference
		*/
		std::cout << "temp object construct start" << std::endl;
		C11String temp = p_src;		// note: copy constructor will be called, instead of move constructor!
		// if we are quite sure p_src will not be used, we could use the following instead:
		// C11String temp = std::move(p_src);
		std::cout << "temp object construct finish: " << temp << std::endl;
	}

	C11String testC11StringValue()
	{
		C11String str("testStringValue");

		// return std::move(str);	return value optimization
		// http://thbecker.net/articles/rvalue_references/section_06.html
		return str;
	}
	void testLRValue()
	{
		C11String a;
		a = testC11StringValue(); // a is a lvalue, testC11StringValue() is a rvalue

		C11String b("testlvalueReference"); // b is  a lvalue
		std::cout << "IsLvalueReference(b): " 
			<< C11String::IsLvalueReference(b) << std::endl;

		std::cout << "IsLvalueReference(testC11StringValue()): "
			<< C11String::IsLvalueReference(testC11StringValue()) << std::endl;

		std::cout << "Start to Test the std::move() " << std::endl;
		C11String a1("aaaa");
		C11String b1("bbbb");
		std::cout << "Before move: a=" << a1
			<< "; b=" << b1 << std::endl;
		C11Practice::Swap(a1, b1);
		std::cout << "After swap is called: a=" << a1
			<< "; b=" << b1 << std::endl;

		C11Practice::SwapWithMove(a1, b1);
		std::cout << "After SwapWithMove is called: a=" << a1
			<< "; b=" << b1 << std::endl;

		std::cout << "start to test rvalue and rvalue reference" << std::endl;
		testRValueAndRValueReference(testC11StringValue());
		std::cout << "finish to test rvalue and rvalue reference" << std::endl;
	}

	void testMove()
	{
		std::string s1 = "hello";
		std::string s2 = "world";

		std::cout << "Before move: " << std::endl;
		std::cout << "s1 = " << s1 << ", s2 = " << s2 << std::endl;
		s2 = std::move(s1);

		std::cout << "After move: " << std::endl;
		std::cout << "s1 = " << s1 << ", s2 = " << s2 << std::endl;
	}

	void testC11Practice()
	{
		testLRValue();

		testMove();
	}
}