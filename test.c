/**
 * Copyright (c) 2010-2011 Andreas Meingast, <ameingast@gmail.com>
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

#include <stdio.h>

#include "bm.h"
#include "lambda.h"
#include "test.h"

#define ASSERT(c) do {                                                      \
  if (!(c)) printf("%s:%d: Assertion failed: <"#c">\n", __FILE__, __LINE__); \
} while (0)

#define ASSERT_EQUAL(x, y) ASSERT(x == y)

#define ASSERT_NOT_EQUAL(x, y) ASSERT(x != y)

static void test_lambda(void)
{  
  int (*max)(int, int) = lambda(int, (int x, int y) { return x > y ? x : y; });
  
  ASSERT_EQUAL(2, max(1, 2));
  ASSERT_EQUAL(3, lambda(int, (int x, int y) { return x > y ? x : y; })(2, 3));
}

static void test_apply(void)
{
  int (*add_one)(int) = lambda(int, (int x) { return x + 1; });
  
  ASSERT_EQUAL(2, apply(add_one, 1));
  ASSERT_EQUAL(2, apply(lambda(int, (int x) { return x + 1; }), 1));
}

static void test_chain(void)
{
  int (*add_one)(int) = lambda(int, (int x) { return x + 1; });
  
  ASSERT_EQUAL(3, chain(add_one, add_one, 1));
  ASSERT_EQUAL(3, chain(add_one, lambda(int, (int x) { return x + 1; }), 1));
}

static void test_map(void)
{
  int x[5] = { 1, 2, 3, 4, 5 }, y[5] = { 0 };
  int add_one_f(int x) { return x + 1; }
  int (*add_one_p)(int) = lambda(int, (int x) { return x + 1; });
  
  map(x, y, 5, lambda(int, (int x) { return x + 1; }));
  for (int i = 0; i < 5; i++) ASSERT_EQUAL(x[i] + 1, y[i]);
  
  map(x, y, 5, add_one_f);
  for (int i = 0; i < 5; i++) ASSERT_EQUAL(x[i] + 1, y[i]);
  
  map(x, y, 5, add_one_p);
  for (int i = 0; i < 5; i++) ASSERT_EQUAL(x[i] + 1, y[i]);
}

static void test_foldl_int(void)
{
  int x[] = { 1, 2, 3, 4, 5 }, e = 0;
  
  foldl(x, e, 5, lambda(int, (int x, int y) { return x + y; }));
  ASSERT_EQUAL(e, 15);
}

static void test_foldr_int(void)
{
  char x[] = { 2, 5 }, e = 20;
  
  foldr(x, e, 2, lambda(int, (int x, int y) { return x / y; }));
  ASSERT_EQUAL(e, 2);
}

static void test_select(void)
{
  int x[5] = { 1, 2, 3, 4, 5 }, y[5] = { 0 };
  
  select(x, y, 5, lambda(int, (int x) { return x % 2 == 0; }));
  ASSERT_EQUAL(y[0], 2);
  ASSERT_EQUAL(y[1], 4);
}

static void test_forall(void)
{
  int x[] = { 1, 2, 3, 4, 5 }, counter = 0;
  
  forall(x, 5, lambda(void, (int x) { counter++; }));
  ASSERT_EQUAL(counter, 5);
}

static void test_exists(void)
{
  int xs[] = { 1, 2, 3 };
  
  ASSERT_EQUAL(1, exists(xs, 3, lambda(int, (int x) { return x == 2; })));
  ASSERT_EQUAL(0, exists(xs, 3, lambda(int, (int x) { return x < 0; })));
}

static void test_all(void)
{
  int xs[] = { 2, 2, 2 };
  
  ASSERT_EQUAL(1, all(xs, 3, lambda(int, (int x) { return x == 2; })));
  ASSERT_EQUAL(0, all(xs, 3, lambda(int, (int x) { return x < 2; })));
}

static void test_nested_forall(void)
{
  int xs[] = { 1, 2, 3 }, ys[] = { 1, 2, 3 }, zs[] = { 1, 2, 3 }, counter = 0;
  
  forall(xs, 3, lambda(void, (int x) { 
    forall(ys, 3, lambda(void, (int y) {
      forall(zs, 3, lambda(void, (int z) {
        counter++;
      }));
    }));
  }));
  ASSERT_EQUAL(27, counter);
}

static void test_nested_map(void)
{
  int xxs[3][3] = { { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 } }, ys[3] = { };
  
  map(xxs, ys, 3, lambda(int, (int xs[]) { 
    int result = 0;
    foldl(xs, result, 3, lambda(int, (int x, int y) { return x + y; }));
    return result;
  }));
  ASSERT_EQUAL(6, ys[0]);
  ASSERT_EQUAL(6, ys[1]);
  ASSERT_EQUAL(6, ys[2]);
}

static void test_nested_all(void)
{
  int xxs[3][3] = { { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 } };
  
  ASSERT_EQUAL(1, all(xxs, 3, lambda(int, (int xs[]) {
    return all(xs, 3, lambda(int, (int x) { return x < 4; }));
  })));
}

static void test_bm(void)
{
  int i = 0;
  
  ASSERT_NOT_EQUAL(0, bm(10, lambda(void, (void) { i++; })));
  ASSERT_EQUAL(i, 10);
}

void test_suite(void)
{
  test_lambda();
  test_apply();
  test_chain();
  test_map();
  test_foldl_int();
  test_select();
  test_foldr_int();
  test_forall();
  test_exists();
  test_all();
  test_nested_forall();
  test_nested_map();
  test_nested_all();
  test_bm();
}