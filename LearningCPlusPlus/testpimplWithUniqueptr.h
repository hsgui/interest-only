#pragma once

#include <memory>
namespace LearningCPP
{
	namespace SmartPointers
	{
		class WidgetWithUniqueptr {
		public:
			WidgetWithUniqueptr();
			~WidgetWithUniqueptr(); // declaration only

			WidgetWithUniqueptr(WidgetWithUniqueptr&& rhs);

			WidgetWithUniqueptr(const WidgetWithUniqueptr& rhs);

			WidgetWithUniqueptr& operator=(WidgetWithUniqueptr&& rhs);

			WidgetWithUniqueptr& operator=(const WidgetWithUniqueptr& rhs);

		private:
			struct Impl;
			std::unique_ptr<Impl> pImpl;
		};
	}
}