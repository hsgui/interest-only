#pragma once

#include "power.hpp"
#include <iostream>

namespace LearningCPP
{
    void testPowerN()
    {
        std::cout << "IntegerPower<3>(3) = " << IntegerPower<3>(3) << std::endl;
    }

    void testLearningCPP()
    {
        std::cout << "test powerN" << std::endl;
        testPowerN();
    }
}