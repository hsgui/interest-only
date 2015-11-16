#pragma once

#include <iostream>
#include <vector>
#include <functional>

namespace LearningCPP
{
	namespace Lambda
	{
		using FilterContainer = std::vector<std::function<bool(int)>>;
		FilterContainer filters;

		int computeDivisor()
		{
			return rand();
		}

		void addDivisorFilter()
		{
			int divisor = computeDivisor();
			filters.emplace_back([&](int value) {return value % divisor == 0; });

			filters.emplace_back([&divisor](int value) {return value % divisor == 0; });
		}

		class Widget
		{
		public:
			Widget()
				: divisor(0)
			{}

			Widget(int p_divisor)
				: divisor(p_divisor)
			{}

			void addFilter() const;

			void addFilter1() const;

			void addFilter2() const;

			void addFilter3() const;

			void addFilter4() const;

			bool isValidated() const
			{
				return true;
			}

		private:
			int divisor;
		};

		void Widget::addFilter() const
		{
			// no divisor is available -- filters.emplace_back([divisor](int value)
			
			// implicit use of a raw pointer: this
			// Inside any Widget member function, for example, compilers internally replace uses divisor with this->divisor.
			// In the version of Widget::addFilter with a defalut by-value capture.
			// what's being captured is the Widget's this pointer, not divisor!
			//		so if this pointer is destroyed, a dangling pointer will occur.
			// compilers treat the code as if it had been written as addFilter1()
			// we can know that the viability of the closures arising from this lambda is tied to the lifetime of the Widget whose this pointer they contain a copy of.
			filters.emplace_back([=](int value) {std::cout << "Widget::addFilter(): divisor=" << divisor << std::endl; return value % divisor == 0; });
		}

		void Widget::addFilter1() const
		{
			auto currentObjectPtr = this;
			filters.emplace_back(
				[currentObjectPtr](int value)
			{
				return value % (currentObjectPtr->divisor) == 0;
			});
		}

		void Widget::addFilter2() const
		{
			auto divisorCopy = divisor;
			filters.emplace_back(
				[divisorCopy](int value)
			{
				return value % divisorCopy == 0;
			});
		}

		void Widget::addFilter3() const
		{
			// C++ 14
			// copy divisor to closure.
			// generalized lambda capture.
			// there's no such thing as a default capture mode for a generalized lambda capture.
			filters.emplace_back(
				[divisor = divisor](int value)
			{
				return value % divisor == 0;
			});
		}

		// captures nothing. so no copy capture is done.
		// divisor is static.
		// divisor is not self-contained.
		// This lambda doesn't use any non-static local variables. So nothing is captured.
		// practically speaking, this lambda captures divisor by reference, a direct contradiction to what the default by-value capture clause seems to imply.
		// If we stay away from default by-value capture clauses, we eliminate the risk of code being misread in this way.
		void Widget::addFilter4() const
		{
			static auto divisor = 4;
			filters.emplace_back(
				[=](int value)
			{
				return value % divisor == 0; // divisor is not captured!!!
			});

			++divisor; // modify divisor.
		}

		// after this function return, Widget is destroyed.
		// filters now holds dangling pointer!
		// because the captured is this, not divisor
		// after Widget is destroyed, this is dangling.
		// to solve this problem, using Widget::addFilter2();
		void doSomeWork()
		{
			auto pw = std::make_unique<Widget>(5);
			pw->addFilter();
		}

		// init capture is C++14 feature
		// move capture in C++14, which doesn't contain in C++11
		void testInitCapture()
		{
			auto upw = std::make_unique<Widget>();
			auto func = [&] {return upw->isValidated(); };
			func();

			// using init capture makes it possible to specify:
			// 1. the name of a data member in the closure class generated from the lambda
			// 2. an expression to initialize that data member
			// To the left of the "=" is the name of the data member in the closure class we're specifying
			// To the right of the "=" is the initializing expression.
			// The scope on the left of the "=" is different from the scope on the right

			// The scope on the left is that of the closure class.
			// The scope on the right is the same as where the lambda is being defined.
			auto func1 = [upw = std::move(upw)]
			{
				return upw->isValidated();
			};

			// in c++11, it's not possible to capture the result of an expression.
			// another name for init capture is generalized lambda capture.
			auto func2 = [upw = std::make_unique<Widget>()]
			{
				upw->isValidated();
			};

			// this is the same with func2.
			// std::bind produces function objects like lambda expression.
			//	let's call that function object to be bind objects
			// the first argument to std::bind is a callable object,
			//		Subsequent arguments represent values to be passed to that object
			// A bind object contains copies of all the arguments passed to std::bind
			// For each lvalue argument, the corresponding object in the bind object is copy constructed
			// for each rvalue, it's move constructed.
			// In this example, the second argument is an rvalue.
			// so std::make_unique<Widget> is move constructed into the bind object.
			// This move construction is the crux of move capture emulation.
			// when a bind object is called, the arguments it stores are passed to the callable object originally passed to std::bind.
			// In this example, that means when func3 is called, the move-constructed copy of std::make_unique<Widget>() is passed
			//		as an argument to the lambda that was passed to std::bind.
			// This parameter in the lambda is a lvaue reference to the copy in the bind object.
			//	(It's not a rvalue reference, because although the expression used to initialize the copy in the bind object is a rvalue,
			//		the copy in the bind object itself is a lvalue)
			// Use of unique_ptr inside the lambda will thus operate on the move-constructed copy of the unique_ptr inside the bind object.
			auto func3 = std::bind(
				[](const std::unique_ptr<Widget>& p)
					{return p->isValidated(); },
				std::make_unique<Widget>());
			func3();

			// by default, the operator() member function inside the closure class generated from a lambda is const
			// That has the effect of rendering all data members in the closure const within the body of the lambda.
			// the move-constructed copy of unique_ptr inside the bind object is not const. 
			// So to prevent that copy of unique_ptr from being modified inside the lambda, the lambda's parameter is declared reference-to-const
			// If the lambda were declared mutalbe, operator() in its closure class would not be declared const.
			// And it would be appropriate to omit const in the lambda's parameter declaration:
			auto func4 = std::bind(
				[](std::unique_ptr<Widget>& p) mutable
					{return p->isValidated(); },
				std::make_unique<Widget>());
			func4();
		}

		void test()
		{
			long long x = 4;
			// capture by copy
			auto c1 = [x](int y) {return x*y > 55; };
			// the type of c1 is a function class - closure type.
			// c1 itself is a closure.
			// sizeof(c1) == 8
			std::cout << "typename(c1)="<< typeid(c1).name() <<", sizeof(c1)=" << sizeof(c1) << std::endl;
			std::cout << "c1(18)=" << c1(18) << std::endl;

			// closure is copied
			auto c2 = c1;
			std::cout << "c2(18)=" << c2(18) << std::endl;

			addDivisorFilter();
			std::cout << "filters[0](12) = " << filters[0](12) << std::endl;

			Widget w(3);
			w.addFilter();
			std::cout << "filters[2](12) = " << filters[2](12) << std::endl;

			testInitCapture();
		}
	}
}