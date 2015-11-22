#pragma once

#include "lrvalue.hpp"
#include <string>
#include <iostream>
#include <vector>

namespace C11Practice
{
    /*
        http://thbecker.net/articles/rvalue_references/section_05.html
        question:
            rvalue reference is a rvalue?

        p_src is a rvalue reference,
        but in the line "C11String temp = p_src", copy constructor will be called

        remember: if rvalue reference has a name, then it's a lvalue;
                  if rvalue reference doesn't have a name, then it's a rvalue

        Why is that?
        we could think as following:
            if the move constructor is called to construct temp object, then the data in p_src willn't be used!
                what will it cause? 
                then the following codes after the construction that use the p_src will lead to unexpected behavior
    */
    void testRValueAndRValueReference(C11String&& p_src)
    {
        /* 
            http://kuring.me/post/cpp11_right_reference
        */
        std::cout << "temp object construct start" << std::endl;
        C11String temp = p_src;        // note: copy constructor will be called, instead of move constructor!
        // if we are quite sure p_src will not be used, we could use the following instead:
        // C11String temp = std::move(p_src);
        std::cout << "temp object construct finish: " << temp << std::endl;
    }

    C11String testC11StringValue()
    {
        C11String str("testStringValue");

        // return std::move(str);    return value optimization
        // http://thbecker.net/articles/rvalue_references/section_06.html
        return str;
    }
    void testLRValue()
    {
        C11String a;
        a = testC11StringValue(); // a is a lvalue, testC11StringValue() is a rvalue

        C11String b("testlvalueReference"); // b is  a lvalue
        std::cout << "IsLvalueReference(b): " 
            << C11String::IsLvalueReference(b) << std::endl;

        std::cout << "IsLvalueReference(testC11StringValue()): "
            << C11String::IsLvalueReference(testC11StringValue()) << std::endl;

        std::cout << "Start to Test the std::move() " << std::endl;
        C11String a1("aaaa");
        C11String b1("bbbb");
        std::cout << "Before move: a=" << a1
            << "; b=" << b1 << std::endl;
        C11Practice::Swap(a1, b1);
        std::cout << "After swap is called: a=" << a1
            << "; b=" << b1 << std::endl;

        C11Practice::SwapWithMove(a1, b1);
        std::cout << "After SwapWithMove is called: a=" << a1
            << "; b=" << b1 << std::endl;

        std::cout << "start to test rvalue and rvalue reference" << std::endl;
        testRValueAndRValueReference(testC11StringValue());
        std::cout << "finish to test rvalue and rvalue reference" << std::endl;
    }

    void testMove()
    {
        std::string s1 = "hello";
        std::string s2 = "world";

        std::cout << "Before move: " << std::endl;
        std::cout << "s1 = " << s1 << ", s2 = " << s2 << std::endl;
        s2 = std::move(s1);

        std::cout << "After move: " << std::endl;
        std::cout << "s1 = " << s1 << ", s2 = " << s2 << std::endl;
    }

    void bracedInitializers(const std::vector<int>& a)
    {
        std::cout << a.size() << std::endl;
    }

    template<typename... Args>
    void bracedInitializersProxy(Args&&... args)
    {
        bracedInitializers(std::forward<Args>(args)...);
    }

    void nullPointers(const int* p)
    {
        std::cout << p << std::endl;
    }

    template<typename... Args>
    void nullPointersProxy(Args&&... args)
    {
        nullPointers(std::forward<Args>(args)...);
    }

    void testBracedInitializers()
    {
        // pass braced initializers
        bracedInitializers({ 1,2,3,4 });

        // std::forward failed.
        //bracedInitializersProxy({ 1,2,3,4 });

        // option:
        auto a = { 1,2,3,4 };
        bracedInitializersProxy(a);
    }

    void testnullPointers()
    {
        nullPointers(0);

        nullPointersProxy(nullptr);
        // cannot convert argument from "int" to "const int*"
        //nullPointersProxy(0);
    }

    struct IPv4Header
    {
        std::uint32_t version : 4,
            IHL : 4,
            DSCP : 6,
            ECN : 2,
            totalLength : 16;
    };

    void bitfieldFunc(uint32_t l)
    {
        std::cout << l << std::endl;
    }

    template<typename... Args>
    void bitfieldProxy(Args&&... args)
    {
        bitfieldFunc(std::forward<Args>(args)...);
    }

    void testBitfieldFunc()
    {
        IPv4Header header;
        header.totalLength = 4;
        bitfieldFunc(header.totalLength);

        bitfieldProxy(4);

        //bitfieldProxy(header.totalLength);
        auto b = header.totalLength;
        // work around.
        bitfieldProxy(b);
    }

    int overloadFunc(int a)
    {
        std::cout << a << std::endl;
        return a;
    }

    int overloadFunc(int a, int b)
    {
        std::cout << a << ", " << b << std::endl;
        return a + b;
    }

    // the parameter is the same as int (*o)(int)
    void overloadFuncP(int o(int))
    {
        o(4);
    }

    template<typename... Args>
    void overloadFuncTemplate(Args&&... args)
    {
        overloadFuncP(std::forward<Args>(args)...);
    }

    void testOverloadFunc()
    {
        overloadFuncP(overloadFunc);
        // unkown type...
        //overloadFuncTemplate(overloadFunc);

        // working around
        using F = int (*)(int);
        F a = overloadFunc;
        overloadFuncTemplate(a);
        // or
        overloadFuncTemplate(static_cast<F>(overloadFunc));
    }

    void testC11Practice()
    {
        testLRValue();

        testMove();

        testnullPointers();
    }
}