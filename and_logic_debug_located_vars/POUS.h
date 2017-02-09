#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

// PROGRAM MY_PROGRAM
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_LOCATED(BOOL,INICIAR)
  __DECLARE_LOCATED(BOOL,PARAR)
  __DECLARE_LOCATED(BOOL,LAMP)
  __DECLARE_VAR(BOOL,AND15_OUT)

} MY_PROGRAM;

void MY_PROGRAM_init__(MY_PROGRAM *data__, BOOL retain);
// Code part
void MY_PROGRAM_body__(MY_PROGRAM *data__);
#endif //__POUS_H
