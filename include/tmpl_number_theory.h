#ifndef TMPL_NUMBER_THEORY_H
#define TMPL_NUMBER_THEORY_H

#include <libtmpl/include/tmpl_vector.h>

extern unsigned int tmpl_Short_Trailing_Zeros(short int n);
extern unsigned int tmpl_UShort_Trailing_Zeros(unsigned short int n);

extern unsigned int tmpl_Int_Trailing_Zeros(int n);
extern unsigned int tmpl_UInt_Trailing_Zeros(unsigned int n);

extern unsigned int tmpl_Long_Trailing_Zeros(long int n);
extern unsigned int tmpl_ULong_Trailing_Zeros(unsigned long int n);

extern unsigned int tmpl_Int_GCD(int m, int n);
extern unsigned int tmpl_UInt_GCD(unsigned int m, unsigned int n);
extern unsigned int tmpl_UIntVector_GCD(tmpl_UIntVector *arr);

extern tmpl_ULongVector *
tmpl_Sieve_of_Eratosthenes(unsigned long N);

#endif

