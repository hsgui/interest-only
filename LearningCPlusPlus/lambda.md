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