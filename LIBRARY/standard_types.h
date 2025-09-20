#ifndef STANDARD_TYPES_H
#define STANDARD_TYPES_H

typedef short unsigned int u16;
typedef short signed int s16;
typedef long unsigned int u32;
typedef long signed int s32;
typedef long long unsigned int u64;
typedef long long signed int s64;
typedef signed char s8;
typedef unsigned char u8;
typedef long double d64;
typedef double d128;
typedef float f32;

/* NULL pointer definition */
#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif
/*
 * False value definition
 */
#ifndef False
#define False (0u)
#endif

/*
 * True value definition
 */
#ifndef True
#define True (1u)
#endif

/*
 * boolean data type definition
 */
typedef unsigned char bool;

/* Logical value declaration */

typedef enum{
	LOW = (0u), HIGH = (1u)
}Logical_Value;

#endif
