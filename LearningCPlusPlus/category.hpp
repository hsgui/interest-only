#pragma once

#include <memory>
#include <functional>

namespace CategoryPractice
{
    /*
        http://bartoszmilewski.com/2014/10/28/category-theory-for-programmers-the-preface/

        Types are sets of values. 
        The type bool is a two-element set of true and false,
        The type char is a 256-elments set of integer range in [0, 255]

        a category of sets, called Set. 
        In Set, objects are sets (or types) and morphisms (arrows) are functions

        pure functions: functions that always produce the same result given the same input
            and have no side effects.
    */
    /*
        category consists of objects and arrows (morphisms). 
        Arrows can be composed, and the composition is associative.
        category theory is about composing arrows
    */
    /*
        identity function
    */
    template<typename T>
    T id(T& t)
    {
        return t;
    }

    template<typename T>
    void unit(T& t)
    {}

    /*
        todo: using std::unique_ptr<T>
        lift function f:: A -> B to std::shared_ptr<A> -> shared_ptr<B>
        shared_ptr<T> is a container of type A.
        type constructor shared_ptr constructs type shared_ptr<T> from type T
        shared_ptr is a Functor ?

        std::function -- http://en.cppreference.com/w/cpp/utility/functional/function
    */
    template<typename A, typename B>
    std::shared_ptr<B> fmap(std::function<B(A)>& f, std::shared_ptr<A> const& a)
    {
        std::shared_ptr<B> result;
        if (a) result.reset(new B(f(*a)));
        return result;
    }

    template<typename A, typename B>
    std::shared_ptr<B> apply(std::shared_ptr<std::function<B(A)>>& f, std::shared_ptr<A> const& a)
    {
        std::shared_ptr<B> result;
        if (f && a)
        {
            result.reset(new B((*f)(*a)));
        }

        return result;
    }
}