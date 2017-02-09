void MY_PROGRAM_init__(MY_PROGRAM *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__IX0_0,data__->INICIAR,retain)
  __INIT_LOCATED_VALUE(data__->INICIAR,__BOOL_LITERAL(TRUE))
  __INIT_LOCATED(BOOL,__IX0_1,data__->PARAR,retain)
  __INIT_LOCATED_VALUE(data__->PARAR,__BOOL_LITERAL(TRUE))
  __INIT_LOCATED(BOOL,__QX0_0,data__->LAMP,retain)
  __INIT_LOCATED_VALUE(data__->LAMP,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->AND15_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void MY_PROGRAM_body__(MY_PROGRAM *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,AND15_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_LOCATED(data__->INICIAR,),
    (BOOL)__GET_LOCATED(data__->PARAR,)));
  __SET_LOCATED(data__->,LAMP,,__GET_VAR(data__->AND15_OUT,));

  goto __end;

__end:
  return;
} // MY_PROGRAM_body__() 





