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