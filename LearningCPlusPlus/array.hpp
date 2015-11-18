#pragma once

// http://www.codeproject.com/Articles/257589/An-Idiots-Guide-to-Cplusplus-Templates-Part#NonTypeTemplArg
namespace TemplatePractice
{
    const int DEFAULT_ARRAY_LENGTH = 128;
    /*
        default nontype argument is 128
        when declare Array<int>, it means Array<int, 128>, which is automatically placed 
            by compiler during the instantiation of this class template

        1. only integral data-types can be non-type integer argument, it includes int, char, long, long long, unisgned variants and enums
            Types such as float and double are not allowed
        2. When being instantiated, only compile time constant integer can be passed. this means 100, 100+99, 1<<3 etc are allowed, 
            since they are compiled time constant expressions. Arguments, that involve function call like abs(-120), are not allowed.

        Array<int> and Array<int, 128> are the same type;
        Array<int> and Array<int, 129> are different type!
        Array<double> and Array<int> are different type too!
    */
    template<typename T, 
             int SIZE = DEFAULT_ARRAY_LENGTH>
    class Array {
    private:
        T theArray[SIZE];
    public:
        void Initialize()
        {
            for (int i = 0; i < SIZE; ++i)
            {
                // T must have default construtor!
                theArray[i] = T();
            }
        }

        T operator[](int p_index) const
        {
            if (p_index < SIZE && p_index >= 0)
            {
                return theArray[p_index];
            }
            return T();
        }

        T& operator[](int p_index)
        {
            return theArray[p_index];
        }

        T Accumulate() const
        {
            // default constructor, initial the "0" value
            T sum = T();
            for (int i = 0; i < SIZE; ++i)
            {
                // T must have += operator.
                sum += theArray[i];
            }
            return sum;
        }

        template<typename C>
        void Copy(C p_targetArray[SIZE])
        {
            for (int i = 0; i < SIZE; ++i)
            {
                p_targetArray[i] = static_cast<C>(theArray[i]);
            }
        }
    };
}