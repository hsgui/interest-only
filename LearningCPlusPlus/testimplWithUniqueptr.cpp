#include "testpimplWithUniqueptr.h"

#include <string>
#include <vector>

namespace LearningCPP
{
	namespace SmartPointers
	{
		struct WidgetWithUniqueptr::Impl {
			std::string name;
			std::vector<double> data;
		};

		WidgetWithUniqueptr::WidgetWithUniqueptr()
			: pImpl(std::make_unique<Impl>())
		{}

		WidgetWithUniqueptr::~WidgetWithUniqueptr() = default;

		WidgetWithUniqueptr::WidgetWithUniqueptr(WidgetWithUniqueptr&& rhs) = default;

		WidgetWithUniqueptr::WidgetWithUniqueptr(const WidgetWithUniqueptr& rhs)
			: pImpl(std::make_unique<Impl>(*rhs.pImpl)) // copy ctor
		{}

		WidgetWithUniqueptr& WidgetWithUniqueptr::operator=(WidgetWithUniqueptr&& rhs) = default;

		WidgetWithUniqueptr& WidgetWithUniqueptr::operator=(const WidgetWithUniqueptr& rhs) // copy operator=
		{
			*pImpl = *rhs.pImpl;
			return *this;
		}
	}
}