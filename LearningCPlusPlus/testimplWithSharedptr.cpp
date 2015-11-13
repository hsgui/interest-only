#include "testingimplWithSharedptr.h"

#include <string>
#include <vector>

namespace LearningCPP
{
	namespace SmartPointers
	{
		struct WidgetWithSharedptr::Impl {
			std::string name;
			std::vector<double> data;
		};

		WidgetWithSharedptr::WidgetWithSharedptr()
			: pImpl(std::make_shared<Impl>())
		{}
	}
}