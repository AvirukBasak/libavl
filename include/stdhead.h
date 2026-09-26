#ifndef __STDHEAD_H__
#define __STDHEAD_H__

#include <stddef.h>    // type: size_t

typedef void *ptr_t;

#if !defined(__bool_true_false_are_defined) && __STDC_VERSION__ < 202311L
    typedef _Bool bool;
    #define true (1)
    #define false (0)
#endif

typedef signed char i8_t;
typedef signed short i16_t;
typedef signed long i32_t;
typedef signed long long i64_t;

typedef unsigned char ui8_t;
typedef unsigned short ui16_t;
typedef unsigned long ui32_t;
typedef unsigned long long ui64_t;

typedef float f32_t;
typedef double f64_t;

#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

void abort(void) __attribute__((noreturn));
// unsigned long strlen(const char *);
// void *memset(void *, int, unsigned long);
// void *memcpy(void *, const void *, unsigned long);

#endif
