#pragma once

#include <iostream>
#include <memory>

namespace C11Practice
{
	/*
		1. http://kuring.me/post/cpp11_right_reference
		2. http://accu.org/index.php/journals/227
		3. http://thbecker.net/articles/rvalue_references/section_02.html

		lvalue: locator value, represents an object that occupies some identifiable location in memory
				and allows us to take the address of that memory location via the & operator

				think of expression as functions and then a lvalue can be thought as the result of a function returning a reference

			i.e. has an address, a variable name
		rvalue: is an expression that is not an lvalue, which doesn't represent an object that occupies some identifiable location in memory
				It's just a temporary value.
			i.e. literal number, 1,
	*/
	class C11String
	{
	public:
		C11String()
		{
			m_data = nullptr;
			m_length = 0;

			std::cout << "Default Constructor is called!" << std::endl;
		}

		C11String(const char* p_data)
		{
			size_t length = strlen(p_data);
			Init(p_data, length);

			std::cout << "Constructor(const char*) is called! this->m_data=" 
				<< (long)m_data << std::endl;
		}

		/*
			copy constructor
			p_src is lvalue reference to C11String
		*/
		C11String(const C11String& p_src)
		{
			Init(p_src.m_data, p_src.m_length);

			std::cout << "Copy Constructor(const C11String&) is called! p_other->m_data=" << (long)p_src.m_data
				<< "; this->m_data=" << (long)this->m_data << std::endl;
		}

		/*
			rvalue reference overload for copy constructor
			move constructor:
				the parameter is not const, and have &&
				Rvalue reference

			p_src is an rvalue reference to C11String

			when it comes to function overload resolution
			lvalues prefer old-style lvalue preferences, whereas rvalues prefer this new rvalue reference
		*/
		C11String(C11String&& p_src)
		{
			std::cout << "Move Constructor(C11String&&) is called! p_src->m_data="
				<< (long)p_src.m_data << std::endl;

			m_data = p_src.m_data;
			m_length = p_src.m_length;

			p_src.m_data = nullptr;
			p_src.m_length = 0;
		}

		/*
			the lvalue reference can only be bound to lvalues but not rvalues
			however, we could bind an rvalue to a const lvalue reference
			e.g.	int& a = 3 error
					const int& a = 3 ok

			if we implement:
				void foo(X&);
				but not void foo(X&&);
			then, foo can be called on lvalues, but not on rvalues, because rvalues can't be bound to non-const lvalue reference

			if we implement:
				void foo(X const&);
				but not void foo(X&&);
			then, foo can be called on lvalues and rvalues. But it's impossible to make it distinguish between lvalues and rvalues

			if we implement:
				void foo(X&&);
				but neither one of void foo(X&) and void foo(X const&);
			then, foo can only be called on rvalues, trying to call it on an lvalue will trigger a compile error
		*/
		C11String& operator=(const C11String& p_src)
		{
			if (this != &p_src)
			{
				if (m_data != nullptr)
				{
					free(m_data);
				}

				Init(p_src.m_data, p_src.m_length);
			}

			std::cout << "Copy operator= is called! p_src->m_data=" << (long)p_src.m_data
				<< "; this->m_data=" << (long)this->m_data << std::endl;

			return *this;
		}

		/*
			move semantics
		*/
		C11String& operator=(C11String&& p_src)
		{
			std::cout << "Move operator= is called! src: "
				<< (long)p_src.m_data << std::endl;

			if (this != &p_src)
			{
				if (m_data != nullptr)
				{
					free(m_data);
				}

				Init(p_src.m_data, p_src.m_length);
				p_src.Reset();
			}

			return *this;
		}

		operator const char* () const
		{
			return m_data;
		}

		static bool IsLvalueReference(const C11String&& p_rvalueReference)
		{
			return false;
		}

		static bool IsLvalueReference(const C11String& p_lvalueReference)
		{
			return true;
		}

		~C11String()
		{
			if (m_data)
			{
				std::cout << "Deconstructor is called! this->m_data="
					<< (long)m_data << std::endl;
				free(m_data);
			}
			else
			{
				std::cout << "Deconstructor is called!" << std::endl;
			}
		}

	private:
		char* m_data;
		size_t m_length;

		void Init(const char* p_data, size_t p_length)
		{
			m_length = p_length;
			m_data = new char[m_length + 1];

			memcpy(m_data, p_data, m_length);
			m_data[m_length] = '\0';
		}

		void Reset()
		{
			m_data = nullptr;
			m_length = 0;
		}
	};

	template<typename T>
	static void Swap(T& a, T&b)
	{
		/*
			a, b are both lvalue reference

			copy constructor and copy operator= are called, 
			instead of move constructor and move operator=
		*/
		T temp(a);
		a = b;
		b = temp;
	}

	template<typename T>
	static void SwapWithMove(T& a, T& b)
	{
		/*
			a, b are both lvalue reference,
			std::move will convert the parameter to rvalue without doing anything else
			question:
				how std::move implement?

			http://thbecker.net/articles/rvalue_references/section_05.html

		*/
		T temp(std::move(a));
		a = std::move(b);
		b = std::move(temp);
	}

	/*
		perfect forwarding
		http://thbecker.net/articles/rvalue_references/section_07.html
	*/
	/*
		the intent of factory1 function template is to forward the argument arg from the factory function to T's constructor.
		Ideally, as far as arg is concerned, everything should behave just as if the factory function wern't there
			and the constructor were called directly in the client code -- perfect forward
	*/
	/*
		problem of factory1: 
			it introduces an extra call by value (copty constructor) if the constructor of T takes its argument by reference
				-- not perfect
	*/
	template<typename T, typename Arg>
	static std::shared_ptr<T> factory1(Arg arg)
	{
		return std::shared_ptr<T>(new T(arg));
	}

	/*
		problem of factory2:
			the factory function can't be called on rvalues if T could construct by rvalue
	*/
	template<typename T, typename Arg>
	static std::shared_ptr<T> factory2(Arg& arg)
	{
		return std::shared_ptr<T>(new T(arg));
	}

	/*
		problem of factory3:
			0. if T's constructor is T(Arg& );
			1. if T's constructor takes serveral arguments, but not all argument are const,
				e.g. T(Arg1 const&, Arg2 &);
				then, all combinations of non-const and const reference for the various arguments
			2. the argument of the constructor of T in the body of factory3 is a lvalue,
				then, move semantics can never happen even if it would without wrapping function

			-- not perfect
	*/
	template<typename T, typename Arg>
	static std::shared_ptr<T> factory3(Arg const& arg)
	{
		return std::shared_ptr<T>(new T(arg));
	}

	/*
		http://thbecker.net/articles/rvalue_references/section_08.html
		reference collapsing rules:
			A& & -> A&
			A& && -> A&
			A&& & -> A&
			A&& && -> A&&

		special template argument deduction rule for function templates that take an argument by rvalue reference to a template argument:
			1. when factory is called on a lvalue of type A, then T resolves to A& and hence, by the reference collapsing rules,
				 the argument type effectively becomes A&;
			2. when factory is called on a rvalue of type A, then, T resolves to A, and hence, the argument type becomes A&&

		note: typename std::remove_reference<S>::type is to declare std::remove_reference<S>::type is a type, 
				otherwise, the compile will assume std::remove_reference<S>::type to be a value, which is the default behaviour
			  remove_reference: http://en.cppreference.com/w/cpp/types/remove_reference

			  possible implementation

			  template<typename T> struct remove_reference		{typedef T type;};
			  template<typename T> struct remove_reference<T&>	{typedef T type;};
			  template<typename T> struct remove_reference<T&&> {typedef T type;};
	*/
	template<typename T>
	typename std::remove_reference<T>::type&&
		move(T&& a) noexcept
	{
		typedef typename std::remove_reference<T>::type&& RvalRef;
		return static_cast<RvalRef>(a);
	}

	template<typename S>
	S&& forward(typename std::remove_reference<S>::type& a) noexcept
	{
		return static_cast<S&&>(a);
	}

	template<typename T, typename Arg>
	static std::shared_ptr<T> factory(Arg&& arg)
	{
		return std::shared_ptr<T>(new T(forward<Arg>(arg)));
	}
}