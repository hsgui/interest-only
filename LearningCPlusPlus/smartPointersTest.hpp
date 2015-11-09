#pragma once

#include <memory>
#include <iostream>

namespace LearningCPP
{
	namespace SmartPointers
	{
		class StrBlob
		{
		public:
			typedef std::vector<std::string>::size_type size_type;
			StrBlob();
			StrBlob(std::initializer_list<std::string> il);
			size_type size() const { return data->size(); }
			bool empty() const { return data->empty(); }

			void push_back(const std::string& t) { data->push_back(t); }

			void pop_back();

			std::string& front();
			std::string& back();

			std::string& front() const;
			std::string& back() const;

		private:
			void check(size_type i, const std::string& msg) const;
			std::shared_ptr<std::vector<std::string>> data;
		};

		StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}

		StrBlob::StrBlob(std::initializer_list<std::string> il) 
			: data (std::make_shared<std::vector<std::string>>(il)){}

		void StrBlob::check(size_type i, const std::string& msg) const
		{
			if (i >= data->size())
			{
				throw std::out_of_range(msg);
			}
		}

		std::string& StrBlob::front()
		{
			check(0, "front on empty StrBlob");
			return data->front();
		}

		std::string& StrBlob::back()
		{
			check(0, "back on emtpy StrBlob");
			return data->back();
		}

		std::string& StrBlob::front() const
		{
			check(0, "const front on empty StrBlob");
			return data->front();
		}

		std::string& StrBlob::back() const
		{
			check(0, "const back on empty StrBlob");
			return data->back();
		}

		void StrBlob::pop_back()
		{
			check(0, "pop_back on empty StrBlob");
			data->pop_back();
		}

		void test()
		{
			std::shared_ptr<int> p1 = std::make_shared<int>(3);
			std::shared_ptr<std::string> p2 = std::make_shared<std::string>(5, '9');
			// p3 points to an int that is value initialized
			std::shared_ptr<int> p3 = std::make_shared<int>();

			auto p1_1(p1);
			std::cout << p1.use_count() << ", " << p1_1.use_count() << std::endl;
			p1.reset();
			std::cout << p1.use_count() <<", " << p1_1.use_count() << std::endl;
			std::cout << p1.unique() << std::endl;

			std::shared_ptr<int> p4(new int(5));
			std::cout << *p4 << std::endl;

			int i1 = 1;
			std::shared_ptr<int> p4_1(&i1);
			//p4_1.reset(); // error
		}
	}
}