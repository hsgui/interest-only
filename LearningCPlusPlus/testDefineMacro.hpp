#pragma once
#include <iostream>

#define LogPdiError(title, ...)         \
        do                              \
        {                                  \
            printf("method1 %s\n", title); \
        } while (false)                     \

// override the previous macro
#define LogPdiError(title, ID, ...)         \
        do                              \
        {                                  \
            printf("method2 %s, id=%d\n", title, ID); \
        } while (false)                     \

namespace LearningCPP
{
    namespace DefineMacro
    {
        void test()
        {
            LogPdiError("hello", 6);
        }
    }
}