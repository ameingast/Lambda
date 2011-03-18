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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bm.h"

#define BM_SIZE       32768
#define BM_SMALL_SIZE 32
#define BM_ITS        16

static void bm_vector_addition(void)
{
  long v[BM_SIZE][3] = { { 0 } }, r[3] = { 0 };
  float t1, t2;
    
  for (int i = 0; i < BM_SIZE; i++) v[i][0] = v[i][1] = v[i][2] = i;
  
  t1 = bm(BM_ITS, lambda(void, (void) {
    forall(v, BM_SIZE, lambda(void, (long k[]) {
      r[0] += k[0]; r[1] += k[1]; r[2] += k[2];
    }));
  }));
  
  r[0] = r[1] = r[2] = 0;
  t2 = bm(BM_ITS, lambda(void, (void) {
    for (int i = 0; i < BM_SIZE; i++) {
      r[0] += v[i][0]; r[1] += v[i][1]; r[2] += v[i][2];
    }
  }));
  
  printf("[+]:\tforall: %.3f | for: %.3f :: speedup: %.3f\n", t1, t2, t1/t2);
}

static void bm_arith(void)
{
  long v[BM_SIZE] = { 0 }, r = 0;
  float t1, t2;
  
  for (int i = 0; i < BM_SIZE; i++) v[i] = i;
  
  t1 = bm(BM_ITS, lambda(void, (void) {
    forall(v, BM_SIZE, lambda(void, (long l) { r += l; }));
  }));
  
  r = 0;
  t2 = bm(BM_ITS, lambda(void, (void) {
    for (int i = 0; i < BM_SIZE; i++) r += i;
  }));
  
  printf("+:\tforall: %.3f | for: %.3f :: speedup: %.3f\n", t1, t2, t1/t2);
}

static inline int is_prime(long p)
{ 
  if (p < 4) return 0;
  else for (int i = 2; i < sqrt(p); i++) if (p % i == 0) return 0;
  return 1;
}

static inline long fib(long k)
{
  return (k < 2) ? 1 : fib(k - 1) + fib(k - 2);
}

static void bm_primes(void)
{
  long v[BM_SIZE] = { 0 }, r1[BM_SIZE] = { 0 }, r2[BM_SIZE] = { 0 };
  float t1, t2;
  
  for (int i = 0; i < BM_SIZE; i++) v[i] = i;
  
  t1 = bm(BM_ITS, lambda(void, (void) { select(v, r1, BM_SIZE, is_prime); }));
    
  t2 = bm(BM_ITS, lambda(void, (void) {
    for (int i = 0; i < BM_SIZE; i++) r2[i] = is_prime(v[i]);
  }));
  
  printf("prime:\tselect: %.3f | for: %.3f :: speedup: %.3f\n", t1, t2, t1/t2);
}

static void bm_fib_memo(void)
{
  long v[BM_SMALL_SIZE] = { 0 }, r1[BM_SMALL_SIZE] = { 0 }, r2[BM_SMALL_SIZE] = { 0 };
  float t1, t2;
  
  for (int i = 0; i < BM_SMALL_SIZE; i++) v[i] = i;
    
  long (*fib_memo)(long) = lambda(long, (long p) {
    static long fib_cache[BM_SMALL_SIZE] = { -1 };
    
    if (p < 2) 
      return 1;
    if (fib_cache[p] != -1)
      return fib_cache[p];
    else
      return fib_cache[p] = fib_memo(p - 1) + fib_memo(p - 2);
  });
  
  t1 = bm(BM_ITS, lambda(void, (void) { map(v, r1, BM_SMALL_SIZE, fib_memo); }));
  
  t2 = bm(BM_ITS, lambda(void, (void) {
    for (int i = 0; i < BM_SMALL_SIZE; i++)
      r2[i] = fib(v[i]);
  }));
  
  printf("fib:\tmap: %.3f | for: %.3f :: speedup: %.3f\n", t1, t2, t1/t2);
}

void bm_suite(void)
{
  bm_arith();
  bm_vector_addition();
  bm_primes();
  bm_fib_memo();
}