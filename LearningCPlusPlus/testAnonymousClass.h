#pragma once

#include <iostream>
#include <stdio.h>
#include <stddef.h>

using namespace std;

// https://msdn.microsoft.com/en-us/library/a3bbz53t.aspx
/*
    A microsoft C extension allows us to declare a structure variable within another structure without giving it a name.
    These nested structures are called anonymous structures. C++ does not allow anonymous strucutures.

    we can access the members of an anonymous structure as if they were members in the containing structure.

    A union is a user-defined type in which all members share the same memory location. 
    This means that at any given time, a union can contain no more than one object from its list of members.
    It also means that no matter how many members a union has, it always uses only enough memory to store the largest member.
*/

namespace LearningCPP {
    namespace TestAnonymousClass
    {
        typedef struct
        {
            unsigned x;
            unsigned y;
        } Point;

        struct PTValue
        {
            Point point;
            union
            {
                struct
                {
                    int value1;
                    int value2;
                };
                int values[2];
            };
        };

        void Print(PTValue v)
        {
            std::cout << "value1: " << v.value1 << std::endl;
            std::cout << "value2: " << v.value2 << std::endl;
        }

        void testAnnoymousStructure()
        {
            PTValue value;
            value.value1 = 3;
            value.value2 = 4;
            Print(value);
        }

        /*
            An "incomplete type" can be:
            1. a structure type whose members have not yet specified:
                struct student *ps; -- student has incomplete type.
                struct student
                {
                    int num;
                }; -- student structur now completed.
            2. a union type whose members have not yet specified;
            3. An array type whose dimension have not yet specified:
                char a[]; -- a has incomplete type.
                char a[2]; -- a now has complete type.

            http://en.cppreference.com/w/c/language/struct
            If a struct defines at least one named member, it is allowed to additionally declare its last member with incomplete array type.
            When an element of the flexible array member is accessed, 
            then the struct behaves as if the array member had the longest size fitting in the memory allocated for this object
            If no additional storage is allocated, it behaves as if an array with 1 member, 
                except the behavior is undefined if that element is acessed or a pointer one past that element is produced.
            Initialization, sizeof, and the assignment operator ignore the flexible array member. -- behaves as if the array with 1 memeber.
            structures with flexible array members (or unions whose last member is a structure with flexible array member) 
                can't appear as array elements or as members of other structures
        */
        struct InCompleteStruct
        {
            int n;
            double d[];
        };

        void testFlexibleArrayInStruct()
        {
            InCompleteStruct t0;    // 8 btyes
            std::cout << "sizeof(int)=" << sizeof(int) << ", sizeof(t0)=" << sizeof(t0) << std::endl;
            InCompleteStruct t1 = { 0 };
            std::cout << "sizeof(t1)=" << sizeof(t1) << std::endl;  // 8 bytes
            InCompleteStruct t2 = { 1, {4.2, 3.4} };
            std::cout << "sizeof(t2)=" << sizeof(t2) << std::endl; // 8 bytes

            InCompleteStruct *t3 = (InCompleteStruct*)malloc(sizeof(InCompleteStruct) + 32);
            std::cout << "sizeof(*t3)=" << sizeof(*t3) << std::endl;
            t3->d[8] = 10;  // as if t3->d was double[9]
            std::cout << "t3->d[8]=" << t3->d[8] << std::endl;

            t1 = t2;    // only n is copied, but d is not.
            std::cout << "t1.n=" << t1.n << std::endl;
        }

        void testIntializeStructure()
        {
            struct A
            {
                char a;
                char b;
                double c;
                char d;
            };
            std::cout << "offset of char a =" << offsetof(A, a) << std::endl;
            std::cout << "offset of char b =" << offsetof(A, b) << std::endl;
            std::cout << "offset of double c =" << offsetof(A, c) << std::endl;
            std::cout << "offset of char d =" << offsetof(A, d) << std::endl;
            std::cout << "sizeof(struct A)=" << sizeof(A) << std::endl;

            // A pointer to a struct can be cast to a pointer to its first member and vice versa
            A a;
            a.a = 'a';
            char* firstElement = (char*)&a;
            A b = *((A*)firstElement);
            std::cout << "firstElement=" << *firstElement << ", b.a=" << b.a << std::endl;
        }

        void test()
        {
            testAnnoymousStructure();
            testFlexibleArrayInStruct();
            testIntializeStructure();
        }
    }
}