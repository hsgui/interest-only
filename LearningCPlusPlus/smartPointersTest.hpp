#pragma once

#include <memory>
#include <iostream>

#include "testpimplWithUniqueptr.h"
#include "testingimplWithSharedptr.h"

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

		class Investment {
		public:
			virtual ~Investment()
			{
				std::cout << "destroying Investment..." << std::endl;
			}
		};

		class Stock: public Investment
		{
		public:
			Stock()
			{
				std::cout << "I'm Stock" << std::endl;
			}

			~Stock()
			{
				std::cout << "destroying stock..." << std::endl;
			}
		};

		class Bond : public Investment
		{
		public:
			Bond()
			{
				std::cout << "I'm Bond" << std::endl;
			}

			~Bond()
			{
				std::cout << "destroying Bond..." << std::endl;
			}
		};

		class RealEstate : public Investment
		{
		public:
			RealEstate()
			{
				std::cout << "I'm RealEstate" << std::endl;
			}

			~RealEstate()
			{
				std::cout << "destorying RealEstate..." << std::endl;
			}
		};

		enum InvestmentType
		{
			Stock_Type,
			Bond_Type,
			RealEstate_Type
		};

		template<typename D, typename... Ts>
		std::unique_ptr<Investment, D>
			makeInvestment(InvestmentType type, D del, Ts&&... params)
		{
			std::unique_ptr<Investment, D> pInv(nullptr, del);
			switch (type)
			{
			case Stock_Type:
				pInv.reset(new Stock(std::forward<Ts>(params)...));
				break;
			case Bond_Type:
				pInv.reset(new Bond(std::forward<Ts>(params)...));
				break;
			case RealEstate_Type:
				pInv.reset(new RealEstate(std::forward<Ts>(params)...));
				break;
			default:
				break;
			}

			return pInv;
		}

		void investmentDeleter(Investment* p)
		{
			std::cout << "function pointer" << std::endl;
			delete p;
		}

		void test_unique_ptr()
		{
			auto delFuncObj1 = [](Investment* p)
			{
				std::cout << "call delFuncObj1" << std::endl;
				delete p;
			};

			std::unique_ptr<Investment, decltype(delFuncObj1)> u1 = makeInvestment(RealEstate_Type, delFuncObj1);
			// sizeof(u1) = 4
			std::cout << "sizeof: std::unique_ptr<Investment, decltype(delFuncObj1)>=" << sizeof(u1) << std::endl;
			u1.reset();

			long long count = 0;
			char c1 = 'c';
			auto delFuncObj2 = [&count, &c1](Investment* p)
			{
				++count;
				
				std::cout << "call delFuncObj2, count=" << count << ", c1=" << c1 << std::endl;
				delete p;
			};

			std::unique_ptr<Investment, decltype(delFuncObj2)> u2 = makeInvestment(Bond_Type, delFuncObj2);
			// each capture parameter is a pointer in the lambda function object, sizeof(u2) = 12 (4 + 4*2);
			std::cout << "sizeof: std::unique_ptr<Investment, decltype(delFuncObj2)>=" << sizeof(u2) << ", delFuncObj2=" << sizeof(delFuncObj2) << std::endl;

			//std::unique_ptr<Investment, decltype(delFuncObj1)> u3 = makeInvestment(Stock_Type, delFuncObj2);// decltype(delFuncObj1) is not decltype(delFuncObj2);

			std::unique_ptr<Investment, decltype(investmentDeleter)*> u4 = makeInvestment(Bond_Type, investmentDeleter);
			std::cout << "sizeof: std::unique_ptr<Investment, decltype(investmentDeleter)*>=" << sizeof(u4) << std::endl;

			struct delFuncObj3
			{
				long long i = 0;
				void operator()(Investment* p)
				{
					i++;
					std::cout << "delFuncObj3, i=" << i << std::endl;

					delete p;
				}
			};

			delFuncObj3 obj3;
			std::unique_ptr<Investment, decltype(obj3)> u5 = makeInvestment(Bond_Type, obj3);
			std::cout << "sizeof: std::unique_ptr<Investment, decltype(obj3)>=" << sizeof(u5) << std::endl;

			struct DelFuncObj4
			{
				void operator()(Investment* p)
				{
					std::cout << "DelFuncObj4 is called" << std::endl;
					delete p;
				}
			};

			DelFuncObj4 obj4;
			std::unique_ptr<Investment, decltype(obj4)> u6 = makeInvestment(Bond_Type, obj4);
			std::cout << "sizeof: std::unique_ptr<Investment, decltype(obj4)>=" << sizeof(u6) << std::endl;

			//std::unique_ptr<Investment, decltype(obj4)> u7 = makeInvestment(Bond_Type, delFuncObj1);// decltype(obj4) is not decltype(delFuncObj1)

			std::shared_ptr<Investment> sp1 = std::move(u6);
			std::cout << "sp1.use_count()=" << sp1.use_count() << std::endl;

			// create std::vector of size 10 with all values set to 20.
			auto upv1 = std::make_unique<std::vector<int>>(10, 20);
			std::cout << "std::make_unique<std::vector<int>>(10, 20): size=" << upv1->size() << std::endl;

			auto initList = { 10,20 };
			// create std::vector using std::initializer_list ctor
			auto upv2 = std::make_unique<std::vector<int>>(initList);
			std::cout << "std::make_unique<std::vector<int>>(initList): size=" << upv2->size() << std::endl;
		}

		WidgetWithUniqueptr getWidgetWithUniqueptr()
		{
			WidgetWithUniqueptr w;
			return w;
		}

		void test_pimpl()
		{
			WidgetWithUniqueptr w = getWidgetWithUniqueptr();
			
			std::shared_ptr<WidgetWithUniqueptr> sw = std::make_shared<WidgetWithUniqueptr>();
			sw->process();// this will make the pointed-to Widget destruct twice when not inherit from std::enable_shared_from_this.

			std::shared_ptr<WidgetWithSharedptr> swws = std::make_shared<WidgetWithSharedptr>();
			std::cout << "WidgetWithSharedptr* = " << swws.get() << std::endl;
			std::cout << "sizeof(WidgetWistSharedPtr)=" << sizeof(WidgetWithSharedptr) << std::endl;
			std::cout << "sizeof(std::shared_ptr<WidgetWithSharedptr>) = " << sizeof(swws) << std::endl;
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
			// sizeof(std::unique_ptr<int>) is 4, the same as raw pointer
			std::cout << *u5 << ", sizeof=" << sizeof(u5) << std::endl;

			// sizeof(std::shared_ptr<std::string>(hello))=8
			std::cout << "sizeof(std::shared_ptr<std::string>(hello))=" << sizeof(std::shared_ptr<std::string>("hello")) << std::endl;

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

			test_unique_ptr();

			test_pimpl();
		}
	}
}