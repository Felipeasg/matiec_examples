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

static int tick = 0;

//#define BUFFER_SIZE     1024

//extern MY_PROGRAM INST0;

/***                                                                                                          
 * Declare global variables from resources and conf                                                           
 **/                                                                                                          
extern __IEC_INT_t CONFIG__RESETCOUNTERVALUE;                                                                 
//extern PLC_PRG STD_RESSOURCE__INST0;
extern MY_PROGRAM STD_RESSOURCE__INST0;

typedef const struct {                                                                                        
    void *ptr;                                                                                                
    __IEC_types_enum type;                                                                                    
} dbgvardsc_t;  

static dbgvardsc_t dbgvardsc[] = {                                                                            
//{&(CONFIG__RESETCOUNTERVALUE), INT_ENUM},                                                                     
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

void* UnpackVar(dbgvardsc_t *dsc, void **real_value_p, char *flags)                                           
{                                                                                                             
    void *varp = dsc->ptr;                                                                                    
    void *forced_value_p = NULL;                                                                              
    *flags = 0;                                                                                               
    /* find data to copy*/                                                                                    
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
	printf("\n");
	printf("BufferIterator\n");
    
	void *real_value_p = NULL;                                                                                
    void *visible_value_p = NULL;                                                                             
    char flags = 0;                                                                                           
                                                                                                              
    visible_value_p = UnpackVar(dsc, &real_value_p, &flags);                                                  
            
	printf("flags: %u\n", flags);                                                                                                  
    if(flags & ( __IEC_DEBUG_FLAG | __IEC_RETAIN_FLAG)){                                                      
		printf("__IEC_DEBUG_FLAG | __IEC_RETAIN_FLAG\n");
        USINT size = __get_type_enum_size(dsc->type);                                                         
		printf("\n");
		printf("size %u\n", size);

        if(flags & __IEC_DEBUG_FLAG){                                                                         
            printf("__IEC_DEBUG_FLAG\n");

			/* copy visible variable to buffer */;                                                            
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

				printf("buffer_cursor[0] = %u\n", buffer_cursor[0]);
				printf("buffer_cursor[1] = %u\n", buffer_cursor[1]);
				printf("buffer_cursor[2] = %u\n", buffer_cursor[2]);
				printf("buffer_cursor[3] = %u\n", buffer_cursor[3]);

	
                /* increment cursor according size*/                                                          
                buffer_cursor = next_cursor;                                                                  
            }                                                                                                 
            /* re-force real value of outputs (M and Q)*/                                                     
            if((flags & __IEC_FORCE_FLAG) && (flags & __IEC_OUTPUT_FLAG)){                                    
                memcpy(real_value_p, visible_value_p, size);                                                  
            }                                                                                                 
        }                                                                                                     
        if(flags & __IEC_RETAIN_FLAG){                                                                        
     		printf("__IEC_RETAIN_FLAG\n");

            /* compute next cursor positon*/                                                                  
            unsigned int next_retain_offset = retain_offset + size;                                           
            /* if buffer not full */                                                                          
//            Retain(retain_offset, size, real_value_p);                                                        
            /* increment cursor according size*/                                                              
            retain_offset = next_retain_offset;                                                               
        }                                                                                                     
    }                                                                                                         
}   

void DebugIterator(dbgvardsc_t *dsc){                                                                         
    BufferIterator(dsc, 1);                                                                                   
}    

                                                                                                              
void RetainIterator(dbgvardsc_t *dsc){                                                                        
    BufferIterator(dsc, 0);                                                                                   
}   

void run()
{


	BOOL var;

    *__IX0_1 = (BOOL)1;
	*__IX0_0 = (BOOL)1;

#if 0
	visible_value_p = UnpackVar(&dbgvardsc[0], &real_value_p, &flags);
	USINT size = __get_type_enum_size(dbgvardsc[0].type);

	memcpy(&var, real_value_p, size);

	printf("size %u\n", (USINT)size);
	printf("var %s\n", var? "TRUE":"FALSE");
//	printf("STD_RESSOURCE__INST0.INICIAR: %u\n", (int *)real_value_p);
#endif


    printf("Tick %d\n",tick);
    config_run__(tick++);

    printf("IX0.0 = %s\n", *__IX0_0? "TRUE" : "FALSE");
    printf("IX0.1 = %s\n", *__IX0_1? "TRUE" : "FALSE");
    printf("QX0.0 = %s\n", *__QX0_0? "TRUE" : "FALSE");

	printf("\n");

	printf("INICIAR: %s\n", (BOOL)__GET_LOCATED(STD_RESSOURCE__INST0.INICIAR,)? "TRUE" : "FALSE");
	printf("PARAR: %s\n", (BOOL)__GET_LOCATED(STD_RESSOURCE__INST0.PARAR,)? "TRUE" : "FALSE");
	printf("LAMP: %s\n", (BOOL)__GET_LOCATED(STD_RESSOURCE__INST0.LAMP,)? "TRUE" : "FALSE");

	printf("\n");

#if 1
	/* Reset buffer cursor */                                                                         
    buffer_cursor = debug_buffer;                                                                     
    /* Iterate over all variables to fill debug buffer */                                             
    __for_each_variable_do(DebugIterator);   
//	__for_each_variable_do(RetainIterator);
#endif

}

