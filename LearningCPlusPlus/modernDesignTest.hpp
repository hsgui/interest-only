#pragma once

#include "typemanip.hpp"
#include "hierarchyGenerator.hpp"
#include "typelist.hpp"
#include "functor.hpp"
#include <iostream>
#include <vector>

namespace ModernDesign {

	using namespace HierarchyGenerator;

	template<typename T>
	struct Holder
	{
		T value;
	};

	// define a test functor
	struct TestFunctor1
	{
		void operator()(int i, double d)
		{
			std::cout << "TestFunctor1::operator() ("
				<< i << ", " << d << ") called." << std::endl;
		}
	};

	void TestFunction1(int i, double d)
	{
		std::cout << "TestFunction1("
			<< i << ", " << d << ") called." << std::endl;
	}

	const char* TestFunction2(int i, int j)
	{
		std::cout << "TestFunction2(" << i << ", " << j << ") called" << std::endl;
		return "0";
	}

	class TestMemFun
	{
	public:
		void Test()
		{
			std::cout << "TestMemFun.Test() is called" << std::endl;
		}
	};

	void testConversion()
	{
		std::cout << "SUPERSUBCLASS(int, float): " 
			<< SUPERSUBCLASS(int, float) << std::endl;
		std::cout << "SUPERSUBCLASS(int, char): "
			<< SUPERSUBCLASS(int, char) << std::endl;
		std::cout << "SUPERSUBCLASS(float, int): "
			<< SUPERSUBCLASS(float, int) << std::endl;
		std::cout << "SUPERSUBCLASS(int, unsigned int): " 
			<< SUPERSUBCLASS(int, unsigned int) << std::endl;
		std::cout << "SUPERSUBCLASS(int, int): "
			<< SUPERSUBCLASS(int, int) << std::endl;
	}

	void testGenerateScatterHierarchy()
	{
		typedef GenerateScatterHierarchy<TYPELIST_2(int, double), Holder> TestT1;
		typedef Holder<int> IntHolder;
		typedef Holder<double> DoubleHolder;

		std::cout << "SUPERSUBCLASS(IntHolder, GenerateScatterHierarchy<TYPELIST_2(int, double), Holder>): "
			<< SUPERSUBCLASS(IntHolder, TestT1) << std::endl;
		std::cout << "SUPERSUBCLASS(DoubleHolder, GenerateScatterHierarchy<TYPELIST_2(int, double), Holder>): "
			<< SUPERSUBCLASS(DoubleHolder, TestT1) << std::endl;

		TestT1 testTObj;
		IntHolder i1;
		i1.value = 4;
		(static_cast<Holder<int>&>(testTObj)).value = i1.value;
		(static_cast<Holder<double>&>(testTObj)).value = 1.0f;
		std::cout << "(static_cast<Holder<int>&>(testTObj)).value: "
			<< (static_cast<Holder<int>&>(testTObj)).value << std::endl;

		std::cout << "Field<int>(testTObj).value: "
			<< Field<int>(testTObj).value << std::endl;
		std::cout << "Field<double>(testTObj).value: "
			<< Field<double>(testTObj).value << std::endl;

		typedef Tuple<TYPELIST_3(int, int, int)> Point3D;
		Point3D pt;
		Field<0>(pt) = 3;
		Field<1>(pt) = 4;
		Field<2>(pt) = 5;
		std::cout << "Tuple<TYPELIST_3(int, int, int)>: "
			<< Field<0>(pt) << ", " << Field<1>(pt) << ", " << Field<2>(pt) << std::endl;
	}

	void testTypeTraits()
	{
		const bool iterIsPointer = TypeTraits<std::vector<int>::iterator>::isPointer;
		std::cout << "std::vector<int>::iterator is "
			<< (iterIsPointer ? "fast" : "smart") << std::endl;
	}

	void testFunctor()
	{
		TestFunctor1 f1;
		Functor<void, TYPELIST_2(int, double)> cmd1(f1);
		cmd1(4, 4.5);

		// funtion pointer is also supported
		Functor<void, TYPELIST_2(int, double)> cmd2(&ModernDesign::TestFunction1);
		cmd2(4, 5.6);

		// handling pointers to member functions
		TestMemFun o1;
		Functor<void, NullListType> cmd3(&o1, &TestMemFun::Test);
		cmd3();

		// binding
		Functor<const char*, TYPELIST_2(int, int)> f2(&ModernDesign::TestFunction2);
		Functor<const char*, TYPELIST_1(int)> f3(BindFirst(f2, 10));
		f3(15);

		// chain
		std::cout << "Chain(cmd1, cmd2)(2, 4) is called..." << std::endl;
		Chain(cmd1, cmd2)(2, 4);
	}

	void testModernDesign()
	{
		std::cout << std::endl
			<< "test conversion ..." << std::endl;
		testConversion();

		std::cout << std::endl
			<< "test type traits..." << std::endl;
		testTypeTraits();

		std::cout << std::endl
			<< "test generate scatter hierarchy ..." << std::endl;
		testGenerateScatterHierarchy();

		std::cout << std::endl
			<< "test functor..." << std::endl;
		testFunctor();
	}
}