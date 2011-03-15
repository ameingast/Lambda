/**
 * Copyright (c) 2010 Andreas Meingast, <ameingast@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#ifndef _LAMBDA_H_
#define _LAMBDA_H_

/**
 * Generates an anonymous function with return type 'ret' and function body 
 * 'body'.
 */
#define lambda(ret, body) ({ ret __fn__ body __fn__; })

#define apply(f, ...) (f(__VA_ARGS__))

#define chain(f, g, ...) (apply(f, apply(g, __VA_ARGS__)))

/**
 * Maps all elements in the array source to the array target by applying 
 * f to its elements.
 */
#define map(source, target, size, f) do {                             \
  for (int __i = 0; __i < size; __i++) target[__i] = f(source[__i]);  \
} while (0)

#define foldl(source, e, size, f) do {                                \
  for (int __i = 0; __i < size; __i++) e = f(e, source[__i]);         \
} while (0)

#define foldr(source, e, size, f) do {                                \
  for (int __i = size - 1; __i >= 0; __i--) e = f(e, source[__i]);    \
} while (0)

#define forall(source, size, f) do {                                  \
  for (int __i = 0; __i < size; __i++) f(source[__i]);                \
} while (0)

#define select(source, target, size, f) do {                          \
  for (int __i = 0, __j = 0; __i < size; __i++)                       \
    if (0 != f(source[__i])) target[__j++] = source[__i];             \
} while (0)

#define exists(source, size, f) ({                                    \
  int __fn__ (void) {                                                 \
    for (int i = 0; i < size; i++) if (0 != f(source[i])) return 1;   \
    return 0;                                                         \
  } __fn__;                                                           \
})()

#define all(source, size, f) ({                                       \
  int __fn__ (void) {                                                 \
    for (int i = 0; i < size; i++) if (0 == f(source[i])) return 0;   \
    return 1;                                                         \
  } __fn__;                                                           \
})()

#endif