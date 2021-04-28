
/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_RATIONAL_H__
#define __TMPL_RATIONAL_H__

#include <libtmpl/include/tmpl_bool.h>

typedef struct _tmpl_RationalNumber {
    signed long int numerator;
    signed long int denominator;
} tmpl_RationalNumber;

extern tmpl_Bool
tmpl_RationalNumber_Compare(tmpl_RationalNumber p, tmpl_RationalNumber q);

extern tmpl_RationalNumber
tmpl_RationalNumber_Add(tmpl_RationalNumber p, tmpl_RationalNumber q);

extern tmpl_RationalNumber
tmpl_RationalNumber_Multiply(tmpl_RationalNumber p, tmpl_RationalNumber q);

#endif

