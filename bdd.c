#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "bdd.h"
#include "lambda.h"

typedef struct bdd_entry_t_ {
  char name[128];  
  closure_f befores[128];
  char it_names[128][128];
  closure_f its[128];
} bdd_entry_t;

static bdd_entry_t specs[128] = {  };
static int ctr = 0;

void run_specs(void)
{
  for (int i = 0; i < ctr; i++) {
    fprintf(stdout, "Describing '%s'\n", specs[i].name);
    specs[i].befores[0]();
    fprintf(stdout, "it %s = ", specs[i].it_names[0]);
    specs[i].its[0]();
    fprintf(stdout, "\n");
  }
}

void describe(const char *spec_name, closure_f f)
{
  assert(ctr < 128);
  assert(NULL != spec_name);
  
  bdd_entry_t *ptr = &specs[ctr];
  strncpy(ptr->name, spec_name, 127);
  f();
  ctr++;
}

void before_each(closure_f f)
{
  assert(NULL != f);
  
  specs[ctr].befores[0] = f;
}

void it(const char *description, closure_f f)
{
  assert(NULL != description);
  assert(NULL != f);
  
  specs[ctr].its[0] = f;
  strncpy(specs[ctr].it_names[0], description, 127);
}