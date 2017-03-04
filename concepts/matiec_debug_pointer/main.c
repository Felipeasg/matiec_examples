#include <stdio.h>

typedef enum {
	INT_ENUM = 0,
	CHAR_ENUM
} types_enum;

typedef struct {
  int table [6];
} __ARRAY_OF_INT_6;

typedef struct {
  __ARRAY_OF_INT_6 value;
  unsigned char flags;
} __IEC___ARRAY_OF_INT_6_t;

typedef struct {
  __ARRAY_OF_INT_6 *value;
  unsigned char flags;
  __ARRAY_OF_INT_6 fvalue;
} __IEC___ARRAY_OF_INT_6_p;


__IEC___ARRAY_OF_INT_6_t TESTARRAY0;

typedef const struct {
	void *ptr;
	types_enum type;	
} dbgvardsc_t;


static dbgvardsc_t dbgvardsc[] = {
	{&(TESTARRAY0.value.table[0]), INT_ENUM},
	{&(TESTARRAY0.value.table[1]), INT_ENUM},
	{&(TESTARRAY0.value.table[2]), INT_ENUM},
	{&(TESTARRAY0.value.table[3]), INT_ENUM},
	{&(TESTARRAY0.value.table[4]), INT_ENUM},
	{&(TESTARRAY0.value.table[5]), INT_ENUM}
};

int main(int argc, char** argv) {

	{
		static const __ARRAY_OF_INT_6 temp = {{1,2,3,4,5,6}};
		TESTARRAY0.value = temp;
	}

	printf("TESTARRAY0[0]: %d\n", TESTARRAY0.value.table[0]);
	printf("TESTARRAY0[1]: %d\n", TESTARRAY0.value.table[1]);
	printf("TESTARRAY0[2]: %d\n", TESTARRAY0.value.table[2]);
	printf("TESTARRAY0[3]: %d\n", TESTARRAY0.value.table[3]);
	printf("TESTARRAY0[4]: %d\n", TESTARRAY0.value.table[4]);
	printf("TESTARRAY0[5]: %d\n", TESTARRAY0.value.table[5]);

	printf("\n");

	printf("dbgvardsc[0].ptr: %d\n", *(int *)dbgvardsc[0].ptr);
	printf("dbgvardsc[1].ptr: %d\n", *(int *)dbgvardsc[1].ptr);
	printf("dbgvardsc[2].ptr: %d\n", *(int *)dbgvardsc[2].ptr);
	printf("dbgvardsc[3].ptr: %d\n", *(int *)dbgvardsc[3].ptr);
	printf("dbgvardsc[4].ptr: %d\n", *(int *)dbgvardsc[4].ptr);
	printf("dbgvardsc[5].ptr: %d\n", *(int *)dbgvardsc[5].ptr);

	return 0;
}
