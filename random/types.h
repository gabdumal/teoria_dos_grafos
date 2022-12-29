
#ifndef __types_h__
#define __types_h__

#include <limits.h>


#define assigned(p)       ((p) != NULL)
#define isnull(p)         ((p) == NULL)

#define MAXREAL          9999999999
#define INTMAX           9999999


typedef enum { FALSE, TRUE } BOOL,  *PBOOL;

typedef          char        CHAR,  *PCHAR;  // caractere
typedef unsigned char        BYTE,  *PBYTE;
typedef unsigned short int   UINT,  *PUINT;
typedef signed   short int   INT,   *PINT;
typedef unsigned long  int   ULONG, *PULONG;
typedef signed   long  int   LONG,  *PLONG;

typedef float REAL, *PREAL;

typedef double LONGFLOAT, *PLONGFLOAT;

typedef void *POINTER;

#ifdef __MSDOS__

typedef unsigned short int   CARDINAL, *PCARDINAL;

#else

typedef unsigned long int    CARDINAL, *PCARDINAL;

#endif

#endif

