#pragma once

#include <future>
#include <iostream>

namespace LearningCPP
{
    namespace Concurrency
    {
        int doAsyncWork1()
        {
            std::cout << "run doAsyncWork1..." << std::endl;
            int sum = 0;
            for (int i = 0; i < 20; ++i)
            {
                sum += i;
            }
            return sum;
        }

        void testAsync()
        {
            auto fut1 = std::async(doAsyncWork1);

            auto fut2 = std::async(std::launch::async | std::launch::deferred, doAsyncWork1);
        }
    }
}