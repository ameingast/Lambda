#include <stdio.h>
#include <stdlib.h>

#include "lambda.h"

#define ASSERT_EQUAL(x, y) do {                                           \
  if (x != y) printf("%s:%d: <" #x " != " #y ">\n", __FILE__, __LINE__);  \
} while (0)

static void test_lambda(void)
{  
  int (*max)(int, int) = lambda(int, (int x, int y) { return x > y ? x : y; });
  
  ASSERT_EQUAL(2, max(1, 2));
  ASSERT_EQUAL(3, max(3, 2));
}

static void test_apply(void)
{
  int (*add_one)(int) = lambda(int, (int x) { return x + 1; });
  
  ASSERT_EQUAL(2, apply(add_one, 1));
}

static void test_chain(void)
{
  int (*add_one)(int) = lambda(int, (int x) { return x + 1; });
  
  ASSERT_EQUAL(3, chain(add_one, add_one, 1));
}

static void test_map(void)
{
  int x[5] = { 1, 2, 3, 4, 5 }, y[5] = { 0 };
  int add_one_f(int x) { return x + 1; }
  int (*add_one_l)(int) = lambda(int, (int x) { return x + 1; });
  
  map(x, y, 5, lambda(int, (int x) { return x + 1; }));
  for (int i = 0; i < 5; i++) ASSERT_EQUAL(x[i] + 1, y[i]);
  
  map(x, y, 5, add_one_f);
  for (int i = 0; i < 5; i++) ASSERT_EQUAL(x[i] + 1, y[i]);
  
  map(x, y, 5, add_one_l);
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

int main(int argc, char **argv)
{ 
  test_lambda();
  test_apply();
  test_chain();
  test_map();
  test_foldl_int();
  test_select();
  test_foldr_int();
  test_forall();
  return 0;
}