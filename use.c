#include <stdio.h>

#include "lambda.h"

static void adder(void)
{
  int (*adder)(int, int) = lambda(int, (int x, int y) { return x + y; });
  
  printf("adder(1, 2): %d\n", adder(1, 2));
  printf("adder(3, 4): %d\n", adder(3, 4));
}

static void memo_closure(void)
{
  int (*memo)(int) = lambda(int, (int new) {
    static int _memo = 0;
    
    int old = _memo;
    _memo = new;
    return old;
  });
  
  printf("memo(1): %d\n", memo(1));
  printf("memo(2): %d\n", memo(2));
  printf("memo(3): %d\n", memo(3));
}

void use_suite(void)
{
  adder();
  memo_closure();
}