#ifndef _LAMBDA_BDD_H_
#define _LAMBDA_BDD_H_

typedef void(*closure_f)(void);
typedef void(*it_f)(const char *description, closure_f);

void run_specs(void);

void describe(const char *spec_name, closure_f closure);
void before_each(closure_f closure);
void it(const char *description, closure_f f);

#endif 
