void MY_PROGRAM_init__(MY_PROGRAM *data__, BOOL retain) {
  __INIT_LOCATED(INT,__IW0_0,data__->VAR1,retain)
  __INIT_LOCATED_VALUE(data__->VAR1,0)
  __INIT_LOCATED(INT,__IW0_1,data__->VAR2,retain)
  __INIT_LOCATED_VALUE(data__->VAR2,0)
  __INIT_LOCATED(INT,__IW0_2,data__->VAR3,retain)
  __INIT_LOCATED_VALUE(data__->VAR3,0)
  __INIT_LOCATED(INT,__QW0_0,data__->VAR4,retain)
  __INIT_LOCATED_VALUE(data__->VAR4,0)
  __INIT_VAR(data__->MUL22_OUT,0,retain)
  __INIT_VAR(data__->ADD24_OUT,0,retain)
}

// Code part
void MY_PROGRAM_body__(MY_PROGRAM *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,MUL22_OUT,,MUL__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_LOCATED(data__->VAR1,),
    (INT)__GET_LOCATED(data__->VAR2,)));
  __SET_VAR(data__->,ADD24_OUT,,ADD__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->MUL22_OUT,),
    (INT)__GET_LOCATED(data__->VAR3,)));
  __SET_LOCATED(data__->,VAR4,,__GET_VAR(data__->ADD24_OUT,));

  goto __end;

__end:
  return;
} // MY_PROGRAM_body__() 





