#include "bm.h"

static void bm_vector_addition(void)
{
  long v[32768][3] = {}, r[3] = { 0, 0, 0 };
  
  for (int i = 0; i < 32768; i++) {
    v[i][0] = i; v[i][1] = i + 1; v[i][2] = i + 2;
  }
  
  BM(stdout, "forall()", {
    forall(v, 32768, lambda(void, (long k[]) {
      r[0] += k[0]; r[1] += k[1]; r[2] += k[2];
    }));
  });
  
  r[0] = r[1] = r[2] = 0;
  
  BM(stdout, "for()", {
    for (int i = 0; i < 32768; i++) {
      r[0] += v[i][0]; r[1] += v[i][1]; r[2] += v[i][2];
    }
  });
}

void bm_suite(void)
{
  bm_vector_addition();
}