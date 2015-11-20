# Rvalue reference

#### 1. Expression value categories

An expression can be an `lvalue` or an `rvalue`. In concept, rvalues correspond to temporary objects returned from functions, while lvalues correspond to objects we can refer to, either by name or by following a pointer or `lvalue reference` (lvalue reference is an lvalue). An expression that is not an lvalue is an rvalue.

A useful heuristic to determin whether an expression is an lvalue is to ask if we can take its address. If we can, it typically is. If we can't, it's usually an rvalue. Additionally, If the type of an expression is an lvalue reference (`T&` or `const T&`), that expression is a lvalue.

Remmeber that the `type of an expression` is independent of whether the `expression is an lvalue or an rvalue`. That is, given a type `T`, we can have lvalues of type `T` as well as rvalues of type `T`. When dealing with a parameter of rvalue reference type, the parameter itself is an lvalue:

```C++
class Widget{
public:
// rhs means "right-hand side"
// rhs (an expression) is an lvalue
// because we can take rhs's address inside Widget's move constructor
// though it has an rvalue reference type.
// By similar reasoning, all parameters are lvalues.
    Widget(Widget&& rhs);
}
```

#### 2. Arguments and parameters

In a function call, the expressions passed at the call site are the function's `arguments`. 

The arguments are used to initialize the function's `parameters`.

```C++
void someFunc(Widget w);

Widget wid;

someFunc(wid);

SomeFunc(std::move(wid));
```

In the first call to `someFunc` above, the `argument` is `wid`. In the second call, the `argument` is `std::move(wid)`. In both calls, the `parameter` is `w`. *`All parameters` are `lvalues`, but the `arguments` with which they are initialized may be rvalues or lvalues*.

#### 3. Understand `std::move` and `std::forward`

`std::move` doesn't move anything, `std::forward` doesn't forward anything. **At runtime, neither does anything at all. They generate no executable code. Not a single byte.**

`std::move` and `std::forward` are merely functions (function templates) that perform *cast*:

* `std::move` unconditionally casts its argument to an rvalue; 

* while `std::forward` performs this cast only if a particular condition is fulfilled, that is *its argument was initialized with an rvalue*.

##### 3.1 `std::move` const type

```C++
template<typename T>
typename remove_reference<T>::type&&
move(T&& param)
{
    // alias declaration;
    using ReturnType =
        typename remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}
```

The `“&&”` part of the function’s return type implies that `std::move` returns an rvalue reference. If the type `T` happens to be an lvalue reference, `T&&` would become an lvalue reference. To prevent this from happening, the type trait `std::remove_reference` is applied to `T`, thus ensuring that `“&&”` is applied to a type that isn’t a reference. That guarantees that `std::move` truly returns an `rvalue reference`, and that’s important, because *rvalue references returned from functions are rvalues*. Thus, *`std::move` casts its argument to an rvalue*, and that’s all it does.

Because `std::move` does nothing but cast its argument to an rvalue, there have been suggestions that a better name for it might have been something like `rvalue_cast`. Be that as it may, the name we have is `std::move`, so it’s important to remember what `std::move` does and doesn’t do. *It does cast. It doesn’t move.*

*Rvalues are candidates for moving*, so applying `std::move` to an object tells the compiler that the object is eligible to be moved from. That’s why `std::move` has the name it does: to make it easy to designate objects that may be moved from. In truth, *rvalues are only usually candidates for moving*

```C++
clas Widget{
public:
    explicit Widget(const std::string text)
        : value(std::move(text))
    {}

private:
    std::string value;
};

class string
{
public:
    string(const string& rhs); // copy ctor
    string(string&& rhs); // move ctor
};
```

Although we are moving `text`, but `value` is constructed by copy-construction, not move-construction. Because the result of `std::move` is an `rvalue const std::string`.

In the `Widget` constructor’s member initialization list, the result of `std::move(text)` is an `rvalue of type const std::string`. That rvalue can’t be passed to std::string’s move constructor, because the move constructor takes an rvalue reference to a `non-const std::string`. The rvalue can be passed to the copy constructor, because an `lvalue-reference-to-const` is permitted to bind to a `const rvalue`. The member initialization therefore invokes the copy constructor in `std::string`, even though text has been cast to an rvalue! Such behavior is essential to maintaining const-correctness. *Moving a value out of an object generally modifies the object*, so the language should not permit const objects to be passed to functions(such as move constructors) that could modify them.

Two lessons we can draw from this example:

* Don't declare objects `const` if we want to be able to move from them. Move requests on `const` objects are silently transformed into copy operations.

* `std::move` not only doesn't actually move anything, it doesn't guarantee that the object it's casting will eligible to be moving.

The only thing we know for sure about the result of applying `std::move` to an object is that *it's an rvalue*.