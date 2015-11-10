#pragma once

#include <memory>
#include <iostream>

namespace LearningCPP
{
	namespace SmartPointers
	{
		class StrBlob;

		class StrBlobPtr
		{
		public:
			StrBlobPtr() : curr(0) {}

			StrBlobPtr(StrBlob& a, size_t sz = 0);

			std::string& deref() const;

			StrBlobPtr& incr();

		private:
			// check returns a shared_ptr to the vector if the check succeeds.
			std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;

			// store a weak_ptr, which means the underlying vector might be destroyed.
			std::weak_ptr<std::vector<std::string>> wptr;

			std::size_t curr; // current position within the array.
		};

		class StrBlob
		{
		public:
			friend class StrBlobPtr;

			typedef std::vector<std::string>::size_type size_type;
			StrBlob();
			StrBlob(std::initializer_list<std::string> il);

			StrBlobPtr begin() { return StrBlobPtr(*this); }
			StrBlobPtr end() { return StrBlobPtr(*this, data->size()); }

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

		StrBlobPtr::StrBlobPtr(StrBlob& a, size_t sz)
			: wptr(a.data)
			, curr(sz)
		{}

		std::shared_ptr<std::vector<std::string>>
			StrBlobPtr::check(std::size_t i, const std::string& msg) const
		{
			auto ret = wptr.lock();
			if (!ret)
			{
				throw std::runtime_error("unbound StrBlobStr");
			}

			if (i >= ret->size())
			{
				throw std::out_of_range(msg);
			}

			return ret;
		}

		std::string& StrBlobPtr::deref() const
		{
			auto p = check(curr, "dereference past end");
			return (*p)[curr];
		}

		StrBlobPtr& StrBlobPtr::incr()
		{
			check(curr, "increment past end of StrBlobPtr");
			++curr;
			return *this;
		}

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

		std::unique_ptr<int> clone(int p)
		{
			return std::unique_ptr<int>(new int(p));
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

			//int i1 = 1;
			//std::shared_ptr<int> p4_1(&i1);
			//p4_1.reset(); // error

			std::unique_ptr<int> u1(new int(3));
			u1 = nullptr;

			std::unique_ptr<std::string> u2(new std::string("hello world"));
			std::unique_ptr<std::string> u3(u2.release());
			std::cout << "u2=" << ((u2 == nullptr) ? std::string("nullptr"):(*u2)) << ", u3=" << *u3 << std::endl;

			std::unique_ptr<std::string> u4(new std::string("another"));
			u3.reset(u4.release());
			std::cout << "u4=" << ((u4) ? (*u4) : std::string("nullptr")) << ", u3=" << *u3 << std::endl;

			std::unique_ptr<int> u5 = clone(5);
			std::cout << *u5 << std::endl;

			std::shared_ptr<int> p5 = std::make_shared<int>(8);
			std::cout << "use_count=" << p5.use_count() << std::endl;
			std::weak_ptr<int> w1(p5);
			std::shared_ptr<int> p6 = p5;
			std::cout << "use_count=" << w1.use_count() << std::endl;

			if (std::shared_ptr<int> np = w1.lock())
			{
				std::cout << "use_count=" << np.use_count() << std::endl;
			}

			int * pia = new int[10];

			delete [] pia;

			std::unique_ptr<int[]> up(new int[10]);
			int* up1 = up.release();
			std::cout << ((up1 == nullptr) ? "nullptr" : "not nullptr") << std::endl;

			int n = 6;
			std::allocator<std::string> alloc;
			auto const p = alloc.allocate(n);
			auto q = p;
			alloc.construct(q++);
			alloc.construct(q++, 10, 'c');
			//alloc.construct(q++, "hi"); // can't point to unconstructed memory

			while (q != p)
			{
				alloc.destroy(--q);
			}

			std::vector<std::string> v1{ "hello", "world" };
			q = std::uninitialized_copy(v1.begin(), v1.end(), q);

			q = std::uninitialized_fill_n(q, n - 2, "me");

			//alloc.deallocate(p, n);

			while (q != p)
			{
				std::cout << *(--q) << std::endl;
				alloc.destroy(q);
			}

			alloc.deallocate(p, n);
		}
	}
}