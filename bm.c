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

#include <math.h>
#include <stdlib.h>

#include "bm.h"

static void bm_vector_addition(void)
{
  long v[32768][3] = {}, r[3] = { 0, 0, 0 };
  clock_t t;
    
  for (int i = 0; i < 32768; i++) {
    v[i][0] = i; v[i][1] = i + 1; v[i][2] = i + 2;
  }
  
  t = bm(lambda(void, (void) {
    forall(v, 32768, lambda(void, (long k[]) {
      r[0] += k[0]; r[1] += k[1]; r[2] += k[2];
    }));
  }));
  printf("forall(V+): %d\n", (int)t);
  
  r[0] = r[1] = r[2] = 0;
  
  t = bm(lambda(void, (void) {
    for (int i = 0; i < 32768; i++) {
      r[0] += v[i][0]; r[1] += v[i][1]; r[2] += v[i][2];
    }
  }));
  printf("for(V+): %d\n", (int)t);
}

static inline int is_prime(long p)
{  
  switch (p) {
    case 1: case 2: case 3: return 0;
    default: for (int i = 2; i < sqrt(p); i++) if (p % i == 0) return 0;
  }
  return 1;
}

static void bm_primes(void)
{
  long v[32768] = {}, r1[32768] = {}, r2[32768] = {}, r3[32768] = {};
  clock_t t;
  
  for (int i = 0; i < 32768; i++) v[i] = i;
  
  t = bm(lambda(void, (void) { select(v, r1, 32768, is_prime); }));
  printf("select(is_prime): %d\n", (int)t);
  
  t = bm(lambda(void, (void) {
    select(v, r2, 32768, lambda(int, (long k) { return is_prime(k); }));
  }));
  printf("select(lambda(is_prime)): %d\n", (int)t);
  
  t = bm(lambda(void, (void) {
    for (int i = 0; i < 32768; i++) r3[i] = is_prime(v[i]);
  }));
  printf("for(is_prime): %d\n", (int)t);
}

void bm_suite(void)
{
  bm_vector_addition();
  bm_primes();
}