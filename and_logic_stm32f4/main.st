PROGRAM program0
  VAR
    LocalVar0 AT %I0.0 : BOOL;
    LocalVar2 AT %I0.1 : BOOL;
    LocalVar1 AT %Q0.0 : BOOL;
    LocalVar3 AT %I0.2 : BOOL;
  END_VAR

  LocalVar1 := NOT(LocalVar2) AND (LocalVar0 OR LocalVar1);
END_PROGRAM


CONFIGURATION configuration0

  RESOURCE resource0 ON PLC
    TASK task_0(INTERVAL := T#500ms,PRIORITY := 0);
    PROGRAM instance_0 WITH task_0 : program0;
  END_RESOURCE
END_CONFIGURATION
