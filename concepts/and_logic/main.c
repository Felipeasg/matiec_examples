#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "accessor.h"
#include "iec_std_lib.h"

//NEED TO DECLARE!!!!
TIME __CURRENT_TIME;

__DECLARE_ARRAY_TYPE(__ARRAY_OF_SINT_5,SINT,[5])

typedef struct {
	// PROGRAM Interface - IN, OUT, IN_OUT variables

	// PROGRAM private variables - TEMP, private and located variables
	__DECLARE_VAR(BOOL,INICIAR)
	__DECLARE_VAR(BOOL,PARAR)
	__DECLARE_VAR(BOOL,LAMP)
	__DECLARE_VAR(SINT,TEST1)
	__DECLARE_VAR(INT,TEST2)
	__DECLARE_VAR(DINT,TEST3)
	__DECLARE_VAR(LINT,TEST4)
	__DECLARE_VAR(USINT,TEST5)
	__DECLARE_VAR(UINT,TEST6)
	__DECLARE_VAR(UDINT,TEST7)
	__DECLARE_VAR(ULINT,TEST8)
	__DECLARE_VAR(REAL,TEST9)
	__DECLARE_VAR(LREAL,TEST10)
	__DECLARE_VAR(TIME,TEST11)
	__DECLARE_VAR(TIME,TEST12)
	__DECLARE_VAR(TIME,TEST13)
	__DECLARE_VAR(DATE,TEST14)
	__DECLARE_VAR(TOD,TEST15)
	__DECLARE_VAR(DT,TEST16)
	__DECLARE_VAR(STRING,TEST17)
	__DECLARE_VAR(BYTE,TEST18)
	__DECLARE_VAR(WORD,TEST19)
	__DECLARE_VAR(DWORD,TEST20)
	__DECLARE_VAR(LWORD,TEST21)
	__DECLARE_VAR(__ARRAY_OF_SINT_5,TESTARRAY)
} MY_PROGRAM;

void MY_PROGRAM_init__(MY_PROGRAM *data__, BOOL retain) {
	__INIT_VAR(data__->INICIAR,__BOOL_LITERAL(FALSE),retain)
										  __INIT_VAR(data__->PARAR,__BOOL_LITERAL(FALSE),retain)
										  __INIT_VAR(data__->LAMP,__BOOL_LITERAL(FALSE),retain)
										  __INIT_VAR(data__->TEST1,15,retain)
										  __INIT_VAR(data__->TEST2,15,retain)
										  __INIT_VAR(data__->TEST3,15,retain)
										  __INIT_VAR(data__->TEST4,15,retain)
										  __INIT_VAR(data__->TEST5,15,retain)
										  __INIT_VAR(data__->TEST6,15,retain)
										  __INIT_VAR(data__->TEST7,15,retain)
										  __INIT_VAR(data__->TEST8,15,retain)
										  __INIT_VAR(data__->TEST9,15.0,retain)
										  __INIT_VAR(data__->TEST10,15.0,retain)
										  __INIT_VAR(data__->TEST11,__time_to_timespec(1, 0, 14.7, 0, 0, 0),retain)
										  __INIT_VAR(data__->TEST12,__time_to_timespec(1, 14, 0, 0, 0, 0),retain)
										  __INIT_VAR(data__->TEST13,__time_to_timespec(1, 3.5, 18, 12, 14, 5),retain)
										  __INIT_VAR(data__->TEST14,__date_to_timespec(25, 6, 1984),retain)
										  __INIT_VAR(data__->TEST15,__tod_to_timespec(55.36, 36, 15),retain)
										  __INIT_VAR(data__->TEST16,__dt_to_timespec(55.36, 36, 15, 25, 6, 1984),retain)
										  __INIT_VAR(data__->TEST17,__STRING_LITERAL(5,"HELLO"),retain)
										  __INIT_VAR(data__->TEST18,15,retain)
										  __INIT_VAR(data__->TEST19,15,retain)
										  __INIT_VAR(data__->TEST20,15,retain)
										  __INIT_VAR(data__->TEST21,12315555,retain)

										  {
		static const __ARRAY_OF_SINT_5 temp = {{5,4,3,2,1}};
		__SET_VAR(data__->,TESTARRAY,,temp);
										  }
}

MY_PROGRAM STD_RESSOURCE__INST0;



typedef const struct {                                                                                        
	void *ptr;
	__IEC_types_enum type;
} dbgvardsc_t;  

static dbgvardsc_t dbgvardsc[] = {                                                                            
		{&(STD_RESSOURCE__INST0.INICIAR), BOOL_ENUM},
		{&(STD_RESSOURCE__INST0.PARAR), BOOL_ENUM},
		{&(STD_RESSOURCE__INST0.LAMP), BOOL_ENUM},
		{&(STD_RESSOURCE__INST0.TEST1), SINT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST2), INT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST3), DINT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST4), LINT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST5), USINT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST6), UINT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST7), UDINT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST8), ULINT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST9), REAL_ENUM},
		{&(STD_RESSOURCE__INST0.TEST10), LREAL_ENUM},
		{&(STD_RESSOURCE__INST0.TEST11), TIME_ENUM},
		{&(STD_RESSOURCE__INST0.TEST12), TIME_ENUM},
		{&(STD_RESSOURCE__INST0.TEST13), TIME_ENUM},
		{&(STD_RESSOURCE__INST0.TEST14), DATE_ENUM},
		{&(STD_RESSOURCE__INST0.TEST15), TOD_ENUM},
		{&(STD_RESSOURCE__INST0.TEST16), DT_ENUM},
		{&(STD_RESSOURCE__INST0.TEST17), STRING_ENUM},
		{&(STD_RESSOURCE__INST0.TEST18), BYTE_ENUM},
		{&(STD_RESSOURCE__INST0.TEST19), WORD_ENUM},
		{&(STD_RESSOURCE__INST0.TEST20), DWORD_ENUM},
		{&(STD_RESSOURCE__INST0.TEST21), LWORD_ENUM},
		{&((&STD_RESSOURCE__INST0)->TESTARRAY.value.table[0]), SINT_ENUM},
		{&((&STD_RESSOURCE__INST0)->TESTARRAY.value.table[1]), SINT_ENUM},
		{&((&STD_RESSOURCE__INST0)->TESTARRAY.value.table[2]), SINT_ENUM},
		{&((&STD_RESSOURCE__INST0)->TESTARRAY.value.table[3]), SINT_ENUM},
		{&((&STD_RESSOURCE__INST0)->TESTARRAY.value.table[4]), SINT_ENUM},
};      


#define __Unpack_case_t(TYPENAME)\
		case TYPENAME##_ENUM :\
		*flags = ((__IEC_##TYPENAME##_t *)varp)->flags; \
		forced_value_p = *real_value_p = &((__IEC_##TYPENAME##_t *)varp)->value; \
		break;

#define __Unpack_case_p(TYPENAME)\
		case TYPENAME##_O_ENUM :\
		*flags = __IEC_OUTPUT_FLAG;\
		case TYPENAME##_P_ENUM :\
		*flags |= ((__IEC_##TYPENAME##_p *)varp)->flags;\
		*real_value_p = ((__IEC_##TYPENAME##_p *)varp)->value;\
		forced_value_p = &((__IEC_##TYPENAME##_p *)varp)->fvalue;\
		break;


void* UnpackVar(dbgvardsc_t *dsc, void **real_value_p, char *flags)
{                                                                                                             
	void *varp = dsc->ptr;
	void *forced_value_p = NULL;
	*flags = 0;
	/* find data to copy*/

	// lib/C/iec_types_all.h:26:#define __ANY(DO) 
	switch(dsc->type){                                                                                        
	__ANY(__Unpack_case_t)
        												__ANY(__Unpack_case_p)
	default:
		break;
	}
	if (*flags & __IEC_FORCE_FLAG)
		return forced_value_p;
	return *real_value_p;
}       



#define __print_BOOL(name) printf("(BOOL) %s\n", name?"TRUE":"FALSE");
#define __print_SINT(name) printf("(SINT) %d\n", name);
#define __print_INT(name) printf("(INT) %d\n", name);
#define __print_DINT(name) printf("(DINT) %d\n", name);
#define __print_LINT(name) printf("(LINT) %d\n", name);
#define __print_USINT(name) printf("(USINT) %u\n", name);
#define __print_UINT(name) printf("(UINT) %u\n", name);
#define __print_UDINT(name) printf("(UDINT) %u\n", name);
#define __print_ULINT(name) printf("(ULINT) %lu\n", name);
#define __print_REAL(name) printf("(REAL) %f\n", (double)name);
#define __print_LREAL(name) printf("(LREAL) %f\n", (double)name);
#define __print_TIME(name)  STRING __tmp = __time_to_string(name);\
		__tmp.body[__tmp.len] = 0;\
		printf("(TIME) %*s\n", __tmp.len, &__tmp.body);//{STRING __tmp = __time_to_string(name);__tmp.body[__tmp.len] = 0; printf("(TIME) %*s\n", __tmp.len, &__tmp.body);}
#define __print_DATE(name) STRING __tmp = __date_to_string(name);\
		__tmp.body[__tmp.len] = 0;\
		printf("(DATE) %*s\n", __tmp.len, &__tmp.body);
#define __print_TOD(name) STRING __tmp = __tod_to_string(name);\
		__tmp.body[__tmp.len] = 0;\
		printf("(TOD) %*s\n", __tmp.len, &__tmp.body);
#define __print_DT(name) STRING __tmp = __dt_to_string(name);\
		__tmp.body[__tmp.len] = 0;\
		printf("(DT) %*s\n", __tmp.len, &__tmp.body);
#define __print_STRING(name) printf("(STRING) %s\n", &name);//printf("(STRING) {%d, \"%*s\"}\n", name->len, name->len, &name->body);
#define __print_BYTE(name) printf("(BYTE) 0x%2.2x\n", name);
#define __print_WORD(name) printf("(WORD) 0x%4.4x\n", name);
#define __print_DWORD(name) printf("(DWORD) 0x%8.8x\n", name);
#define __print_LWORD(name) printf("(LWORD) 0x%16.16lx\n", name);


#define __printVar(TYPENAME,...)\
		case TYPENAME##_ENUM : {\
			IEC_##TYPENAME var;\
			memcpy(&var, real_value_p, sizeof(IEC_##TYPENAME));\
			__print_##TYPENAME(var); }\
			printf(" '-> size: %d\n", size);\
			break;

#define BUFFER_SIZE 180
/* The buffer itself */
char debug_buffer[BUFFER_SIZE];

/* Buffer's cursor*/
static char* buffer_cursor = debug_buffer;

static inline void BufferIterator(dbgvardsc_t *dsc)                                             
{          
	void *real_value_p = NULL;                                                                                
	void *visible_value_p = NULL;
	char flags = 0;

	visible_value_p = UnpackVar(dsc, &real_value_p, &flags);

	USINT size = __get_type_enum_size(dsc->type);

	if(dsc->type == STRING_ENUM){
		/* optimization for strings */
		size = ((STRING*)visible_value_p)->len + 1;
	}

	char* next_cursor = buffer_cursor + size;
	/* copy data to the buffer */
	memcpy(buffer_cursor, visible_value_p, size);
#ifdef PRINT_DEBUG
	printf("buffer_cursor = %d\n", buffer_cursor[0]);
#endif

	/* increment cursor according size*/
	buffer_cursor = next_cursor;
	switch(dsc->type) {
	__ANY(__printVar);
	default:
		break;
	}

#if 0
	USINT size = __get_type_enum_size(dsc->type);

	if(dsc->type == BOOL_ENUM) {
		BOOL var = 0;
		memcpy(&var, real_value_p, sizeof(BOOL));
		printf("BOOL var: %s - size: %d\n", var ? "TRUE" : "FALSE", size);
	}
	else if(dsc->type == SINT_ENUM) {
		SINT var = 0;
		memcpy(&var, real_value_p, sizeof(SINT));
		printf("SINT var: %d - size: %d\n", var);
	} else if(dsc->type == INT_ENUM) {
		INT var = 0;
		memcpy(&var, real_value_p, sizeof(INT));
		printf("INT var: %d - size: %d\n", var);
	} else if(dsc->type == DINT_ENUM) {
		DINT var = 0;
		memcpy(&var, real_value_p, sizeof(DINT));
		printf("DINT var: %d - size: %d\n", var);
	} else if(dsc->type == ULINT_ENUM) {
		ULINT var = 0;
		memcpy(&var, real_value_p, sizeof(ULINT));
		printf("ULINT var: %d - size: %d\n", var);
	} else if(dsc->type == REAL_ENUM) {
		REAL var = 0;
		memcpy(&var, real_value_p, sizeof(REAL));
		printf("REAL var: %f - size: %d\n", var);
	} else if(dsc->type == LREAL_ENUM) {
		LREAL var = 0;
		memcpy(&var, real_value_p, sizeof(LREAL));
		printf("LREAL var: %f - size: %d\n", var);
	}
#endif
}

int main(int argc,char **argv) {
	BOOL retain;


	MY_PROGRAM_init__(&STD_RESSOURCE__INST0, retain);

	int i;
	for(i = 0; i < sizeof(dbgvardsc)/sizeof(dbgvardsc_t); i++){
		dbgvardsc_t *dsc = &dbgvardsc[i];
		if(dsc->type != UNKNOWN_ENUM)
			BufferIterator(dsc);
	}

	for(int i = 0; i < BUFFER_SIZE; i++) {
		printf("debug_buffer[%d] = %d\n", i, debug_buffer[i]);
	}

	return 0;
}
