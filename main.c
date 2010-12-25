#include <stdio.h>
#include <stdlib.h>

#include "lambda.h"

#define ASSERT_EQUAL(x, y, m) do { if (x != y) printf("%s\n", m); } while (0)

static void test_lambda(void)
{  
  int (*max)(int, int) = lambda(int, (int x, int y) { return x > y ? x : y; });
  
  ASSERT_EQUAL(2, max(1, 2), "max");
  ASSERT_EQUAL(3, max(3, 2), "max");
}

static void test_map(void)
{
  int x[5] = { 1, 2, 3, 4, 5 }, y[5] = { 0 };
  
  map(x, y, 5, lambda(int, (int x) { return x + 1; }));
  for (int i = 0; i < 5; i++) ASSERT_EQUAL(x[i] + 1, y[i], "map");
}

static void test_foldl_int(void)
{
  int x[] = { 1, 2, 3, 4, 5 }, e = 0;
  
  foldl(x, e, 5, lambda(int, (int x, int y) { return x + y; }));
  ASSERT_EQUAL(e, 15, "fold");
}

static void test_foldr_int(void)
{
  char x[] = { 2, 5 }, e = 20;
  
  foldr(x, e, 2, lambda(int, (int x, int y) { return x / y; }));
  ASSERT_EQUAL(e, 2, "foldr");
}

static void test_select(void)
{
  int x[5] = { 1, 2, 3, 4, 5 }, y[5] = { 0 };
  
  select(x, y, 5, lambda(int, (int x) { return x % 2 == 0; }));
  ASSERT_EQUAL(y[0], 2, "select");
  ASSERT_EQUAL(y[1], 4, "select");
}

static void test_forall(void)
{
  int x[] = { 1, 2, 3, 4, 5 }, counter = 0;
  
  forall(x, 5, lambda(void, (int x) { counter++; }));
  ASSERT_EQUAL(counter, 5, "forall");
}

int main(int argc, char **argv)
{ 
  test_lambda();
  test_map();
  test_foldl_int();
  test_select();
  test_foldr_int();
  test_forall();
  return 0;
}