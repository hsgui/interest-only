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

#### 4. Distinguish universal references from rvalue references

To declare an `rvalue reference` to some type `T`, we write `T&&`. It thus seems reasonable to assume that if we see `“T&&”` in source code, we're looking at an rvalue reference. Alas, it’s not quite that simple:
```C++
void f(Widget&& param); // rvalue reference

Widget&& var1 = Wiget(); // rvalue reference

auto&& var2 = var1; // not a rvalue reference

template<typename T>
void f(std::vector<T>&& param); // rvalue reference

template<typename T>
void f(T&& param); // not rvalue reference
```

In fact, `“T&&”` has two different meanings. 

* One is `rvalue reference`. Such references behave exactly the way we expect: they bind only to rvalues, and it is to identify objects that may be moved from.

* The other meaning for `“T&&”` is either rvalue reference or lvalue reference. We call it `universal references`. Such references look like rvalue references in the source code (i.e., `“T&&”`), but they can behave as if they were lvalue references (i.e., “T&”). Their dual nature permits them to bind to rvalues (like rvalue references) as well as lvalues (like lvalue references). Furthermore, they can bind to const or non-const objects, to volatile or non-volatile objects, even to objects that are both const and volatile. They can bind to virtually anything. Such unprecedentedly flexible references deserve a name of their own - `universal reference`.

`Universal references` arise in two contexts. 

* The most common is function template parameters:

```C++
template<typename T>
void f(T&& param);
```

* The second context is `auto` declarations:

```C++
auto&& var2 = var1;
```

How to distinguish universal reference and rvalue reference:

* If a function template parameter has exactly type `T&&` for a **deduced type T**, or if an object is declared using **auto&&**, the parameter or object is a universal reference.

* If the form of the type declaration isn’t precisely `T&&`, or if type deduction does not occur, `T&&` denotes an rvalue reference

```C++
// not precisely T&&
template<typename T>
void f(const std::vector<T>&& param); // rvalue reference

// not precisely T&&
template<typename T>
void f(const T&& param); // rvalue reference

// no type deduction inside vector
// because when push_back is called, T is already known
template<class T, class Allocator = allocator<T>>  
class vector {
public:
    void push_back(T&& x); // rvalue reference
};
```

* Universal references correspond to rvalue references if they’re initialized with rvalues. They correspond to lvalue references if they’re initialized with lvalues.

#### 5. Use `std::move` on `rvalue reference`, `std::forward` on `universal reference`

In short, rvalue references should be unconditionally cast to rvalues (via std::move) when forwarding them to other functions, because they’re always bound to rvalues, and universal references should be conditionally cast to rvalues (via std::forward) when forwarding them, because they’re only sometimes bound to rvalues.

```C++
class Widget 
{
public:
    Widget(Widget&& rhs)             // rhs is rvalue reference  
        : name(std::move(rhs.name))  // use std::move
        , p(std::move(rhs.p))
        { }
private:
    std::string name;
    std::shared_ptr<SomeDataStructure> p; 
}; 
```

```C++
class Widget 
{
public:
    template<typename T>
    void setName(T&& newName)   // newName is universal reference
    { name = std::forward<T>(newName); }  // use std::forward
private:
    T name;
}; 
```

##### 5.1 using universal reference or rvalue reference more than once.

In some cases, we’ll want to use the object bound to an rvalue reference or a universal reference more than once in a single function, and we’ll want to make sure that it’s not moved from until we’re otherwise done with it. In that case, we’ll want to **apply `std::move` (for rvalue references) or `std::forward` (for universal references) to only the final use of the reference**.

```C++
template<typename T>
void setSignText(T&& text) // text is a universal reference
{
    // don't use sign.setText(std::forward<T>(text));
    // because it conditionally change text
    // but we are using text after this statement.
    sign.setText(text);

    // this is the last call.
    // conditionally cast text to rvalue
    // and may change text
    signHistory.add(std::forward<T>(text));
}
```

##### 5.2 using `std::move` (for rvalue reference parameters) or `std::forward` (for universal reference) to return by value.

If we’re in a function that returns by value, and we’re returning an object bound to an rvalue reference or a universal reference, we’ll want to apply `std::move` or `std::forward` when we return the reference. To see why, consider an `operator+` function to add two matrices together, where the left-hand matrix is known to be an rvalue (and can hence have its storage reused to hold the sum of the matrices):

```C++
Matrix  // by-value return, and return from a ravlue reference
operator+(Matrix&& lhs, const Matrix& rhs)
{
    lhs += rhs;
    return std::move(lhs);
}
```

By casting `lhs` to an rvalue in the return statement (via `std::move`), `lhs` will be moved into the function’s return value location. If the call to `std::move` were omitted, the fact that `lhs` is an lvalue would force compilers to instead copy it into the return value location. Assuming that the `Matrix` type supports `move construction`, which is more efficient than `copy construction`, using `std::move` in the return statement yields more efficient code. 

The situation is similar for universal references and `std::forward`:

```C++
template<typename T>
Fraction // by-value return, and return from universal references.
reduceAndCopy(T&& frac)
{
    frac.reduce();
    return std::forward<T>(frac);
}
```

If the call to `std::forward` were omitted, `frac` would be unconditionally *copied* into `reduceAndCopy`’s return value

##### 5.3 Never apply `std::move` or `std::forward` to local objects if they would be eligible for the RVO (return value optimization)

```C++
Widget makeWidget()
{
    Widget w;

    // don't apply std::move(w);
    return w;
}
```

 `makeWidget` can avoid the need to copy the local variable `w` by *constructing it in the memory alloted for the function’s return value*. This is known as the **return value optimization (RVO)**.

About `RVO`, compilers may elide the copying (or moving) of a local object in a function that returns by value if 

* the type of the local object is the same as that returned by the function and 
* the local object is what’s being returned

In the `makeWidget`, both conditions are fulfilled. Actually no copy is applied.

If `std::move(w)` is used in `makeWidget`: it moves the contents of `w` into `makeWidget`’s return value location. But compilers won't use the `RVO` to eliminate the move, which is constructing `w` in the memory alloted for the function’s return value. Because compilers can’t. Condition (2) stipulates that the `RVO` may be performed **only if what’s being returned is a local object**, but it's not. What `std::move(w)` returns is a reference to `w`. Returning a reference to a local object doesn't satisfy the condtitions required for the `RVO`. So compilers must move `w` into the function's return value location.

In effect, the Standard requires that when the `RVO` is permitted, **either copy elision takes place or `std::move` is implicitly applied to local objects being returned**.

So:
```C++
Widget makeWidget()
{
    Widget w;

    return w;
}
```
compilers must either elide the copying of `w` or they must treat the function as if it were written like this:
```C++
Widget makeWidget()
{
    Widget w;

    // treat w as rvalue
    // if no copy elision was performed.
    return std::move(w);
}
```

The situation is similar for `by-value function parameters`. They’re not eligible for copy elision with respect to their function’s return value, but **compilers must treat them as rvalues if they’re returned**. As a result, if your source code looks like this,
```C++
Widget makeWidget(Widget w)
{
    // by-value parameter of same type as function's return value
    return w;
}
```
compilers must treat it as if it had been written this way:
```C++
Widget makeWidget(Widget w)
{
    return std::move(w);
}
```