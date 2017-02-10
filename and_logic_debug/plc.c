/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2011  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2007-2011  Laurent Bessard and Edouard Tisserant
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 *
 *
 * Simple PLC run cycle test implementation - prints every located at each cycle
 *
 */

#include "iec_std_lib.h"
#include "iec_types_all.h" 
#include "POUS.h"

#include <stdio.h>

/*for memcpy*/                                                                                                
#include <string.h>                                                                                           
#include <stdio.h>                                                                                            
                                                                                                              
#define BUFFER_SIZE 14                                                                                        
                                                                                                              
/* Atomically accessed variable for buffer state */                                                           
#define BUFFER_FREE 0                                                                                         
#define BUFFER_BUSY 1  

#define __print_BOOL(name) printf("  %s = (BOOL) %s\n",#name, name?"TRUE":"FALSE");
#define __print_SINT(name) printf("  %s = (SINT) %d\n",#name, name);
#define __print_INT(name) printf("  %s = (INT) %d\n",#name, name);
#define __print_DINT(name) printf("  %s = (DINT) %d\n",#name, name);
#define __print_LINT(name) printf("  %s = (LINT) %d\n",#name, name);
#define __print_USINT(name) printf("  %s = (USINT) %u\n",#name, name);
#define __print_UINT(name) printf("  %s = (UINT) %u\n",#name, name);
#define __print_UDINT(name) printf("  %s = (UDINT) %u\n",#name, name);
#define __print_ULINT(name) printf("  %s = (ULINT) %lu\n",#name, name);
#define __print_REAL(name) printf("  %s = (REAL) %f\n",#name, (double)name);
#define __print_LREAL(name) printf("  %s = (LREAL) %f\n",#name, (double)name);
#define __print_TIME(name) {STRING __tmp = __time_to_string(name);__tmp.body[__tmp.len] = 0; printf("  %s = (TIME) %*s\n",#name, __tmp.len, &__tmp.body);}
#define __print_DATE(name) {STRING __tmp = __date_to_string(name);__tmp.body[__tmp.len] = 0; printf("  %s = (DATE) %*s\n",#name, __tmp.len, &__tmp.body);}
#define __print_TOD(name) {STRING __tmp = __tod_to_string(name);__tmp.body[__tmp.len] = 0; printf("  %s = (TOD) %*s\n",#name, __tmp.len, &__tmp.body);}
#define __print_DT(name) {STRING __tmp = __dt_to_string(name);__tmp.body[__tmp.len] = 0; printf("  %s = (DT) %*s\n",#name, __tmp.len, &__tmp.body);}
#define __print_STRING(name) printf("  %s = (STRING) {%d, \"%*s\"}\n",#name, name->len, name->len, &name->body);
#define __print_BYTE(name) printf("  %s = (BYTE) 0x%2.2x\n",#name, name);
#define __print_WORD(name) printf("  %s = (WORD) 0x%4.4x\n",#name, name);
#define __print_DWORD(name) printf("  %s = (DWORD) 0x%8.8x\n",#name, name);
#define __print_LWORD(name) printf("  %s = (LWORD) 0x%16.16lx\n",#name, name);
/*
 * Functions and variables provied by generated C softPLC
 **/ 
void config_run__(int tick);
void config_init__(void);

/*
 *  Functions and variables to export to generated C softPLC
 **/
 
TIME __CURRENT_TIME;

/* The buffer itself */                                                                                       
char debug_buffer[BUFFER_SIZE];                                                                               
                                                                                                              
/* Buffer's cursor*/                                                                                          
static char* buffer_cursor = debug_buffer;                                                                    
static unsigned int retain_offset = 0; 

#define __LOCATED_VAR(type, name, ...) type __##name;
#include "LOCATED_VARIABLES.h"
#undef __LOCATED_VAR
#define __LOCATED_VAR(type, name, ...) type* name = &__##name;
#include "LOCATED_VARIABLES.h"
#undef __LOCATED_VAR



static int tick = 0;

//#define BUFFER_SIZE     1024

//extern MY_PROGRAM INST0;

/***                                                                                                          
 * Declare global variables from resources and conf                                                           
 **/                                                                                                          
/*
	Posso usar o arquivo VARIABLES.csv para declarar as variáveis de debug automaticamente
	
	// Programs
	0;STD_CONF.STD_RESSOURCE.INST0;MY_PROGRAM;
*/

__IEC_INT_t CONFIG__RESETCOUNTERVALUE;                                                                 
//extern PLC_PRG STD_RESSOURCE__INST0;
extern MY_PROGRAM STD_RESSOURCE__INST0;

typedef const struct {                                                                                        
    void *ptr;                                                                                                
    __IEC_types_enum type;                                                                                    
} dbgvardsc_t;  

//SOMENTE VARIÁVEIS QUE NÃO SÃO LOCATED DEFINIDAS NO POUS.h

/*
// PROGRAM MY_PROGRAM
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,INICIAR)
  __DECLARE_VAR(BOOL,PARAR)
  __DECLARE_VAR(BOOL,LAMP)
  __DECLARE_VAR(BOOL,AND15_OUT)

} MY_PROGRAM;

*/
static dbgvardsc_t dbgvardsc[] = {                                                                            
{&(CONFIG__RESETCOUNTERVALUE), INT_ENUM},                                                                    
{&(STD_RESSOURCE__INST0.INICIAR), BOOL_ENUM},
{&(STD_RESSOURCE__INST0.PARAR), BOOL_ENUM}, 
{&(STD_RESSOURCE__INST0.LAMP), BOOL_ENUM}, 
{&(STD_RESSOURCE__INST0.AND15_OUT), BOOL_ENUM}
};      

typedef void(*__for_each_variable_do_fp)(dbgvardsc_t*);                                                       
void __for_each_variable_do(__for_each_variable_do_fp fp)                                                     
{                                                                                                             
    int i;                                                                                                    
    for(i = 0; i < sizeof(dbgvardsc)/sizeof(dbgvardsc_t); i++){                                               
        dbgvardsc_t *dsc = &dbgvardsc[i];                                                                     
        if(dsc->type != UNKNOWN_ENUM)                                                                         
            (*fp)(dsc);                                                                                       
    }                                                                                                         
}   

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

// lib/C/iec_types_all.h:70:#define __IEC_DEBUG_FLAG 0x01   
static inline void BufferIterator(dbgvardsc_t *dsc, int do_debug)                                             
{                                                                                                             
	void *real_value_p = NULL;                                                                                
    void *visible_value_p = NULL;                                                                             
    char flags = 0;                                                                                           
                                                                                                              
    visible_value_p = UnpackVar(dsc, &real_value_p, &flags);                                                  

	printf("flags: %01x\n", flags);    
	printf("visible_value_p: %d\n", *(BOOL *)visible_value_p);
   	printf("forced_value_p: %d\n", *(BOOL *)real_value_p);

    if(flags & ( __IEC_DEBUG_FLAG | __IEC_RETAIN_FLAG)){                                                      
        USINT size = __get_type_enum_size(dsc->type);                                                         

        if(flags & __IEC_DEBUG_FLAG){                                                                         
			printf("DEBUG\n");
			/* copy visible variable to buffer */
            if(do_debug){                                                                                     
                /* compute next cursor positon.                                                               
                   No need to check overflow, as BUFFER_SIZE                                                  
                   is computed large enough */                                                                
                if(dsc->type == STRING_ENUM){                                                                 
                    /* optimization for strings */                                                            
                    size = ((STRING*)visible_value_p)->len + 1;                                               
                }                                                                                        
		
                char* next_cursor = buffer_cursor + size;                                                     
                /* copy data to the buffer */                                                                 
                memcpy(buffer_cursor, visible_value_p, size);                                                 
				printf("buffer_cursor = %d\n", buffer_cursor[0]);	

                /* increment cursor according size*/                                                          
                buffer_cursor = next_cursor;                                                                  
            }                                                                                                 
            /* re-force real value of outputs (M and Q)*/                                                     
            if((flags & __IEC_FORCE_FLAG) && (flags & __IEC_OUTPUT_FLAG)){
				printf("FORCE | OUTPUT\n");
                memcpy(real_value_p, visible_value_p, size);                                                  
            }                                                                                                 
        }                                                                                                     
        if(flags & __IEC_RETAIN_FLAG){                                                                        
			printf("RETAIN\n");
            /* compute next cursor positon*/                                                                  
            unsigned int next_retain_offset = retain_offset + size;                                           
            /* if buffer not full */                                                                          
//            Retain(retain_offset, size, real_value_p);                                                        
            /* increment cursor according size*/                                                              
            retain_offset = next_retain_offset;                                                               
        }                                                                                                     
    } else {
#if 0
		USINT size = __get_type_enum_size(dsc->type);

		/* compute next cursor positon.                                                               
		   No need to check overflow, as BUFFER_SIZE                                                  
		   is computed large enough */
		if(dsc->type == STRING_ENUM){
			/* optimization for strings */
			size = ((STRING*)visible_value_p)->len + 1;
		}

		char* next_cursor = buffer_cursor + size;
		/* copy data to the buffer */
		memcpy(buffer_cursor, visible_value_p, size);
		printf("buffer_cursor = %d\n", buffer_cursor[0]);

		/* increment cursor according size*/
		buffer_cursor = next_cursor;
#endif
	}                                                                    
}   

void DebugIterator(dbgvardsc_t *dsc){                                                                         
    BufferIterator(dsc, 1);                                                                                   
}    

                                                                                                              
void RetainIterator(dbgvardsc_t *dsc){                                                                        
    BufferIterator(dsc, 0);                                                                                   
}   

#define __RegisterDebugVariable_case_t(TYPENAME) \
        case TYPENAME##_ENUM :\
            ((__IEC_##TYPENAME##_t *)varp)->flags |= flags;\
            if(force)\
             ((__IEC_##TYPENAME##_t *)varp)->value = *((TYPENAME *)force);\
            break;
#define __RegisterDebugVariable_case_p(TYPENAME)\
        case TYPENAME##_P_ENUM :\
            ((__IEC_##TYPENAME##_p *)varp)->flags |= flags;\
            if(force)\
             ((__IEC_##TYPENAME##_p *)varp)->fvalue = *((TYPENAME *)force);\
            break;\
        case TYPENAME##_O_ENUM :\
            ((__IEC_##TYPENAME##_p *)varp)->flags |= flags;\
            if(force){\
             ((__IEC_##TYPENAME##_p *)varp)->fvalue = *((TYPENAME *)force);\
             *(((__IEC_##TYPENAME##_p *)varp)->value) = *((TYPENAME *)force);\
            }\
            break;

void RegisterDebugVariable(int idx, void* force)
{
    if(idx  < sizeof(dbgvardsc)/sizeof(dbgvardsc_t)){
        unsigned char flags = force ? __IEC_DEBUG_FLAG | __IEC_FORCE_FLAG :  __IEC_DEBUG_FLAG;
		printf("RegisterDebug flag: %01x\n", flags);		

        dbgvardsc_t *dsc = &dbgvardsc[idx];
        void *varp = dsc->ptr;
        switch(dsc->type){
            __ANY(__RegisterDebugVariable_case_t)
            __ANY(__RegisterDebugVariable_case_p)
        default:
            break;
        }
    }
}

#define __ResetDebugVariablesIterator_case_t(TYPENAME) \
        case TYPENAME##_ENUM :\
            ((__IEC_##TYPENAME##_t *)varp)->flags &= ~(__IEC_DEBUG_FLAG|__IEC_FORCE_FLAG);\
            break;

#define __ResetDebugVariablesIterator_case_p(TYPENAME)\
        case TYPENAME##_P_ENUM :\
        case TYPENAME##_O_ENUM :\
            ((__IEC_##TYPENAME##_p *)varp)->flags &= ~(__IEC_DEBUG_FLAG|__IEC_FORCE_FLAG);\
            break;

void ResetDebugVariablesIterator(dbgvardsc_t *dsc)
{
    /* force debug flag to 0*/
    void *varp = dsc->ptr;
    switch(dsc->type){
        __ANY(__ResetDebugVariablesIterator_case_t)
        __ANY(__ResetDebugVariablesIterator_case_p)
    default:
        break;
    }
}

void ResetDebugVariables(void)
{
    __for_each_variable_do(ResetDebugVariablesIterator);
}


void run()
{

#if 0
	BOOL var;

    *__IX0_1 = (BOOL)1;
	*__IX0_0 = (BOOL)1;
#endif
//	ResetDebugVariables();

	__SET_VAR((&STD_RESSOURCE__INST0)->,INICIAR,,0);
	__SET_VAR((&STD_RESSOURCE__INST0)->,PARAR,,0);

    printf("Tick %d\n",tick);
    config_run__(tick++);



	/* DEBUG */

	if (tick == 1) {
		char force = 1; //__IEC_DEBUG_FLAG; //| __IEC_FORCE_FLAG;

	//	RegisterDebugVariable(0, &flag);
	//	RegisterDebugVariable(1, &flag);
		RegisterDebugVariable(2, &force);
		RegisterDebugVariable(3, &force);
		RegisterDebugVariable(4, &force);
	}

	//__SET_VAR(data__->           ,LAMP   ,,__GET_VAR(data__->AND15_OUT,));
	/* Reset buffer cursor */                                                                         
    buffer_cursor = debug_buffer;
    /* Iterate over all variables to fill debug buffer */                                             
    __for_each_variable_do(DebugIterator);   

	int i = 0;
	for(i = 0; i < BUFFER_SIZE; i++) {
		printf("debug_buffer[%d] = %d\n", i, debug_buffer[i]);
	}
//	__for_each_variable_do(RetainIterator);

}
