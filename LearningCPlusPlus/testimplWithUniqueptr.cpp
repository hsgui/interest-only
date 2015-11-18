#include "testpimplWithUniqueptr.h"

#include <string>
#include <vector>

namespace LearningCPP
{
    namespace SmartPointers
    {
        std::vector<std::shared_ptr<WidgetWithUniqueptr>> processedWidgets;

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

        void WidgetWithUniqueptr::process()
        {
            // add it to the list of processed Widgets; this is wrong.
            // The std::shared_ptr contructed will create a new control block for the pointed-to Widget (*this)
            // If there are std::shared_ptr outside the member function that already point to that Widget...
            //processedWidgets.emplace_back(this);
            processedWidgets.emplace_back(shared_from_this());
        }
    }
}