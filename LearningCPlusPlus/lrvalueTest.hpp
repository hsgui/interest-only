#pragma once

#include "lrvalue.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>

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

    // SFINAE
    // overload universal reference
    // C++ will generate both copy and move constructors
    //  even if the class contains a templatized constructor that could
    //  be instantiated to produce the signature of the copy or move constructor.
    class Person {
    public:
        template<typename T,
            typename = typename std::enable_if <
            !std::is_base_of < Person,
                               typename std::decay<T>::type 
            > ::value >::type>
        explicit Person(T&& n)
            : name(std::forward<T>(n))
        {
            // std::is_constructible type trait performs a compile-time test
            // to determine whether an object of one type can be 
            // constructed from an object of a different type.
            // This causes the specified error message to be produced if client code
            // tries to create a Person from a type that can't be used to construct a std::string
            static_assert(
                std::is_constructible<std::string, T>::value,
                "Parameter n can't be used to construct a std::string");

            std::cout << "SFINAE - overload universal reference:" << name << std::endl;
        }

        explicit Person(int idx)
        {
            std::cout << "SFINAE - overload universal reference, idx=" << idx << std::endl;
        }

    private:
        std::string name;
    };

    void testEnableIf()
    {
        Person p1("hello world");
        Person p2(3);
    }

    std::multiset<std::string> names;

    void logAndAdd(const std::string& name)
    {
        std::cout << name << std::endl;
        names.emplace(name);
    }

    void testLogAndAdd()
    {
        std::string petName("Darla");

        logAndAdd(petName); // pass lvalue std::string, ok

        // Problem 1:
        // pass rvalue std::string
        // the name is copied into names.
        // but as the argument is rvalue, we can do move actually!
        logAndAdd(std::string("Persephone"));

        // Problem 2:
        // an implicit constructor of std::string is called.
        // the name is copied into names
        // we can pass the const char* into emplace directly 
        // so there is no need to construct std::string.
        logAndAdd("Patty Dog");
    }

    template<typename T>
    void logAndAddEfficiently(T&& name)
    {
        std::cout << name << std::endl;
        names.emplace(std::forward<T>(name));
    }

    std::map<int, std::string> nameFromIdx;
    // If we overload the universal reference function
    void logAndAddEfficiently(int idx)
    {
        names.emplace(nameFromIdx[idx]);
    }

    void testLogAndAddEfficiently()
    {
        std::string petName("Darla");

        // instantiate logAndAddEfficiently<std::string &>(std::string& name);
        logAndAddEfficiently(petName);

        // name is moved to names
        // instantiate logAndAddEfficiently<std::string>(std::string&& name);
        logAndAddEfficiently(std::string("Persephone"));

        // construct std::string in names with string literal.
        // instantiate logAndAddEfficiently<const char (&)[10]>(const char (&name)[10]);
        logAndAddEfficiently("Patty Dog");

        // construct std::string in names with string literal.
        // instantiate logAndAddEfficiently<const char (&)[6]>(const char (&name)[6]);
        logAndAddEfficiently("Patty");
    }

    // C++ will generate both copy and move constructors if we don't define one
    //  even if the class contains a templatized constructor that could
    //  be instantiated to produce the signature of the copy or move constructor.
    class BadPerson
    {
    public:
        template<typename T>
        explicit BadPerson(T&& n)
            : name(std::forward<T>(n))
        {
            std::cout << name << std::endl;
        }

        // a compiler-generated copy ctor:
        // BadPerson(const BadPerson& rhs);

        // a compiler-generated move ctor:
        // BadPerson(BadPerson&& rhs);

        explicit BadPerson(int idx)
        {
            std::cout << idx << std::endl;
        }

    private:
        std::string name;
    };

    /*
    // inheritance...
    class SpecialPerson : public BadPerson
    {
    public:
        SpecialPerson(const SpecialPerson& rhs) // copy ctor
            : BadPerson(rhs) // base class forwarding ctor, won't compile
                             // because we use SpecialPerson to initialize BadPerson
                             // and perfect forwarding is an exact match 
                             // than the copy ctor
        {}

        SpecialPerson(SpecialPerson&& rhs)
            : BadPerson(std::move(rhs))
        {}
    };
    */

    void testOverloadUniversalRef()
    {
        // short nameIdx;

        // instantiate logAndAddEfficiently<short&>(short& name); -- exact match
        // not use logAndAddEfficiently(int idx); -- need a promotion
        // this is an error
        // logAndAddEfficiently(nameIdx);

        BadPerson p("Nancy");
        // compile-eror: cannot convet from BadPerson to std::initializer_list<_Elem>
        // It will call the perfect-forwarding constructor.
        // That function will try to initialize BadPerson's std::string data member
        // with a BadPerson object(p)
        // But std::string having no constructor taking a BadPerson.
        // The reason why compiler uses the perfect-forwarding constructor 
        //      instead of the compiler-generated copy constructor is:
        // cloneOfP is being intialized with a non-const lvalue(p), that means:
        // the perfect forwarding construtor can be initialized to take a non-const lvalue
        //      which is an exact match
        // while the copy constructor would require adding const to p to match the parameter's type.
        // auto cloneOfP(p);

        const BadPerson p1("const nancy");
        // compiled.
        // now it's an exact match for the parameter taken by the copy constructor.
        // and the overload-resolution rules in C++ is that:
        //   the normal function is preferred if a template instantiation and a non-template function
        //   are equally good matches for a function call.
        auto cloneOfCP(p1);
    }

    void testC11Practice()
    {
        testLRValue();

        testMove();

        testnullPointers();

        testEnableIf();

        testOverloadUniversalRef();
    }
}