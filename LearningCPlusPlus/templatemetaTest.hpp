#pragma once

#include <iostream>
#include "factorial.hpp"
#include "fraction.hpp"
#include "typelist.hpp"
#include "typemanip.hpp"

namespace TemplatePractice {
    void testFraction()
    {
        typedef Frak<2, 4> two_fourth;
        typedef ScalarMultiplication<3, two_fourth>::result fifth_fourth;
        std::cout << "ScalarMultiplication<3, two_fourth>::result "
            << fifth_fourth::Num << "/" << fifth_fourth::Den << std::endl;

        typedef Simpl<two_fourth>::result one_two;
        std::cout << "Simpl<two_fourth>::result "
            << one_two::Num << "/" << one_two::Den << std::endl;

        typedef Sum<two_fourth, one_two>::result one;
        std::cout << "Sum<two_fourth, one_two> "
            << one::Num << "/" << one::Den << std::endl;

        typedef E<5>::result X;
        std::cout << "e = " << (1.0 * X::Num / X::Den) << std::endl;
        std::cout << "e = " << X::Num << "/" << X::Den << std::endl;
    }

    void testTypeList()
    {
        // all these will be calculated at compile time, they are constant!
        std::cout << std::endl;
        std::cout << "test type list -- all these are calculated at compile time" << std::endl;

        typedef TypeList < ModernDesign::Int2Type<1>, TypeList<ModernDesign::Int2Type<2>,
            TypeList<ModernDesign::Int2Type<3>> >> oneTwoThree;

        std::cout << "Length(oneTwoThree): " << TL::Length<oneTwoThree>::result << std::endl;

        std::cout << "Nth(oneTwoThree, 1): " << TL::Nth<oneTwoThree, 1>::result::value << std::endl;

        std::cout << "Include(3, oneTwoThree): " << TL::Include<ModernDesign::Int2Type<3>, oneTwoThree>::result << std::endl;
        std::cout << "Include(4, oneTwoThree): " << TL::Include<ModernDesign::Int2Type<4>, oneTwoThree>::result << std::endl;

        typedef TL::Append<ModernDesign::Int2Type<4>, oneTwoThree>::result T1234;
        std::cout << "Include(4, T1234): " << TL::Include<ModernDesign::Int2Type<4>, T1234>::result << std::endl;

        int position = TL::Position<ModernDesign::Int2Type<4>, T1234>::result;
        std::cout << "Position<Int<4>, T1234>::result "
            << position << std::endl;
    }

    void testMetaTemplate()
    {
        testFraction();
        testTypeList();
    }
}