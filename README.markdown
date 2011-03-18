LAMBDA
======

The lambda library provides functional programming via lambda expressions
for the C programming language. 

Usage
-----
The library the following macro to use lambda abstractions:

    lambda(ret, body)

the following application creates an anonymous code block that adds 1 
to any given integer.

    lambda(int, (int x) { return x + 1; }) 
  
The above expression alone won't yield any results; it needs to be applied to 
an argument. E.g.

    lambda(int, (int x) { return x + 1; })(1); // yields 2

The lambda expression can also be stored in form of a function pointer. E.g.

    int (*add_one)(int) = lambda(int, (int x) { return x + 1; });
    
    add_one(2); // yields 3
    
The created code block is in fact a pointer to an anonymous function.

See use.c

Caveats
-------
Since each invocation of a lambda expression involves a non-inlined function
call, its performance will almost always be worse than regular C code 
(especially if the C code can be heavily optimized by the compiler).

See bm.c