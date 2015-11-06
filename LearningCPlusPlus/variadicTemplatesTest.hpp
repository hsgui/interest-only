#pragma once

#include <iostream>
#include <ostream>
#include <sstream>

namespace LearningCPP
{
	namespace VariadicTemplate
	{
		template<typename T, typename... Args>
		void foo(const T& t, const Args& ... rest)
		{
			std::cout << "sizeof...(Args) = " << sizeof...(Args) << std::endl;
			std::cout << "sizeof...(rest) = " << sizeof...(rest) << std::endl;
		}

		template<typename T>
		std::ostream& iprint(std::ostream& os, const T& t)
		{
			return os << t << std::endl;
		}

		template<typename T, typename... Args>
		std::ostream& iprint(std::ostream& os, const T& t, const Args& ... rest)
		{
			os << t << ", ";
			return iprint(os, rest...);
		}

		template<typename T>
		struct iremove_reference
		{
			typedef T type;
		};

		template<typename T>
		struct iremove_reference<T&>
		{
			typedef T type;
		};

		template<typename T>
		struct iremove_reference<T&&>
		{
			typedef T type;
		};

		template<typename T>
		size_t countOccurrences(std::vector<T>& p_values, const T& v)
		{
			std::cout << "original template is called" << std::endl;
			size_t occurrence = 0;
			for (const T& element : p_values)
			{
				if (element == v) occurrence++;
			}

			return occurrence;
		}

		template<>
		size_t countOccurrences(std::vector<const char*>& p_values, const char* const& v)
		{
			std::cout << "specialization of const char* is called" << std::endl;
			size_t occurrences = 0;
			for (const char* element : p_values)
			{
				if (std::strcmp(element, v) == 0) occurrences++;
			}
			return occurrences;
		}

		template<typename T>
		void printVector(std::vector<T>& p_values)
		{
			typedef typename std::vector<T>::size_type SizeType;
			SizeType index = SizeType();
			for (; index < p_values.size(); index++)
			{
				std::cout << p_values[index] << "," << std::endl;
			}
		}

		template<typename T>
		void constConversion(T, T)
		{
			std::cout << "constConversion(T, T) is called" << std::endl;
		}

		template<typename T>
		void referenceConversion(const T&, const T&)
		{
			std::cout << "referenceConversion(const T&, const T&) is called" << std::endl;
		}

		template<typename T>
		void typeDeduction1(T&)
		{
			std::cout << "typeDeduction1()" << std::endl;
		}

		template<typename T>
		void typeDeduction2(const T&)
		{
			std::cout << "typeDeduction2()" << std::endl;
		}

		template<typename T>
		void typeDeduction3(T&&)
		{
			std::cout << "typeDeduction3()" << std::endl;
		}

		template<typename T>
		void typeDeduction4(const T&&)
		{
			std::cout << "typeDeduction4()" << std::endl;
		}

		template<typename S>
		S&& iforward(typename std::remove_reference<S>::type& a) noexcept
		{
			return static_cast<S&&>(a);
		}

		void testFunc(int a, int& b)
		{
			std::cout << a << ", " << ++b << std::endl;
		}

		void testFunc2(int&& a, int& b)
		{
			std::cout << a << ", " << b << std::endl;
		}

		// just forward the t1 and t2 to f, with reverse order.
		template<typename F, typename T1, typename T2>
		void flip1(F f, T1 t1, T2 t2)
		{
			f(t2, t1);
		}

		template<typename F, typename T1, typename T2>
		void flip2(F f, T1&& t1, T2&& t2)
		{
			f(t2, t1);
		}

		template<typename F, typename T1, typename T2>
		void flip(F f, T1&& t1, T2&& t2)
		{
			return f(iforward<T2>(t2), iforward<T1>(t1));
		}

		template<typename T> std::string idebug(const T& t)
		{
			std::ostringstream ret;
			ret << t;
			return ret.str();
		}

		template<typename T> std::string idebug(T* p)
		{
			std::ostringstream ret;
			ret << "pointer: " << p;
			if (p)
			{
				ret << " " << idebug(*p);
			}
			else
			{
				ret << " null pointer";
			}

			return ret.str();
		}

		std::string idebug(const std::string& s)
		{
			return '"' + s + '"';
		}

		std::string idebug(const char* p)
		{
			// if the declaration of idebug(const std::string&) is not in scope
			// the return will call idebug(const T&) with T instantiated to string
			return idebug(std::string(p));
		}

		void test()
		{
			foo(23, 1.1, "hello", 0xde);
			iprint(std::cout, 23, 1.1, "hello", 0xde);

			iremove_reference<decltype(42)>::type i = 0;
			std::cout << "iremove_reference<decltype(42)>::type i = " << i << std::endl;

			iremove_reference<decltype(std::move(i))>::type j = 0;
			std::cout << "iremove_reference<decltype(std::move(i))>::type j = " << j << std::endl;

			std::vector<std::string> values1 = { "hello", "world", "hello" };
			std::cout << "occurrences = " << countOccurrences(values1, std::string("hello")) << std::endl;

			std::vector<const char*> values2 = { "hello", "world", "hello" };
			const char* value = "hello";
			std::cout << "occurrences = " << countOccurrences(values2, value) << std::endl;

			std::cout << "printVector(values2) = " << std::endl;
			printVector(values2);

			std::string s1("value1");
			const std::string s2("value2");
			const std::string s3("value3");
			std::cout << "call constConversion(s1, s2)" << std::endl;
			constConversion(s1, s2);	// calls constConversion(std::string, std::string), const is ignored.
			constConversion(s2, s3);	// still calls constConversion(std::string, std::string), const is ignored.
			referenceConversion(s1, s2);// referenceConversion(const std::string&, const std::string&); nonconst object reference to const ojbect reference

			int a[10], b[43];
			constConversion(a, b);		// calls constConversion(char*, char*), T is not a reference type. The array is converted to a pointer
			// referenceConversion(a, b), const T& is a reference type, no conversion. referenceConversion(int[10], int[43]) doesn't match

			long l1 = 1;
			int i2 = 2;
			referenceConversion<long>(l1, i2); // explicit arguments of function template
			//referenceConversion(l1, i2); // referenceConversion(long, int) doesn't match

			void(*fp1)(const int&, const int&);
			fp1 = referenceConversion;
			fp1(1, 2);

			int i3 = 2;
			const int ci1 = 1;
			typeDeduction1(i3);
			typeDeduction1(ci1);
			//typeDeduction1(3);

			typeDeduction2(i3);
			typeDeduction2(ci1);
			typeDeduction2(3);

			typeDeduction3(i3);// typeDeduction3<int&>(int&)
			typeDeduction3(ci1);//typeDeduction3<const int&>(const int&)
			typeDeduction3(4);// typeDeduction3<int>(int&&)
			typeDeduction3(i3 * ci1); // typeDeduction3<int>(int&&)

			typeDeduction4(4);// typeDeduction4<int>(int&&)
			//typeDeduction4(i3);
			//typeDeduction4(ci1);

			int&& i5 = std::move(i3);
			std::cout << "std::move(i3) = " << i5 << std::endl;
			i5 = static_cast<int&&>(i3); // explicitly convert a lvalue to a rvalue reference
			std::cout << "explicitly convert lvalue to rvalue reference: " << i5 << std::endl;

			int i4 = 1;
			testFunc(34, i4); // change i4 from 1 to 2
			std::cout << "i4=" << i4 << std::endl;
			flip1(testFunc, i4, 23); // leave i4 unchanged
			std::cout << "i4=" << i4 << std::endl;
			flip2(testFunc, i4, 35); // i4 is changed
			std::cout << "i4=" << i4 << std::endl;

			//flip2(testFunc2, i4, 32); // cannot convert int to int&&
			flip(testFunc2, i4, 23);

			std::string s2("hello");
			std::cout << idebug(s2) << std::endl;
			std::cout << idebug(&s2) << std::endl;
			std::cout << idebug("hello world") << std::endl;
		}
	}	
}