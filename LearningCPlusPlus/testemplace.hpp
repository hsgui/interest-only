#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <deque>
#include <regex>

namespace LearningCPP
{
	namespace EmplaceBack
	{
		class HugeObject
		{
			std::string value;
		public:
			HugeObject(std::string p_value)
				: value(std::move(p_value))
			{
				std::cout << "Construtor HugeObject:" << value << std::endl;
			}

			HugeObject(const HugeObject& other)
				: value(other.value)
			{
				std::cout << "Copy constructor of value:" << value << std::endl;
			}

			HugeObject(HugeObject&& other) // although the argument passed in is a rvalue reference
				: value(std::move(other.value)) // but other has a name, it's a lvalue, and other is cast to a rvalue before it's copied.
			{
				std::cout << "Move constructor of value:" << value << std::endl;
			}

			HugeObject& operator=(const HugeObject& other) = default;

			HugeObject& operator=(HugeObject&& other) = default;

			~HugeObject()
			{
				std::cout << "Destructor HugeObject:" << value << std::endl;
			}
		};

		void testWithoutReserve()
		{
			std::vector<int> numbers{ 0x22, 0x37, 0x59, 0x90 };

			// a strange value is inserted.
			// the bug apears only if a vector has to grow in size.
			// 1. numbers[1] returns a reference
			// 2. vector has to grow the size and a reallocation is happened
			//		which makes the reference numbers[1] invalid.
			// reference operator[](size_type _pos);
			// template <class... Args> void emplace_back(Args&&... args);
			// template <class... Args> void emplace(const_iterator position, Args&&... args);
			numbers.emplace_back(numbers[1]); 
			numbers.push_back(numbers[1]);

			for (auto number : numbers) {
				std::cout << std::hex << number << "; ";
			}

			std::cout << std::endl;
		}

		void testBackInsertIterator()
		{
			std::vector<int> numbers{ 34, 55, 89, 144 };

			std::vector<int> numbers_at_end{ 1,2,3,4 };

			// back_insert_iterator uses push_back method
			std::back_insert_iterator<std::vector<int>> back_iter(numbers_at_end);
			// use generic functions std::begin() and std::end();
			// => 1, 2, 3, 4, 34, 55, 89, 144
			std::copy(std::begin(numbers), std::end(numbers), back_iter);

			for (auto item : numbers_at_end)
			{
				std::cout << item << "; ";
			}
			std::cout << std::endl;

			std::deque<int> numbers_at_front{ 1,2,3,4 };
			std::front_insert_iterator<std::deque<int>> front_iter(numbers_at_front);

			// use specific functions: numbers.begin() and numbers.end();
			std::copy(numbers.begin(), numbers.end(), front_iter);

			// 144, 89, 55, 34, 1, 2, 3, 4
			for (auto item : numbers_at_front)
			{
				std::cout << item << "; ";
			}
			std::cout << std::endl;
		}

		void testMoveIterator()
		{
			std::vector<std::string> first = { "one", "two", "three" };
			std::vector<std::string> second(3);

			using _iter_ = std::vector<std::string>::iterator;

			// template<class Iterator> class move_iterator;
			std::copy(std::move_iterator<_iter_>(first.begin()),
				std::move_iterator<_iter_>(first.end()),
				second.begin());

			// after the move copy, "first" has three empty strings
			std::cout << "after move copy, first=" << std::endl;
			for (auto item : first)
			{
				std::cout << item << ", ";
			}
			std::cout << std::endl;
			std::cout << "after move copy, second=" << std::endl;
			for (auto item : second)
			{
				std::cout << item << ", ";
			}
			std::cout << std::endl;
		}

		/*
		unordered associative collections (std::unordered_map or std::unordered_multiset)
			Rehashing invalidates iterators, changes ordering between elements, and changes which buckets elements appear in.
				but doesn't invalidate pointers or references to elements
		vector's reallocation:
			reallocation invalidates all the references, pointers, and iterators referring to the elements in the sequence
			insert and emplace members shall not affect the validity of iterators and references to the container.
			the erase members shall invalidate only iterators and references to the erased elements.

		swap:
			no swap() function invalidates any references, pointers, or iterators referring to the elements of the containers being swapped.
		*/
		void testSwap()
		{
			std::vector<int> vec_1{ 1,2,3,4,5,6 };
			std::vector<int> vec_2{ 100, 200, 300, 400, 500, 600 };

			// First vector:
			auto it_for_vec_1 = vec_1.begin();
			std::advance(it_for_vec_1, 4);
			assert(*it_for_vec_1 == 5);

			auto it_for_vec_2 = vec_2.begin();
			std::advance(it_for_vec_2, 2);
			assert(*it_for_vec_2 == 300);

			vec_1.swap(vec_2);

			assert(*it_for_vec_1 == 5);
			assert(*it_for_vec_2 = 300);

			for (auto it = vec_1.begin(); it != vec_1.end(); ++it)
			{
				//vec_1.erase(it);// when erase it, then it is invalidated, and can't use to iterate in for loop any more.
			}
		}

		void testEmplaceBack()
		{
			std::vector<HugeObject> objects;

			// avoid reallocations
			objects.reserve(10);

			// construct and move
			/*
			1. A temporary HugeObject object is created from the string literal "I'm a big object". This object has no name, we'll all it temp.
				Construction of temp is the first HugeObject construction. Because it's a temporary object, temp is a rvalue
			2. temp is passed to the rvalue overload for push_back, where it's bound to the rvalue reference parameter other. 
				A copy of other is then constructed in the memory for the std::vector. This construction is what actually creates a new object inside std::vector.
				The constructor that's used to copy other into the std::vector is the move constructor, because other, being an rvalue reference, gets cast to a rvalue before it's copied
			3. immediately after push_back returns, temp is destroyed, thus calling the HugeObject destructor
			*/
			std::cout << "push_back: " << std::endl;
			objects.push_back(HugeObject("I'm a big object 1"));

			// construct in-place
			/*
			We can avoid create a temporary object using emplace_back.
			template <class... Args> void emplace_back(Args&&... args);
			emplace_back uses whatever arguments are passed to it to construct HugeObject directly inside the std::vector. No temporaries are involved.

			Insertion functions (push_back) takes objects to be inserted, 
			while emplacement functions (emplace_back) take constructor arguments for objects to be inserted.
			This difference permits emplacement functions to avoid the creation and destruction of temporary objects.
			*/
			std::cout << "emplace_back: " << std::endl;
			objects.emplace_back("I'm a big object 2");

			/*
			But there are also situations where the insertion functions run faster.
			there are three heuristic that we use emplace_back
			*/
			/*
			1. The value being added is constructed into the container, not assigned.
			we try to insert an object into a location where already occupied by another object.
			They'll move-assign the value into place.
			But move assignment requires an object to move from, and that means that a temporary object will need to be created to be the source of the move.
				So emplace also creates a temporary object, which has no benefit compared with insert.

			Node-based containers virtually always use construction to add new values, and most standard containers are node-based.
			The only ones that aren't node-based containers are std::vector, std::deque, and std::string.
			Within the non-node-based containers (std::vector, std::deque and std::string), 
				we can rely on emplace_back to use construction instead of assignment to get a new value into place.
			*/
			// need construct a temporary object too.
			std::cout << "assigned to the vector" << std::endl;
			objects.emplace(objects.begin(), "I'm a big object 3");

			/*
			2. The argument types being passed differ from the type held by the container.
			emplacement's advantage over insertion generally stems from the fact that its interface doesn't require creation and destruction of a tempoarary object
				when the argument passed are of a type other than that held by the container.
			When an object of type T is to be added to a container<T>, there's no reason to expect emplacement to run faster than insertion. 
				because no temporary needs to be created to satisfy the insertion interface.

			In this example, the argument passed are type of "const char*", which differ from the type "HugeObject" held by the container
			*/
			objects.emplace_back("I'm a big object 4");

			/*
			3. The container is unlikely to reject the new value as a duplicate.
			Because in order to detect whether a value is already in the container, emplacement implementations typically create a node with the new value.
				and compare the value of this node with existing container nodes.
			If the value to be added is already present, the emplacement is aborted and the node is destroyed, meaning that the cost of its construction and destruction was wasted.
			*/

			/*
			reminds two other issues
			1. resource management using emplace_back
			If there is an exception throwed in emplace_back (for example, allocating a list node fails), the raw pointer (new int(3)) is lost.
			In this case, emplacement functions are unlikely to outperform insertion functions when we're adding resource-managing objects to a container.
			*/
			std::vector<std::shared_ptr<int>> shared_vector;
			shared_vector.emplace_back(new int(3)); // not good!

			std::shared_ptr<int> shared_ele(new int(3));
			shared_vector.emplace_back(std::move(shared_ele)); // a better practice.

			/*
			2. emplacement functions's interaction with "explicit" constructors.
			*/
			std::vector<std::regex> regexes;
			/* 
			add nullptr to container of regexes, this shouldn't valid, but it compiles.

			because std::regex objects can be constructed from character strings.
			Creation of a std::regex from a charater string can exact a comparatively large runtime cost.
			So to minimize the likelihood that such an expend will be incurred unintentionally,
				the std::regex constructor taking a "const char*" pointer is "explicit".
				So the following won't compile:
				std::regex r2 = nullptr;
				std::regex r3 = "[a-z]+";

			In this example with emplace_back, we're not claiming to pass a std::regex object.
			Instead, we're passing a "constructor argument" (const char*) for std::regex object.
				That's not considered an implicit conversion request.
			*/
			regexes.emplace_back(nullptr);

			std::regex r1("[A-Z]+");
			std::regex r2(nullptr);
			//std::regex r3 = nullptr;

			/*
			The syntax used to initialize r3 (employing the "=") corresponds to "copy initialization". 
			While the syntax used to initialize r2 (with the "()") yields "direct initialization"

			"copy initialization" is not permitted to use "explicit" constructors
			while "direct initialization" can use "explicit" constructors.
			That's why initialzing r2 compiles, but initializing r3 doesn't

			more generally, emplacement functions use direct initialization, so they may use "explicit" constructors.
			insertion functions employ copy initialization, so they can't use "explicit" constructors.
			*/

			/*
			In this example, we're requesting an implicit conversion from a pointer to a std::regex
				and the explicit of that constructor prevents such conversions.
			*/
			//regexes.push_back(nullptr); // error, won't compile
		}

		void test()
		{
			testEmplaceBack();
			testWithoutReserve();
			testBackInsertIterator();
			testMoveIterator();
			testSwap();
		}
	}
}