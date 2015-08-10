#pragma once

#include <iostream>

namespace C11Practice
{
	/*
		lvalue: locator value, represents an object that occupies some identifiable location in memory
			i.e. has an address, a variable name
		rvalue: not a lvalue, which doesn't represent an object that occupies some identifiable location in memory
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
				Lvalue reference
		*/
		C11String(const C11String& p_src)
		{
			Init(p_src.m_data, p_src.m_length);

			std::cout << "Copy Constructor(const C11String&) is called! p_other->m_data=" << (long)p_src.m_data
				<< "; this->m_data=" << (long)this->m_data << std::endl;
		}

		/*
			move constructor:
				the parameter is not const, and have &&
				Rvalue reference
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

			std::cout << "Copy Assignment is called! p_src->m_data=" << (long)p_src.m_data
				<< "; this->m_data=" << (long)this->m_data << std::endl;

			return *this;
		}

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

}