FUNCTION_BLOCK myPID
  VAR_INPUT
    SP : REAL := 0.0;
    PV : REAL := 0.0;
  END_VAR
  VAR_OUTPUT
    MV : REAL := 0.0;
  END_VAR
  VAR
    ERROR : REAL := 0.0;
    ERROR_ANT : REAL := 0.0;
  END_VAR
  VAR_INPUT
    KP : REAL := 0.0;
    KI : REAL := 0.0;
    KD : REAL := 0.0;
  END_VAR
  VAR
    DERROR : REAL := 0.0;
    IERROR : REAL := 0.0;
  END_VAR

  ERROR := SP - PV;


  MV := KP*ERROR + KI*IERROR + KD*DERROR;

  DERROR := ERROR - ERROR_ANT;
  IERROR := IERROR + ERROR;

  ERROR_ANT := ERROR;
END_FUNCTION_BLOCK

FUNCTION_BLOCK Scale
  VAR_INPUT
    InMin : REAL;
    InMax : REAL;
    OutMin : REAL;
    OutMax : REAL;
    In : REAL;
  END_VAR
  VAR_OUTPUT
    Out : REAL;
  END_VAR

  Out := (In - InMin) * (OutMax - OutMin) / (InMax - InMin) + OutMin;
END_FUNCTION_BLOCK

PROGRAM My_Program
  VAR CONSTANT
    SP : REAL := 15.0;
    KP : REAL := 1.0;
    KI : REAL := 0.1;
    KD : REAL := 0.2;
  END_VAR
  VAR
    PV_ADC AT %IW0.1 : INT := 0;
    MV_ADC AT %QW0.0 : INT := 0;
  END_VAR
  VAR CONSTANT
    ADC_MIN : INT := 0;
    ADC_MAX : INT := 255;
    TEMP_MIN : REAL := 0.0;
    MV_MIN : REAL := 0.0;
    PWM_MIN : REAL := 0.0;
    TEMP_MAX : REAL := 85.0;
    MV_MAX : REAL := 100.0;
    PWM_MAX : REAL := 255.0;
  END_VAR
  VAR
    myPID0 : myPID;
    Scale0 : Scale;
    Scale1 : Scale;
    INT_TO_REAL3_OUT : REAL;
    INT_TO_REAL4_OUT : REAL;
    INT_TO_REAL30_OUT : REAL;
    REAL_TO_INT31_OUT : INT;
  END_VAR

  INT_TO_REAL3_OUT := INT_TO_REAL(ADC_MIN);
  INT_TO_REAL4_OUT := INT_TO_REAL(ADC_MAX);
  INT_TO_REAL30_OUT := INT_TO_REAL(PV_ADC);
  Scale0(InMin := INT_TO_REAL3_OUT, InMax := INT_TO_REAL4_OUT, OutMin := TEMP_MIN, OutMax := TEMP_MAX, In := INT_TO_REAL30_OUT);
  myPID0(SP := SP, PV := Scale0.Out, KP := KP, KI := KI, KD := KD);
  Scale1(InMin := MV_MIN, InMax := MV_MAX, OutMin := PWM_MIN, OutMax := PWM_MAX, In := myPID0.MV);
  REAL_TO_INT31_OUT := REAL_TO_INT(Scale1.Out);
  MV_ADC := REAL_TO_INT31_OUT;
END_PROGRAM


CONFIGURATION STD_CONF

  RESOURCE STD_RESSOURCE ON PLC
    TASK TaskMain(INTERVAL := T#50ms,PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : My_Program;
  END_RESOURCE
END_CONFIGURATION
