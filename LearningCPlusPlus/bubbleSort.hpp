#pragma once

// https://www10.informatik.uni-erlangen.de/~pflaum/pflaum/ProSeminar/meta-art.html

namespace TemplatePractice {

    static inline void swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    static void iterativeBubbleSort(int* data, int N)
    {
        for (int i = N - 1; i > 0; --i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (data[j] > data[j + 1])
                {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    // issue: when I remove the static keyword, this program has compiling error!
    static void recursiveBubbleSort(int* data, int N)
    {
        for (int j = 0; j < N - 1; ++j)
        {
            if (data[j] > data[j + 1])
                swap(data[j], data[j + 1]);
        }

        if (N > 2)
        {
            recursiveBubbleSort(data, N - 1);
        }
    };

    template<int I, int J>
    class IntSwap {
    public:
        static inline void compareAndSwap(int* data)
        {
            if (data[I] > data[J])
            {
                swap(data[I], data[J]);
            }
        }
    };

    template<int I, int J>
    class IntBubbleSortLoop {
    private:
        enum { go = (J <= I - 2) };
    public:
        static inline void loop(int* data)
        {
            IntSwap<J, J + 1>::compareAndSwap(data);
            IntBubbleSortLoop<go ? I : 0, go ? J + 1 : 0>::loop(data);
        }
    };

    template<>
    class IntBubbleSortLoop<0, 0> {
    public:
        static inline void loop(int* data)
        {
        }
    };

    template<int N>
    class IntBubbleSort {
    public:
        static inline void sort(int* data)
        {
            IntBubbleSortLoop<N - 1, 0>::loop(data);
            IntBubbleSort<N - 1>::sort(data);
        }
    };

    template<>
    class IntBubbleSort<1>
    {
    public:
        static inline void sort(int* data)
        {}
    };

}