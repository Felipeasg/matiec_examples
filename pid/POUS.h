#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

// FUNCTION_BLOCK MYPID
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(REAL,SP)
  __DECLARE_VAR(REAL,PV)
  __DECLARE_VAR(REAL,MV)
  __DECLARE_VAR(REAL,KP)
  __DECLARE_VAR(REAL,KI)
  __DECLARE_VAR(REAL,KD)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,ERROR)
  __DECLARE_VAR(REAL,ERROR_ANT)
  __DECLARE_VAR(REAL,DERROR)
  __DECLARE_VAR(REAL,IERROR)

} MYPID;

void MYPID_init__(MYPID *data__, BOOL retain);
// Code part
void MYPID_body__(MYPID *data__);
// FUNCTION_BLOCK SCALE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(REAL,INMIN)
  __DECLARE_VAR(REAL,INMAX)
  __DECLARE_VAR(REAL,OUTMIN)
  __DECLARE_VAR(REAL,OUTMAX)
  __DECLARE_VAR(REAL,IN)
  __DECLARE_VAR(REAL,OUT)

  // FB private variables - TEMP, private and located variables

} SCALE;

void SCALE_init__(SCALE *data__, BOOL retain);
// Code part
void SCALE_body__(SCALE *data__);
// PROGRAM MY_PROGRAM
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,SP)
  __DECLARE_VAR(REAL,KP)
  __DECLARE_VAR(REAL,KI)
  __DECLARE_VAR(REAL,KD)
  __DECLARE_LOCATED(INT,PV_ADC)
  __DECLARE_LOCATED(INT,MV_ADC)
  __DECLARE_VAR(INT,ADC_MIN)
  __DECLARE_VAR(INT,ADC_MAX)
  __DECLARE_VAR(REAL,TEMP_MIN)
  __DECLARE_VAR(REAL,MV_MIN)
  __DECLARE_VAR(REAL,PWM_MIN)
  __DECLARE_VAR(REAL,TEMP_MAX)
  __DECLARE_VAR(REAL,MV_MAX)
  __DECLARE_VAR(REAL,PWM_MAX)
  MYPID MYPID0;
  SCALE SCALE0;
  SCALE SCALE1;
  __DECLARE_VAR(REAL,INT_TO_REAL3_OUT)
  __DECLARE_VAR(REAL,INT_TO_REAL4_OUT)
  __DECLARE_VAR(REAL,INT_TO_REAL30_OUT)
  __DECLARE_VAR(INT,REAL_TO_INT31_OUT)

} MY_PROGRAM;

void MY_PROGRAM_init__(MY_PROGRAM *data__, BOOL retain);
// Code part
void MY_PROGRAM_body__(MY_PROGRAM *data__);
#endif //__POUS_H
