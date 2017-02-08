void MYPID_init__(MYPID *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SP,0.0,retain)
  __INIT_VAR(data__->PV,0.0,retain)
  __INIT_VAR(data__->MV,0.0,retain)
  __INIT_VAR(data__->ERROR,0.0,retain)
  __INIT_VAR(data__->ERROR_ANT,0.0,retain)
  __INIT_VAR(data__->KP,0.0,retain)
  __INIT_VAR(data__->KI,0.0,retain)
  __INIT_VAR(data__->KD,0.0,retain)
  __INIT_VAR(data__->DERROR,0.0,retain)
  __INIT_VAR(data__->IERROR,0.0,retain)
}

// Code part
void MYPID_body__(MYPID *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,ERROR,,(__GET_VAR(data__->SP,) - __GET_VAR(data__->PV,)));
  __SET_VAR(data__->,MV,,(((__GET_VAR(data__->KP,) * __GET_VAR(data__->ERROR,)) + (__GET_VAR(data__->KI,) * __GET_VAR(data__->IERROR,))) + (__GET_VAR(data__->KD,) * __GET_VAR(data__->DERROR,))));
  __SET_VAR(data__->,DERROR,,(__GET_VAR(data__->ERROR,) - __GET_VAR(data__->ERROR_ANT,)));
  __SET_VAR(data__->,IERROR,,(__GET_VAR(data__->IERROR,) + __GET_VAR(data__->ERROR,)));
  __SET_VAR(data__->,ERROR_ANT,,__GET_VAR(data__->ERROR,));

  goto __end;

__end:
  return;
} // MYPID_body__() 





void SCALE_init__(SCALE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->INMIN,0,retain)
  __INIT_VAR(data__->INMAX,0,retain)
  __INIT_VAR(data__->OUTMIN,0,retain)
  __INIT_VAR(data__->OUTMAX,0,retain)
  __INIT_VAR(data__->IN,0,retain)
  __INIT_VAR(data__->OUT,0,retain)
}

// Code part
void SCALE_body__(SCALE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,OUT,,((((__GET_VAR(data__->IN,) - __GET_VAR(data__->INMIN,)) * (__GET_VAR(data__->OUTMAX,) - __GET_VAR(data__->OUTMIN,))) / (__GET_VAR(data__->INMAX,) - __GET_VAR(data__->INMIN,))) + __GET_VAR(data__->OUTMIN,)));

  goto __end;

__end:
  return;
} // SCALE_body__() 





void MY_PROGRAM_init__(MY_PROGRAM *data__, BOOL retain) {
  __INIT_VAR(data__->SP,15.0,retain)
  __INIT_VAR(data__->KP,1.0,retain)
  __INIT_VAR(data__->KI,0.1,retain)
  __INIT_VAR(data__->KD,0.2,retain)
  __INIT_LOCATED(INT,__IW0_1,data__->PV_ADC,retain)
  __INIT_LOCATED_VALUE(data__->PV_ADC,0)
  __INIT_LOCATED(INT,__QW0_0,data__->MV_ADC,retain)
  __INIT_LOCATED_VALUE(data__->MV_ADC,0)
  __INIT_VAR(data__->ADC_MIN,0,retain)
  __INIT_VAR(data__->ADC_MAX,255,retain)
  __INIT_VAR(data__->TEMP_MIN,0.0,retain)
  __INIT_VAR(data__->MV_MIN,0.0,retain)
  __INIT_VAR(data__->PWM_MIN,0.0,retain)
  __INIT_VAR(data__->TEMP_MAX,85.0,retain)
  __INIT_VAR(data__->MV_MAX,100.0,retain)
  __INIT_VAR(data__->PWM_MAX,255.0,retain)
  MYPID_init__(&data__->MYPID0,retain);
  SCALE_init__(&data__->SCALE0,retain);
  SCALE_init__(&data__->SCALE1,retain);
  __INIT_VAR(data__->INT_TO_REAL3_OUT,0,retain)
  __INIT_VAR(data__->INT_TO_REAL4_OUT,0,retain)
  __INIT_VAR(data__->INT_TO_REAL30_OUT,0,retain)
  __INIT_VAR(data__->REAL_TO_INT31_OUT,0,retain)
}

// Code part
void MY_PROGRAM_body__(MY_PROGRAM *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,INT_TO_REAL3_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->ADC_MIN,)));
  __SET_VAR(data__->,INT_TO_REAL4_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->ADC_MAX,)));
  __SET_VAR(data__->,INT_TO_REAL30_OUT,,INT_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_LOCATED(data__->PV_ADC,)));
  __SET_VAR(data__->SCALE0.,INMIN,,__GET_VAR(data__->INT_TO_REAL3_OUT,));
  __SET_VAR(data__->SCALE0.,INMAX,,__GET_VAR(data__->INT_TO_REAL4_OUT,));
  __SET_VAR(data__->SCALE0.,OUTMIN,,__GET_VAR(data__->TEMP_MIN,));
  __SET_VAR(data__->SCALE0.,OUTMAX,,__GET_VAR(data__->TEMP_MAX,));
  __SET_VAR(data__->SCALE0.,IN,,__GET_VAR(data__->INT_TO_REAL30_OUT,));
  SCALE_body__(&data__->SCALE0);
  __SET_VAR(data__->MYPID0.,SP,,__GET_VAR(data__->SP,));
  __SET_VAR(data__->MYPID0.,PV,,__GET_VAR(data__->SCALE0.OUT,));
  __SET_VAR(data__->MYPID0.,KP,,__GET_VAR(data__->KP,));
  __SET_VAR(data__->MYPID0.,KI,,__GET_VAR(data__->KI,));
  __SET_VAR(data__->MYPID0.,KD,,__GET_VAR(data__->KD,));
  MYPID_body__(&data__->MYPID0);
  __SET_VAR(data__->SCALE1.,INMIN,,__GET_VAR(data__->MV_MIN,));
  __SET_VAR(data__->SCALE1.,INMAX,,__GET_VAR(data__->MV_MAX,));
  __SET_VAR(data__->SCALE1.,OUTMIN,,__GET_VAR(data__->PWM_MIN,));
  __SET_VAR(data__->SCALE1.,OUTMAX,,__GET_VAR(data__->PWM_MAX,));
  __SET_VAR(data__->SCALE1.,IN,,__GET_VAR(data__->MYPID0.MV,));
  SCALE_body__(&data__->SCALE1);
  __SET_VAR(data__->,REAL_TO_INT31_OUT,,REAL_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->SCALE1.OUT,)));
  __SET_LOCATED(data__->,MV_ADC,,__GET_VAR(data__->REAL_TO_INT31_OUT,));

  goto __end;

__end:
  return;
} // MY_PROGRAM_body__() 





