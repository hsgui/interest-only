#pragma once

#include <memory>
#include <vector>
namespace LearningCPP
{
	namespace SmartPointers
	{
		// std::enable_shared_from_this is a base class template. 
		// Its type parameter is always the name of the class being derived.
		// It's The Curiously Recurring Template Pattern (CRTP)
		class WidgetWithUniqueptr 
			: public std::enable_shared_from_this<WidgetWithUniqueptr> 
		{
		public:
			WidgetWithUniqueptr();
			~WidgetWithUniqueptr(); // declaration only

			WidgetWithUniqueptr(WidgetWithUniqueptr&& rhs);

			WidgetWithUniqueptr(const WidgetWithUniqueptr& rhs);

			WidgetWithUniqueptr& operator=(WidgetWithUniqueptr&& rhs);

			WidgetWithUniqueptr& operator=(const WidgetWithUniqueptr& rhs);

			void process();

		private:
			struct Impl;
			std::unique_ptr<Impl> pImpl;
		};
	}
}