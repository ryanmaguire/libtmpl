
/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_POLYNOMIAL_H__
#define __TMPL_POLYNOMIAL_H__

#include <libtmpl/include/tmpl_rational.h>

typedef struct _tmpl_PolynomialZ {
    unsigned long int *coeffs;
    unsigned long int degree;
} tmpl_PolynomialZ;

typedef struct _tmpl_PolynomialQ {
    tmpl_RationalNumber *coeffs;
    unsigned long int degree;
} tmpl_PolynomialQ;

typedef struct _tmpl_PolynomialZMatrix {
    tmpl_PolynomialZ **data;
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;
} tmpl_PolynomialZMatrix;

typedef struct _tmpl_PolynomialQMatrix {
    tmpl_PolynomialQ **data;
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;
} tmpl_PolynomialQMatrix;

extern void
tmpl_PolynomialQ_Add(tmpl_PolynomialQ *P,
                     tmpl_PolynomialQ *Q,
                     tmpl_PolynomialQ *sum);

extern void
tmpl_PolynomialQ_Multiply(tmpl_PolynomialQ *P,
                          tmpl_PolynomialQ *Q,
                          tmpl_PolynomialQ *prod);

extern void
tmpl_PolynomialZ_Add(tmpl_PolynomialZ *P,
                     tmpl_PolynomialZ *Q,
                     tmpl_PolynomialZ *sum);

extern void
tmpl_PolynomialZ_Multiply(tmpl_PolynomialZ *P,
                          tmpl_PolynomialZ *Q,
                          tmpl_PolynomialZ *prod);

#endif

