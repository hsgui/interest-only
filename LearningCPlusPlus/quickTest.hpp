#pragma once

#include <set>
#include <vector>
#include <string>

namespace LearningCPP
{
    namespace QuickTest
    {
        template<typename... Ts>
        void iprintf(const char* format, Ts&&... params)
        {
            printf(format, std::forward<Ts>(params)...);
            printf("\n");
        }

        std::string getString()
        {
            char temp[123];
            sprintf_s(temp, sizeof(temp), "%s.pdi", "hellowWorldhellowWorld");

            // sprintf_s(temp, sizeof(temp), "%s.pdi", "hellowWorld");
            // the following std::move will still use another address to store the data.

            return temp;
        }

        void testMove(std::string& t)
        {
            std::string s = getString();
            iprintf("%p", &s[0]);
            // If the s.size() < _BUF_SIZE (16), it will call "memmove" eventually
            // otherwise, move assignment will just assign the pointer address.
            t = std::move(s);
            iprintf("s=%s, t=%s", s.c_str(), t.c_str());
            iprintf("%p", &t[0]);

            std::string m = t;
            iprintf("t=%s, m=%s", t.c_str(), m.c_str());
        }

        void testCeil()
        {
            size_t a = 1;
            size_t b = 110;

            uint8_t c = (uint8_t)(ceil(((double)a * 100) / b));
            std::cout << c << std::endl;
        }

        void test()
        {
            std::vector<int> a{ 1,2,3,7,4,5 };
            std::vector<int> b{ 6,3,2,7,9,1 };
            std::set<int> combined;
            combined.insert(a.begin(), a.end());
            combined.insert(b.begin(), b.end());

            iprintf("%s, %d", "hello world", 5);

            std::string t;
            testMove(t);
            iprintf("%s", t.c_str());

            testCeil();

            uint64_t i1 = 11;
            printf("result: %12I64X\n", i1);

            return;
        }
    }
}