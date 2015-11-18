# Lambda expression

#### 1. What's Lambda
See [lambda](http://en.cppreference.com/w/cpp/language/lambda)

Lambda expression constructs a closure: an unnamed *function object* capable of capturing variables in scope.

The vocabulary associated with lambdas contains the following three items:

* **A lambda expression**: it's just an expression, it's part of the source code
```C++
int x;
auto c1 = [x](int y) { return x*y > 33;};
```

* **A closure**: it's the runtime object created by a lambda.

* **A closure class**: is a class from which a closure is instantiated. Each lambda causes compilers to generate a unique closure class. The statements inside a lambda become executable instructions in the member functions of its closure class.

#### 2. capture

See [testlambda.hpp](https://github.com/hsgui/interest-only/blob/master/LearningCPlusPlus/testlambda.hpp)

##### 2.1 Default captures

There are two default capture modes: by-reference (`&`) and by-value (`=`)

A by-reference capture causes a closure to contain a reference to a local variable or to a parameter that's available in the scope where the lambda is defined. But if the lifetime of a closure created from that lambda exceeds the lifetime of the local variable or parameter, the reference in the closure will dangle. For example:
```C++
using FilterContainer = 
    std::vector<std::function<bool(int)>>;

FilterContainer filters;

void addDivisorFilter()
{
    auto calc1 = computeSomeValue1();
    auto calc2 = computeSomeValue2();

    // compute divisor at runtime.
    auto divisor = computeDivisor(calc1, calc2);
    // dangle - ref to divisor will dangle.
    // the lifetime of closure exceeds the lifetime of the local variable.
    filters.emplace_back([&](int value){return value % divisor == 0;});
}

addDivisorFilter();
// the program won't crash, but the behavior is definite wrong
filters[0](12);
```

Of course, if we define the lambda expression with an explicit capture, the behavior is also wrong
```C++
filters.emplace_back([&divisor](int value){return value % divisor == 0;});
```

But it's easier to see that viability of the lambda is depend on `divisor`'s lifetime. Also, writing out the name, "divisor", reminds us to ensure that `divisor` lives at least as long as the lambda's closures.

Long-term, it's simply better software engineering to explicitly list the local variables and parameters that a lambda depends on.

Things to remember:

* Default by-reference capture can lead to dangling references

* Default by-value capture is susceptible to dangling pointers(especially this), and it misleadingly suggests that lambda are self-contained(but not for static)

##### 2.2 move capture

If we have a move-only object that we want to get into a closure, C++11 offers no way to do it.
```C++
// C++ 14
auto func = [pw = std::make_unique<Widget>()]
            {
                return pw->someFunc();
            };
// we can't do it in C++11
```
In C++14, there is `generalized lambda capture` (`init capture`) feature we can use to capture `move-only object` like above.

In C++11, we can emulate this `init-capture` via hand-written classes or `std::bind`.

###### 2.2.1 Hand-written classes

Remember that a lambda expression is simply a way to cause the compiler to generate a class and an object of that type will be created. There's nothing we can do with a lambda that we can't do by hand. This is just more work to write code.

```C++
class SomeFuncObj
{
public:
    using DataType = std::unqiue_ptr<Widget>;
    explicit SomeFuncObj(DataType&& ptr)
        : pw(std::move(ptr)){}

    void operator()() const
    {
        return pw->someFunc();
    }

private:
    DataType w;
};

auto func = SomeFuncObj(std::make_unique<Widget>());
```

###### 2.2.2 `std::bind`

To implement the move-capture in C++11, we can use `std::bind` in two steps:

1. moving the object to be captured into a function object produced by `std::bind`;

2. giving the lambda reference to the "captured" object.

```C++
std::vector<double> data;

data.push_back(2.3);
data.push_back(1.1);

auto func = 
    std::bind(
        [](const std::vector<double>& data) // lvalue reference
        {/*use of data*/},
        std::move(data)); // move the object to bind object.
```

`std::bind` produces function objects like lambda expression. Let's call these function objects returned by `std::bind` `bind objects`. The first argument to `std::bind` is a callable object. Subsequent arguments represents values to be passed to that object.

A bind object contains copies of all the arguments passed to `std::bind`. 

* For each lvalue argument, the corresponding object in the bind object is copy constructed. 
* For each rvalue, it’s move constructed. 

In above example, the second argument is an rvalue (the result of `std::move`), so `data` is move constructed into the bind object. This move construction is the crux of move capture emulation, because moving an rvalue into a bind object is how we work around the inability to move an rvalue into a C++11 closure.

When a bind object is “called” (i.e., its function call operator is invoked) the arguments it stores are passed to the callable object originally passed to `std::bind`. In above example, that means that when `func` (the bind object) is called, the move constructed copy of `data` inside `func` is passed as an argument to the lambda that was passed to `std::bind`.

The parameter in that lambda is an lvalue reference to the copy of `data` in the bind object. (It’s not an rvalue reference, because although the expression used to initialize the copy of `data`(`std::move(data)`) is an rvalue, the copy of `data` itself is an lvalue.) Uses of data inside the lambda will thus operate on the move-constructed copy of `data` inside the bind object.

By default, the `operator()` member function inside the closure class generated from a lambda is `const`. That has the effect of rendering all data members in the closure const within the body of the lambda. The move-constructed copy of data inside the bind object is not const, however, so to prevent that copy of data from being modified inside the lambda, the lambda’s parameter is declared reference-to-const. If the lambda were declared `mutable`, `operator()` in its closure class would not be declared `const`, and it would be appropriate to omit `const` in the lambda’s parameter declaration:

```C++
auto func = 
    std::bind(
        [](std::vector<double>& data) mutable // lvalue reference
        {/*use of data*/},
        std::move(data)); // move the object to bind object.
```

Because a bind object stores copies of all the arguments passed to `std::bind`, the bind object in our example contains a copy of the closure produced by the lambda that is its first argument. The lifetime of the closure is therefore the same as the lifetime of the bind object. That’s important, because it means that as long as the closure exists, the bind object containing the pseudo-move-captured object exists, too.

These fundamental points should be:

* It's not possible to move-construct an object into C++11 closure, but it's possible to move-construct an object into a C++11 bind object.

* Emulating move-capture in C++11 consists of move-constructing an object into a bind object, then passing the move-constructed object to the lambda by reference

* Because the lifetime of the bind object is the same as that of the closure, it's possible to treat objects in the bind object as if they were in the closure.