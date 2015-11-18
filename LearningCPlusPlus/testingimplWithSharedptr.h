#pragma once

#include <memory>

namespace LearningCPP
{
    namespace SmartPointers
    {
        class WidgetWithSharedptr
        {
        public:
            WidgetWithSharedptr();

        private:
            struct Impl;
            std::shared_ptr<Impl> pImpl;
        };
    }
}