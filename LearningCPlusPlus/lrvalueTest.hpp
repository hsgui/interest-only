#pragma once

#include "lrvalue.hpp"

namespace C11Practice
{
	C11String testC11StringValue()
	{
		C11String str("testStringValue");

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
	}
}