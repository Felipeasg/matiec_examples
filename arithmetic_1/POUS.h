#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

// PROGRAM MY_PROGRAM
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_LOCATED(INT,VAR1)
  __DECLARE_LOCATED(INT,VAR2)
  __DECLARE_LOCATED(INT,VAR3)
  __DECLARE_LOCATED(INT,VAR4)
  __DECLARE_VAR(INT,MUL22_OUT)
  __DECLARE_VAR(INT,ADD24_OUT)

} MY_PROGRAM;

void MY_PROGRAM_init__(MY_PROGRAM *data__, BOOL retain);
// Code part
void MY_PROGRAM_body__(MY_PROGRAM *data__);
#endif //__POUS_H
