#pragma once

#include <future>
#include <iostream>
#include <chrono>

namespace LearningCPP
{
    namespace Concurrency
    {
        using namespace std::literals;

        template<typename F, typename... Ts>
        inline
            std::future<typename std::result_of<F(Ts...)>::type>
            reallyAsyc(F&& f, Ts&&... params)
        {
            // always use std::launch::async launch policy.
            return std::async(std::launch::async,
                std::forward<F>(f),
                std::forward<Ts>(params)...);
        }

        int doAsyncWork1()
        {
            std::cout << "run doAsyncWork1..." << std::endl;
            int sum = 0;
            for (int i = 0; i < 20; ++i)
            {
                sum += i;
            }
            std::this_thread::sleep_for(1s);

            return sum;
        }

        void testAsync()
        {
            // the default launch policy is std::launch::deferred | std::launch::async
            // which permits both asynchronous and synchronous task execution.
            auto fut1 = std::async(doAsyncWork1);

            while (fut1.wait_for(100ms) != std::future_status::ready)
            {
                std::cout << "fut1.wait_for is not ready" << std::endl;
            }

            int count = 0;
            auto fut2 = std::async(std::launch::deferred, doAsyncWork1);
            // fut2.wait_for will always return std::future_status::deferred
            while (fut2.wait_for(100ms) != std::future_status::ready)
            {
                count++;
                if (count > 20)
                {
                    std::cout << "fut2 runs too long!" << std::endl;
                    break;
                }
                std::cout << "fut2.wait_for is not ready" << std::endl;
            }

            auto fut3 = std::async(std::launch::deferred, doAsyncWork1);
            if (fut3.wait_for(0s) == std::future_status::deferred)
            {
                std::cout << "fut3 is deferred..." << std::endl;
            }
            else
            {
                while (fut3.wait_for(100ms) != std::future_status::ready)
                {
                    std::cout << "fut3.wait_for is not ready" << std::endl;
                }
                int sum = fut3.get();
                std::cout << "sum=" << sum << std::endl;
            }

            auto fut4 = std::async(std::launch::async, doAsyncWork1);
            int sum = fut4.get();
            std::cout << "fut4.get() = " << sum << std::endl;

            auto fut5 = reallyAsyc(doAsyncWork1);
            sum = fut5.get();
            std::cout << "fut5.get() = " << sum << std::endl;
        }

        void test()
        {
            testAsync();
        }
    }
}