# C++ Smart Pointers

#### 1. Operations Common to `shared_ptr` and `unique_ptr`

* `shared_ptr<T> sp`, `unique_ptr<T> up`: Null smart pointer that can point to objects of type `T`;

* `p`: Use `p` as a condition; `true` if `p` points to an object, not a null smart pointer

* `*p`: dereference `p` to get the object to which `p` points.

* `p->mem`: Synonym for `(*p).mem`

* `p.get()`: returns the pointer in `p`. The object to which the returned pointer points will disappear when the smart pointer deletes it.

* `swap(p, q)`, `p.swap(q)`: swaps the pointers in `p` and `q`

#### 2. `shared_ptr` class

##### 2.1 copying and assigning `shared_ptr`

When we copy or assign a `shared_ptr`, each `shared_ptr` keeps track of how many other `shared_ptr` points to the same object:
```C++
// object to which p points to has one user
auto p = make_shared<int>(42);

// p and q points to the same object
// object to which p points to has two users
auto q(p);
```

We can think of a `shared_ptr` as if it has an associated counter, usually referred to as a `reference count`. Whenever we copy a `shared_ptr`, the count is incremented. For example, the counter associated with a `shared_ptr` in incremented when:

* we use it to initialize another `shared_ptr`
* we use it as the right-hand operand of an assignment
* we pass it to or return it from a function by value.

The counter is decremented when:

* we assign a new value to the `shared_ptr`
* `shared_ptr` itself is destroyed, such as when a local `shared_ptr` goes out of scope

##### 2.2 Operations specific to `shared_ptr`

* `make_shared<T>(args)`: returns a `shared_ptr` pointing to a dynamically allocated object of type `T`. Uses `args` to initialize that object.

* `shared_ptr<T> p(q)`: `p` is a copy of the `shared_ptr q`; increments the count in `q`. The pointer in `q` must be convertible to `T*`

* `p = q`: `p` and `q` are `shared_ptr` holding pointers that can be converted to one another. Derements `p`'s reference count and increment `q`'s count; deletes `p`'s existing memory if `p`'s count goes to 0.

* `p.unique()`: returns `true` if `p.use_count()` is one; false otherwise.

* `p.use_count()`: returns the number of objects sharing with `p`; may be a slow operation, intended primarily for debugging purposes.

##### 2.3 Other ways to define and change `shared_ptr`

* `shared_ptr<T> p(q)`: `p` manages the object to which the built-in pointer `q` points; `q` must point to memory allocated by `new` and must be convertible to `T*`.

* `shared_ptr<T> p(u)`: `p` assumes ownership from the `unique_ptr u`; makes `u nullptr`;

* `shared_ptr<T> p(q, d)`: `p` assumes ownership from the object to which the built-in pointer `q` points. `q` must be convertible to `T*`. `p` will use the callable object `d` in place of `delete` to free `q`

* `shared_ptr<T> p(p2, d)`: `p` is a copy of the `shared_ptr<T> p2`and `p` uses the callable object `d` in place of `delete`

* `p.reset()`; `p.reset(q)`; `p.reset(q, d)`: if `p` is the only `shared_ptr` pointing at its object, `reset` frees `p`'s existing object. If the optional built-in pointer `q` is passed, make `p` point to `q`, otherwise, makes `p` nullptr. If `d` is supplied, will call `d` to free `q` otherwise uses `delete` to free `q`

##### 2.3 Using `shared_ptr` with `new`
```C++
// must use direct initialization.
// we can't implicitly convert a pointer to a smart pointer.
// we must explicitly bind a shared_ptr to the pointer.
shared_ptr<int> p2(new int(4));
```

Don't mix ordinary pointers and smart pointers
```C++
int *x(new int(32));
process(shared_ptr<int>(x)); // legal, but the memory will be deleted!
int j = *x; // undefined: x is a dangling pointer!
```

When we bind a `shared_ptr` to a plain pointer, we give responsibility for that memory to that `shared_ptr`. Once we give `shared_ptr` responsibility for a pointer, we should no longer use a built-in pointer to access the memory to which the `shared_ptr` now points.

```C++
shared_ptr<int> p(new int(31));
int *q = p.get();
{
    // two independent shared_ptr points to the same memory
    shared_ptr<int>(q);
}
// block ends, the memory to which q points is freed
int foo = *p; // undefined, the memory to which p points was freed.
```

Use `get` only to pass access to the pointer to code that we know will not delete the pointer. In particular, never use `get` to initialize or assign to another smart pointer.

##### 2.4 Smart pointers and exceptions
`new` has some problem when exception occurs:
```C++
void f()
{
    int* ip = new int(42);
    // code that throws an exception that is not caught inside f
    delete ip; // free the memory before exiting
}
```

If an exception happens between the `new` and the `delete`, and is not caught inside `f`, then this memory can never be freed. memory leak

When we use a smart pointer, the smart pointer class ensures that memory is freed when it's no longer needed even if the block is exited prematurely.
```C++
void f()
{
    shared_ptr<int> ip = make_shared<int>(42);
    //code that throws an exception that is not caught inside f
    // shared_ptr freed automatically when the function ends.
}
```

##### 2.5 Conventions using `shared_ptr`

* Don't use the same built-in pointer value to initialize(or rest) more than one smart pointer

* Don't `delete` the pointer returned from `get()`

* Don't use `get()` to initialize or `reset` another smart pointer.

* If we use a pointer returned by `get()`, remember that the pointer will become valid when the last corresponding smart pointer goes away.

* If we use a smart pointer to manager a resource other than memory allocated by `new`, remember to pass a deleter.

#### 3. `unique_ptr`

Only one `unique_ptr` at a time can point to a given object. The object to which a `unique_ptr` points is destroyed when the `unique_ptr` is destroyed.

Bacause `unique_ptr` owns the object to which it points, `unique_ptr` does not support ordinary copy or assignment.

##### 3.1 `unique_ptr` operations

* `unique_ptr<T> u1`: Null `unique_ptr` that can point to objects of type `T`. `u1` will use `delete` to free its pointer.

* `unique_ptr<T, D> u2`: Null `unique_ptr` that can point to objects of type `T`. `u2` will use a callable object of type `D` to free its pointer.

* `unique_ptr<T, D> u(d)`: Null `unique_ptr` that point to objects of type `T` that uses `d` which must be an object of type `D` in place of `delete`.

* `u = nullptr`: Deletes the object to which `u` points; makes `u null`.

* `u.release()`: Relinquishes control of the pointer `u` had held; returns the pointer `u` had held and makes `u null`.

* `u.reset(); u.reset(q); u.reset(nullptr)`: Deletes the object to which `u` points; If the built-in pointer `q` is supplied, makes `u` point to that object. Otherwise makes `u null`.

We can transfer ownership from one(nonconst) `unique_ptr` to another by calling `release` or `reset`:
```C++
unique_ptr<string> p1(new string("hello world"));
// transfers ownership from p1 to p2
// release make p1 nullptr
unique_ptr<string> p2(p1.release());

unique_ptr<string> p3(new string("another"));
// transfers ownership from p3 to p2
// reset deletes the memory to which p2 had pointed
p2.reset(p3.release());
```

There is one exception to the rule that we cannot copy a `unique_ptr`: We can copy or assign a `unique_ptr` that is about to be destroyed. This is because of the `move` semantics
```C++
unique_ptr<int> clone(int p)
{
    unique_ptr<int> ret(new int(p));
    return ret;
}
```

##### 3.2 effective `unique_ptr`

It's reasonble to assume that, by default, `std::unique_ptr` are the same size as raw pointers, and for most operations(including dereferencing), they execute exactly the same instructions. 

When using custom deleters, the size will be larger. Deleters that are function pointers generally cause the size of a `std::unique_ptr` to grow from one word(e.g. 4 bytes) to two words(e.g. 8 bytes). For deleters that are function objects, the change in size depends on how much state is stored in the function object. Stateless function object(e.g. from lambda expressions with no captures) incur no size penalty. and this means that when a custom deleter can be implemented as either a function or a captureless lambda expression, the lambda is preferable.

* A **function object** is any object for which the *function call operator* is defined.

* A lambda function is an unnamed *function object* capable of capturing variables in scope. 

`std::unique_ptr` is a *move-only type*. Upon destruction, a non-null `std::unique_ptr` destroys its resource. By default, resource destruction is accomplished by applying `delete` to the raw pointer inside the `std::unique_ptr`.

A common use for `std::unique_ptr` is as factory function return type for objects in a hierarchy.

`std::unqiue_ptr` easily and efficiently converts to a `std::shared_ptr`:
```C++
std::unqiue_ptr<int> up(new int(3));

// notice std::move
// move the pointed-object to shared_ptr.
std::shared_ptr<int> sp = std::move(up);
```
see [smartPointersTest.hpp](https://github.com/hsgui/interest-only/blob/master/LearningCPlusPlus/smartPointersTest.hpp)

#### 4. `weak_ptr`

A `weak_ptr` is a smart pointer that doesn't control the lifetime of the object to which it points. A `weak_ptr` points to an object that is managed by a `shared_ptr`. Binding a `weak_ptr` to a `shared_ptr` does not change the reference count of that `shared_ptr`. Once the last `shared_ptr` pointing the object goes away, the object itself will be deleted. That object will be deleted even if there are `weak_ptr` pointing to it.

To create a `weak_ptr`, we initialize it from a `shared_ptr`:
```C++
auto p = make_shared<int>(11);

// reference count is unchanged.
weak_ptr<int> wp(p);
```

Because the object might no longer exist, we can't use a `weak_ptr` to access its object directly. To access that object, we must call `lock`. The `lock` function checks whether the object to which the `weak_ptr` points still exists. If so, `lock` returns a `shared_ptr` to the shared object. As with any other `shared_ptr`, we are guaranteed that the underlying object to which that `shared_ptr` points continues to exist at least as long as that `shared_ptr` exists.

```C++
// true if np is not nullptr
if (shared_ptr<int> np = wp.lock())
{
    // np shares its object with p
}
```

##### 4.1 `weak_ptr` operations

* `weak_ptr<T> w`: Null `weak_ptr` that can point at object of type `T`.

* `weak_ptr<T> w(sp)`: `weak_ptr` that points the same object as the `shared_ptr` sp. `T` must be convertible to the type to which `sp` points.

* `w = p`: `p` can be a `shared_ptr` or a `weak_ptr`. After the assignment `w` shares ownership with `p`.

* `w.reset()`: Makes `w null`

* `w.use_count()`: The number of `shared_ptr` that share ownership with `w`.

* `w.expired()`: Returns `true` if `w.use_count()` is zero, `false` otherwise.

* `w.lock()`: If `expired` is `true`, returns a null `shared_ptr`; otherwise returns a `shared_ptr` to the object to which `w` points.

#### 5. `new` and Arrays

```C++
int *p = new int[43];
```

When we use `new` to allocate an array, we don't get an object with an array type. Instead, we get a pointer to the element type of the array. Because the allocated memory does not have an array type, we cannot call `begin` or `end` on a dynamic array. And we also cannot use a range `for` to process the elements in a dynamic array.

By default, objects allocated by `new` - whether allocated as a single object or in an array - are defalut initialized. We can value initialize the elements in an array by following the size with an empty pair of parentheses.
```C++
// block of ten uninitialized ints
int* pia = new int[10];

// block of ten ints value initialized to 0
int* pia2 = new int[10](0);

// both are blocks of ten empty strings
string* psa = new string[10];
string* psa2 = new string[10]();

int *pia3 = new int[10]{0,1,2,3,4,5,6,7,8,9};

int * px = new int[0];
```

When we use `new` to allocate an array of size zero, `new` returns a valid, nonzero pointer. That pointer is guaranteed to be distinct from any other pointer returned by `new`. This pointer acts as the off-the-end pointer for a zero-element array. The pointer cannot be dereferenced because it points to no element.

```C++
// pia must point to a dynamically allocated array or be nullptr.
delete [] pia;
```

Elements in an array are destroyed in reverse order.

```C++
unique_ptr<int[]> up(new int[10]);

// use the subscript operator to access the elements in the array.
up[0]=1;
up.reset();
```

We can use `unique_ptr` to manage a dynamic array. The brackets in the type specifier `<int[]>` say that `up` points to an array of `int`s

Unlike `unique_ptr`, `shared_ptr` provide no direct support for managing a dynamic array. If we want to use a `shared_ptr` to manage a dynamic array, we must provide our own deleter:
```C++
shared_ptr<int> sp(new int[10], [](int*p) {delete [] p;});

// we need the following code to access the element.
*(sp.get() + 1) = 1;

// uses the lambda we supplied that uses delete[] to free the memory
sp.reset();
```

#### 6. `allocator` class

An aspect of `new` that limits its flexibility is that `new` combines allocating memory with constructing object in that memory. And `delete` combines destruction with deallocation. Combining initialization with allocation is usually what we want when we allocate a single object. In that case, we almost certainly know the value the object should have.

When we allocate a block of memory, we often **plan** to construct objects in that memory as **needed**. In this case, we'd like to decouple memory allocation from object construction. Decoupling construction from allocation means that we can allocate memory in large chunks and pay the overhead of constructing the objects only when we actually need to create them.

**In general, coupling allocation and construction can be wasteful. More importantly, classes that don't have default constructors cannot be dynamically allocated as an array.**

`allocator` lets us separate allocation from construction. It provides type-aware allocation of raw, unconstructed memory.
```C++
allocator<string> alloc;

// allocate 2 unconstructed string
// p point to one past the last constructed element.
auto const p = alloc.allocate(2);

auto q = p;
// *q is the empty string
alloc.construct(q++);

// *q is "hi"
alloc.construct(q++, "hi");

// this construct will lead to error
// q points to unconstructed memory!
alloc.construct(q++, 10, 'w');
```

The memory an allocator allocates is *unconstructed*. We use this memory by constructing objects in that memory. Using unconstructed memory in other ways is undefined.

When we're finished using the objects, we **must** destroy the elements we constructed. which we can do by calling `destroy` oneach constructed element. The `destroy` function takes a pointer and runs the destructor on the pointed-to object
```C++
while (q != p)
{
    alloc.destroy(--q);
};
```

Once the elements have been destroyed, we can either reuse the memory to hold other `string` or return the memory to the system. We free the memory by calling `deallocate`:
```C++
// p cannot be nullptr, it must point to memory allocated by allocate.
// the size argument passed to deallocate must be the same size as used in the call to allocate.
alloc.deallocate(p, 2);
```

##### 6.1 Standard allocator class and customized algorithms

* `allocator<T> a`: Defines an `allocator` object named `a` that can allocate memory for objects of type `T`

* `a.allocate(n)`: Allocates raw, unconstructed memory to hold `n` objects of type `T`

* `a.deallocate(p, n)`: Deallocates memory that held `n` objects of type `T` starting at the address in the `T*` pointer `p`; `p` must be a pointer previously returned by `allocate`, and `n` must be the size requested when `p` was created. The use must run `destroy` on any object that were constructed in this memory before calling `deallocate`

* `a.construct(p, args)`: `p` must be a pointer to type `T` that points to raw memory; `args` are passed to a constructor of type `T`, which is used to construct an object in the memory pointed by `p`.

* `a.destroy(p)`: runs the destructor on the object pointed to by the `T*` pointer `p`.

* `uninitialized_copy(b, e, b2)`: Copied elements from the input range denoted by iterators `b` and `e` into unconstructed, raw memory denoted by the iterator `b2`. The memory denoted by `b2` must be large enough to hold a copy of the elments in the input range.

* `uninitialized_copy_n(b, n, b2)`: Copied elements starting from `b` into raw memory starting at `b2`

* `uninitialized_fill(b, e, v)`: Constructs objects in the range of raw memory denoted by `b` and `e` as a copy of `v`

* `uninitialized_fill_n(b, n, v)`: Constructs an unsigned number `n` objects starting at `b`. `b` must be unconstructed, raw memory large enough to hold the given number of objects.

```C++
std::vector<int> vi{1,2,3,4,5};

allocator<int> alloc;
auto p = alloc.allocate(vi.size() * 2);

// construct elements starting at p as copies of elements in vi
auto q = uninitialized_copy(vi.begin(), vi.end(), p);

// initialize the remaining elements to 42
q = uninitialized_fill_n(q, vi.size(), 42);
```